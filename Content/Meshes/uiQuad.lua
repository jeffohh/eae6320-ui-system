-- A unit quad centered on the origin. The UI vertex shader scales and moves it to cover each UI rectangle.
return {
    vertices = {
        { position = { -0.5, -0.5, 0.0 } },
        { position = { 0.5, -0.5, 0.0 } },
        { position = { 0.5, 0.5, 0.0 } },
        { position = { -0.5, 0.5, 0.0 } },
    },
    indices = {
        0, 1, 2, 0, 2, 3
    }
}
