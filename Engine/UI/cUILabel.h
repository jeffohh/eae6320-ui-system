#pragma once

#include "cUIElement.h"

#include <string>

namespace eae6320
{
	namespace UI
	{
		enum class eTextAlignX {
			Left,
			Center,
			Right
		};

		enum class eTextAlignY {
			Top,
			Center,
			Bottom
		};

		class cUILabel : public cUIElement
		{
		public:
			std::string text;
			sColor textColor;
			sColor backgroundColor = sColor::FromRGBA(0, 0, 0, 0);

			float textHeight = 24.0f;
			float letterSpacing = 0.0f;

			eTextAlignX alignX = eTextAlignX::Center;
			eTextAlignY alignY = eTextAlignY::Center;

			void Submit(const sSubmitContext& i_context) const override;
		};
	}
}