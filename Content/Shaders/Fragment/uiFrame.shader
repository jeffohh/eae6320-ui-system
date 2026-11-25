/*
	Fragment shader for UI rectangles: outputs the color that the vertex shader passed along
*/

#include <Shaders/shaders.inc>

#if defined( EAE6320_PLATFORM_D3D )

void main(

	// Input
	//======

	in const float4 i_fragmentPosition : SV_POSITION,
	in const float4 i_color : COLOR0,

	// Output
	//=======

	out float4 o_color : SV_TARGET

)
{
	o_color = i_color;
}

#elif defined( EAE6320_PLATFORM_GL )

// (The name must match the vertex shader's output)
layout( location = 0 ) in vec4 v_color;

out vec4 o_color;

void main()
{
	o_color = v_color;
}

#endif
