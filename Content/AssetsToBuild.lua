--[[
	This file lists every asset that must be built by the AssetBuildSystem
]]

local module = {
	shaders =
	{
		{ path = "Shaders/Vertex/standard.shader", arguments = { "vertex" } },
		{ path = "Shaders/Fragment/standard.shader", arguments = { "fragment" } },
		{ path = "Shaders/Fragment/animatedColor.shader", arguments = { "fragment" } },
		{ path = "Shaders/Fragment/uiFrame.shader", arguments = { "fragment" } },

		{ path = "Shaders/Vertex/vertexInputLayout_mesh.shader", arguments = { "vertex" } },
		{ path = "Shaders/Vertex/uiFrame.shader", arguments = { "vertex" } },
	},

	meshes = {
		"Meshes/triangle.lua",
		"Meshes/rectangle.lua",
		"Meshes/plane.lua",
		"Meshes/rock.lua",
		"Meshes/hi.lua",

		"Meshes/uiQuad.lua",
	}
}

for i = 97, 98 do
	module.meshes[#module.meshes + 1] = string.format( "Meshes/Fonts/%03d.lua", i );
end


return module
