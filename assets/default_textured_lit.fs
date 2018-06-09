#version 330

uniform sampler2D sampler;
/*uniform vec4 main_color;*/
uniform bool no_texture;

in  vec2 texture_uv;
in  vec3 front_color;
out vec4 fragment_color;

void main()
{
	/* Sets color to white (instead of black) if no texture */
	vec4 tex = vec4(texture(sampler, texture_uv.st).rgb, 1.0) + int(no_texture);
	
    fragment_color = tex * vec4(front_color, 1.0);
    //fragment_color = vec4(front_color, 1.0);
    //fragment_color = tex * vec4(1.0, 1.0, 1.0, 1.0);
}