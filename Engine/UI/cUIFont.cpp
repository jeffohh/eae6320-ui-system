#include "cUIFont.h"

#include <Engine/Asserts/Asserts.h>
#include <Engine/Logging/Logging.h>
#include <Engine/Platform/Platform.h>

#include <cstdio>

eae6320::cResult eae6320::UI::cUIFont::Initialize(const char* const i_meshDirectory)
{
	auto result = Results::Success;

	unsigned int loadedCount = 0;
	for (unsigned int code = FirstCharacter; code <= LastCharacter; ++code)
	{
		char path[256];
		std::snprintf(path, sizeof(path), "%s%03u.lua", i_meshDirectory, code);

		if (!Platform::DoesFileExist(path))
		{
			EAE6320_ASSERTF(false, "Font mesh file doesn't exist: %s", path);
			Logging::OutputError("Font mesh file doesn't exist: %s", path);
			result = Results::Failure;
			continue;
		}

		Graphics::cMesh*& glyph = m_glyphs[code - FirstCharacter];
		if (!(result = Graphics::cMesh::Load(path, glyph)))
		{
			EAE6320_ASSERTF(false, "Failed to load font mesh file: %s", path);
			Logging::OutputError("Failed to load font mesh file: %s", path);
			continue;
		}

		++loadedCount;
	}

	Logging::OutputMessage("Loaded %u UI font glyph meshes from \"%s\"", loadedCount, i_meshDirectory);

	return result;
}

eae6320::cResult eae6320::UI::cUIFont::CleanUp()
{
	for (auto& glyph : m_glyphs)
	{
		if (glyph)
		{
			glyph->DecrementReferenceCount();
			glyph = nullptr;
		}
	}

	return Results::Success;
}

eae6320::Graphics::cMesh* eae6320::UI::cUIFont::GetGlyph(const char i_character) const
{
	if (i_character == ' ')
	{
		return nullptr;
	}

	const auto code = static_cast<uint8_t>(i_character);
	if (code < FirstCharacter || code > LastCharacter)
	{
		EAE6320_ASSERTF(false, "Invalid character: %c", i_character);
		return nullptr;
	}
	return m_glyphs[code - FirstCharacter];
}

float eae6320::UI::cUIFont::GetAdvance(const char i_character) const
{
	return (i_character == ' ') ? spaceAdvance : glyphAdvance;
}

eae6320::UI::cUIFont::~cUIFont()
{
	CleanUp();
}
