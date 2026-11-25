#include "cUILabel.h"

#include "cUIFont.h"

#include <cmath>

void eae6320::UI::cUILabel::Submit(const sSubmitContext& i_context) const
{
	if (!visible)
	{
		return;
	}

	const sRect rect = ResolveRect(i_context.parentRect);

	// optional background quad
	SubmitQuad(i_context, rect, backgroundColor);

	if (text.empty() || !i_context.font || (textHeight <= 0.0f))
	{
		return;
	}

	const cUIFont& font = *i_context.font;

	// calculate size of each glyph in pixels
	const float glyphSize = std::floor(textHeight + 0.5f);

	// calculate total width
	float totalWidth = 0.0f;
	for (const char character : text)
	{
		totalWidth += (font.GetAdvance(character) * glyphSize) + letterSpacing;
	}
	totalWidth -= letterSpacing;

	// where the first character's cell starts
	float penX = rect.x;
	switch (alignX)
	{
	case eTextAlignX::Left:   penX = rect.x; break;
	case eTextAlignX::Center: penX = rect.x + ((rect.width - totalWidth) * 0.5f); break;
	case eTextAlignX::Right:  penX = rect.x + rect.width - totalWidth; break;
	}

	float top = rect.y;
	switch (alignY)
	{
	case eTextAlignY::Top:    top = rect.y; break;
	case eTextAlignY::Center: top = rect.y + ((rect.height - glyphSize) * 0.5f); break;
	case eTextAlignY::Bottom: top = rect.y + rect.height - glyphSize; break;
	}
	top = std::floor(top + 0.5f);

	const float rightEdge = rect.x + rect.width;
	constexpr float tolerance = 0.01f;

	for (const char character : text)
	{
		const float cellWidth = font.GetAdvance(character) * glyphSize;

		// skip characters whose cell isn't fully inside the label
		const bool isInside = (penX >= (rect.x - tolerance)) && ((penX + cellWidth) <= (rightEdge + tolerance));

		Graphics::cMesh* const glyph = font.GetGlyph(character);
		if (isInside && glyph)
		{
			// the glyph mesh fills a square cell, centered horizontally on the character's advance cell
			sRect glyphRect;
			glyphRect.width = glyphSize;
			glyphRect.height = glyphSize;
			glyphRect.x = std::floor((penX + (cellWidth * 0.5f) - (glyphSize * 0.5f)) + 0.5f);
			glyphRect.y = top;
			SubmitQuad(i_context, glyphRect, textColor, glyph);
		}

		penX += cellWidth + letterSpacing;
	}
}



