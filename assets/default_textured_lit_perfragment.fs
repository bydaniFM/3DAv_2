#version 330

struct Light
{
    vec4 position;
    vec3 color;
};

uniform Light light;
uniform float ambient_intensity;
uniform float diffuse_intensity;

uniform sampler2D sampler;
uniform vec3 material_color;
uniform bool no_texture;


in vec4 N;
in vec4 v;
in vec2 texture_uv;

out vec4 fragment_color;

void main (void)  
{  
	// Will be used for attenuation.
    float distance = length(light.position - v);
 
    // Get a lighting direction vector from the light to the vertex.
    vec4 lightVector = normalize(light.position - v);
 
    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(N, lightVector), 0.1);
 
    // Add attenuation. -- Disabled for testing purposes
    //diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));

    // Calculate tex color
    vec4 tex = vec4(texture(sampler, texture_uv.st).rgb, 1.0) + int(no_texture);
    vec4 col = tex * vec4(material_color, 1.0);
 
    // Multiply the color by the diffuse illumination level to get final output color.
    //fragment_color = col * diffuse;    
    fragment_color = ambient_intensity * col + diffuse_intensity * diffuse * vec4(light.color, 1.0) * col;
}