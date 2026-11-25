/*
	Vertex shader for UI rectangles

	The UI doesn't use the camera or a real transform matrix. Instead, the 64 bytes that Graphics
	sends per draw call (the "draw call" constant buffer) are read as four float4s.
	This layout must match sUIDrawData in Engine/UI/cUIElement.cpp.
*/

#include <Shaders/shaders.inc>

#if defined( EAE6320_PLATFORM_D3D )

cbuffer g_constantBuffer_drawCall : register( b2 )
{
	// xy = center of the rectangle in normalized device coordinates, zw = size of the rectangle in normalized device coordinates
	float4 g_ui_rect;
	float4 g_ui_color;
	float4 g_ui_unused0;
	float4 g_ui_unused1;
};

void main(

	// Input
	//======

	// The unit quad (-0.5 to 0.5 on each axis)
	in const float3 i_vertexPosition_local : POSITION,

	// Output
	//=======

	out float4 o_vertexPosition_projected : SV_POSITION,
	out float4 o_color : COLOR0

)
{
	const float2 position_ndc = ( i_vertexPosition_local.xy * g_ui_rect.zw ) + g_ui_rect.xy;
	o_vertexPosition_projected = float4( position_ndc, 0.0, 1.0 );
	o_color = g_ui_color;
}

#elif defined( EAE6320_PLATFORM_GL )

layout( std140, binding = 2 ) uniform g_constantBuffer_drawCall
{
	// xy = center of the rectangle in normalized device coordinates, zw = size of the rectangle in normalized device coordinates
	vec4 g_ui_rect;
	vec4 g_ui_color;
	vec4 g_ui_unused0;
	vec4 g_ui_unused1;
};

// The unit quad (-0.5 to 0.5 on each axis)
layout( location = 0 ) in vec3 i_vertexPosition_local;

// (The name must match the fragment shader's input)
layout( location = 0 ) out vec4 v_color;

void main()
{
	const vec2 position_ndc = ( i_vertexPosition_local.xy * g_ui_rect.zw ) + g_ui_rect.xy;
	gl_Position = vec4( position_ndc, 0.0, 1.0 );
	v_color = g_ui_color;
}

#endif
