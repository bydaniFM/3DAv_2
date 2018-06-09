#version 330

in  vec3 texture_coordinates;
out vec4 fragment_color;

uniform samplerCube texture_cube;

void main()
{
    fragment_color = texture (texture_cube, texture_coordinates);
}