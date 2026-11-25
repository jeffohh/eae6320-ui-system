#pragma once
#include "UITypes.h"
#include "cUIFont.h"

#include <Engine/Results/Results.h>
#include <Engine/Graphics/cMesh.h>
#include <Engine/Graphics/cEffect.h>
#include <cstdint>

namespace eae6320
{
	namespace UI
	{
		struct sSubmitContext
		{
			sRect parentRect;

			uint16_t screenWidth = 0;
			uint16_t screenHeight = 0;

			Graphics::cMesh* quadMesh = nullptr;
			Graphics::cEffect* effect = nullptr;

			const cUIFont* font = nullptr;
		};


		class cUIElement
		{
		public:
			// Screen-space position and dimensions (in pixels)
			sUDim2 position;
			sUDim2 size = sUDim2::FromOffset(200.0f, 100.0f);

			float anchorX = 0.0f; // 0.0f = left, 1.0f = right
			float anchorY = 0.0f; // 0.0f = top, 1.0f = bottom

			bool visible = true;

			virtual void Update(const float i_elapsedSecondCount ) {}
			virtual void Submit(const sSubmitContext& i_context) const {}

			sRect ResolveRect(const sRect& i_parentRect) const;

			cUIElement() = default;
			virtual ~cUIElement() = default;

			cUIElement(const cUIElement&) = delete;
			cUIElement(cUIElement&&) = delete;
			cUIElement& operator=(const cUIElement&) = delete;
			cUIElement& operator=(cUIElement&&) = delete;

		protected:
			static void SubmitQuad(const sSubmitContext& i_context, const sRect& i_rect, const sColor& i_color, Graphics::cMesh* i_mesh = nullptr);
		};
	}
}

