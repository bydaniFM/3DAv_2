#version 330

uniform sampler2D sampler;
uniform vec4 main_color;
uniform bool no_texture;

in  vec2 texture_uv;
out vec4 fragment_color;

void main()
{
	/* Sets color to white (instead of black) if no texture */
	vec4 tex = vec4(texture(sampler, texture_uv.st).rgb, 1.0) + int(no_texture);
	
    fragment_color = tex * main_color;
}