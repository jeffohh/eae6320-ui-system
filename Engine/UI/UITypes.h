#pragma once

#include <cstdint>

namespace eae6320
{
	namespace UI
	{
		struct sColor
		{
			float r = 1.0f;
			float g = 1.0f;
			float b = 1.0f;
			float a = 1.0f;

			constexpr sColor() = default;
			constexpr sColor(const float i_r, const float i_g, const float i_b, const float i_a = 1.0f)
				: r(i_r), g(i_g), b(i_b), a(i_a) {
			}

			static constexpr sColor FromRGBA( const uint8_t i_r, const uint8_t i_g, const uint8_t i_b, const uint8_t i_a = 255 )
			{
				return sColor(i_r / 255.0f, i_g / 255.0f, i_b / 255.0f, i_a / 255.0f);
			}
		};

		struct sUDim
		{
			float scale = 0.0f;
			float offset = 0.0f;
			constexpr sUDim() = default;
			constexpr sUDim(const float i_scale, const float i_offset)
				: scale(i_scale), offset(i_offset) {
			}

			constexpr float Resolve(const float i_parentSize) const
			{
				return (scale * i_parentSize) + offset;
			}
		};

		struct sUDim2
		{
			sUDim x;
			sUDim y;
			constexpr sUDim2() = default;
			constexpr sUDim2(const sUDim i_x, const sUDim i_y)
				: x(i_x), y(i_y) {
			}
			constexpr sUDim2(const float i_xScale, const float i_xOffset, const float i_yScale, const float i_yOffset)
				: x(i_xScale, i_xOffset), y(i_yScale, i_yOffset) {
			}

			static constexpr sUDim2 FromOffset(const float i_xOffset, const float i_yOffset)
			{
				return sUDim2(sUDim(0.0f, i_xOffset), sUDim(0.0f, i_yOffset));
			}

			static constexpr sUDim2 FromScale(const float i_xScale, const float i_yScale)
			{
				return sUDim2(sUDim(i_xScale, 0.0f), sUDim(i_yScale, 0.0f));
			}

		};

		struct sRect
		{
			float x = 0.0f;
			float y = 0.0f;
			float width = 0.0f;
			float height = 0.0f;
		};
	}
}

