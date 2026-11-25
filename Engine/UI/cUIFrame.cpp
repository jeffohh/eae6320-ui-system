#include "cUIFrame.h"

void eae6320::UI::cUIFrame::Submit(const sSubmitContext& i_context) const
{
	if (!visible)
	{
		return;
	}

	SubmitQuad(i_context, ResolveRect(i_context.parentRect), backgroundColor);
}