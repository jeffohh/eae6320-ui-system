#include "cUIManager.h"
#include <Engine/Asserts/Asserts.h>
#include <Engine/Logging/Logging.h>

eae6320::cResult eae6320::UI::cUIManager::Initialize()
{
	auto result = Results::Success;

	if (!(result = Graphics::cMesh::Load("data/Meshes/uiQuad.lua", m_quadMesh)))
	{
		EAE6320_ASSERTF(false, "Failed to load rectangle mesh for UI");
		Logging::OutputError("Failed to load rectangle mesh for UI");
		return result;
	}

	constexpr uint8_t renderStateBits = []
		{
			uint8_t bits = 0;
			Graphics::RenderStates::EnableAlphaTransparency(bits); // alpha blending
			Graphics::RenderStates::DisableDepthTesting(bits); // remove depth so it's on top
			Graphics::RenderStates::DisableDepthWriting(bits);
			Graphics::RenderStates::EnableDrawingBothTriangleSides(bits);
			return bits;
		}();

	if (!(result = Graphics::cEffect::Load(m_uiEffect, "data/Shaders/Vertex/uiFrame.shader", "data/Shaders/Fragment/uiFrame.shader", renderStateBits)))
	{
		EAE6320_ASSERTF(false, "Failed to load shader effect for UI");
		Logging::OutputError("Failed to load shader effect for UI");
		return result;
	}

	if (!(result = m_font.Initialize()))
	{
		EAE6320_ASSERTF(false, "Failed to initialize font for UI");
		Logging::OutputError("Failed to initialize font for UI");
		return result;
	}

	return result;
}

eae6320::cResult eae6320::UI::cUIManager::CleanUp()
{
	auto result = Results::Success;

	ClearElements();

	m_font.CleanUp();

	if (m_quadMesh)
	{
		m_quadMesh->DecrementReferenceCount();
		m_quadMesh = nullptr;
	}
	if (m_uiEffect)
	{
		m_uiEffect->DecrementReferenceCount();
		m_uiEffect = nullptr;
	}

	return result;
}

void eae6320::UI::cUIManager::ClearElements()
{
	m_elements.clear();
}

void eae6320::UI::cUIManager::Update(float i_elapsedSecondCount)
{
	for (auto& element : m_elements)
	{
		if (element)
		{
			element->Update(i_elapsedSecondCount);
		}
	}
}

void eae6320::UI::cUIManager::Submit(uint16_t i_screenWidth, uint16_t i_screenHeight)
{
	if (!m_quadMesh || !m_uiEffect || i_screenWidth == 0 || i_screenHeight == 0)
	{
		return;
	}

	sSubmitContext context;
	context.parentRect.x = 0.0f;
	context.parentRect.y = 0.0f;
	context.parentRect.width = static_cast<float>(i_screenWidth);
	context.parentRect.height = static_cast<float>(i_screenHeight);
	context.screenWidth = i_screenWidth;
	context.screenHeight = i_screenHeight;
	context.quadMesh = m_quadMesh;
	context.effect = m_uiEffect;
	context.font = &m_font;

	for (auto& element : m_elements)
	{
		if (element)
		{
			element->Submit(context);
		}
	}
}

eae6320::UI::cUIManager::~cUIManager()
{
	CleanUp();
}