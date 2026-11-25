#pragma once

#include <Engine/Graphics/cMesh.h>
#include <Engine/Results/Results.h>


namespace eae6320
{
	namespace UI
	{
		class cUIFont
		{
		public:
			static constexpr uint8_t FirstCharacter = 33; // "!"
			static constexpr uint8_t LastCharacter = 126; // "~"

			float glyphAdvance = 0.6f;
			float spaceAdvance = 0.4f;

			cResult Initialize(const char* const i_meshDirectory = "data/Meshes/Fonts/");
			cResult CleanUp();

			Graphics::cMesh* GetGlyph(const char i_character) const;
			float GetAdvance(const char i_character) const;

			cUIFont() = default;
			~cUIFont();

			cUIFont(const cUIFont&) = delete;
			cUIFont(cUIFont&&) = delete;
			cUIFont& operator=(const cUIFont&) = delete;
			cUIFont& operator=(cUIFont&&) = delete;

		private:
			static constexpr size_t GlyphCount = LastCharacter - FirstCharacter + 1;

			Graphics::cMesh* m_glyphs[GlyphCount] = {};
		};
	}
}
