#pragma once

#include "cUIElement.h"

namespace eae6320
{
	namespace UI
	{
		class cUIFrame : public cUIElement
		{
		public:
			sColor backgroundColor;

			void Submit(const sSubmitContext& i_context) const override;
		};
	}
}