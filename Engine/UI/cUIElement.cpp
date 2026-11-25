#include "cUIElement.h"

#include <Engine/Graphics/ConstantBufferFormats.h>
#include <Engine/Graphics/Graphics.h>
#include <Engine/Math/cMatrix_transformation.h>

#include <Engine/Logging/Logging.h>

#include <algorithm>
#include <cmath>

namespace
{
	struct sUIDrawData
	{
		float rect_ndc[4];
		float color[4];
		float unused[8];
	};

	float SnapToPixel(const float i_value)
	{
		return std::floor(i_value + 0.5f);
	}
}


eae6320::UI::sRect eae6320::UI::cUIElement::ResolveRect(const sRect& i_parentRect) const
{
	sRect rect;
	rect.width = std::max(0.0f, size.x.Resolve(i_parentRect.width));
	rect.height = std::max(0.0f, size.y.Resolve(i_parentRect.height));
	rect.x = i_parentRect.x + position.x.Resolve(i_parentRect.width) - (anchorX * rect.width);
	rect.y = i_parentRect.y + position.y.Resolve(i_parentRect.height) - (anchorY * rect.height);
	return rect;
}

void eae6320::UI::cUIElement::SubmitQuad(const sSubmitContext& i_context, const sRect& i_rect, const sColor& i_color, Graphics::cMesh* i_mesh)
{
	Graphics::cMesh* const mesh = i_mesh ? i_mesh : i_context.quadMesh;

	if (!mesh || !i_context.effect || (i_context.screenWidth == 0) || (i_context.screenHeight == 0))
	{
		return;
	}

	if (i_color.a <= 0.0f)
	{
		return;
	}

	const float left = SnapToPixel(i_rect.x);
	const float top = SnapToPixel(i_rect.y);
	const float width = SnapToPixel(i_rect.x + i_rect.width) - left;
	const float height = SnapToPixel(i_rect.y + i_rect.height) - top;

	if ((width <= 0.0f) || (height <= 0.0f))
	{
		return;
	}
	
	const float screenWidth = static_cast<float>(i_context.screenWidth);
	const float screenHeight = static_cast<float>(i_context.screenHeight);

	sUIDrawData drawData = {};
	drawData.rect_ndc[0] = (((left + (width * 0.5f)) / screenWidth) * 2.0f) - 1.0f;
	drawData.rect_ndc[1] = 1.0f - (((top + (height * 0.5f)) / screenHeight) * 2.0f);
	drawData.rect_ndc[2] = (width / screenWidth) * 2.0f;
	drawData.rect_ndc[3] = (height / screenHeight) * 2.0f;
	drawData.color[0] = i_color.r;
	drawData.color[1] = i_color.g;
	drawData.color[2] = i_color.b;
	drawData.color[3] = i_color.a;

	Math::cMatrix_transformation transformation;
	std::memcpy( static_cast<void*>(&transformation), &drawData, sizeof(transformation) );

	Graphics::SubmitMeshAndEffect(*mesh, *i_context.effect, transformation);
}

