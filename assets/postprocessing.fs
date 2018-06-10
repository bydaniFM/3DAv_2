#version 330

uniform sampler2D sampler2d;

in  vec2 texture_uv;
out vec4 fragment_color;

void main()
{
	//Sepia
    vec3 color = texture (sampler2d, texture_uv.st).rgb;
    float i = (color.r + color.g + color.b) * 0.3333333333;
    fragment_color = vec4(vec3(i, i, i) * vec3(1.0, 0.75, 0.5), 1.0);

    //Waves
    /*int offset = 10;
    vec2 texcoord = texture_uv;
    texcoord.x += sin(texcoord.y * 4*2*3.14159 + offset) / 100;
    fragment_color = texture2D(sampler2d, texcoord);*/

    //Bloom - WIP
    /*vec3 luminanceVector = vec3(0.2125, 0.7154, 0.0721);
    vec4 c = texture2D(sampler2d, texture_uv);

    float luminance = dot(luminanceVector, c.xyz);
    luminance = max(0.0, luminance - 0.5);
    c.xyz *= sign(luminance);
    c.a = 1.0;
    fragment_color = c;*/

}