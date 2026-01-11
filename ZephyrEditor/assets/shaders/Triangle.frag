#version 450 core
// Input: interpolated color from vertex shader
in vec3 v_Color;

// Output: final pixel color
layout(location = 0) out vec4 o_Color;

void main()
{
    // Output RGB color with full alpha
    o_Color = vec4(v_Color, 1.0);
}