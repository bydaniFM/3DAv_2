#version 330

uniform vec4 main_color
out vec4 fragment_color;

void main()
{
    fragment_color = main_color;
}