#version 330

struct Light
{
    vec4 position;
    vec3 color;
};

uniform Light light;
uniform float ambient_intensity;
uniform float diffuse_intensity;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat4     normal_matrix;

uniform vec3 material_color;

layout (location = 0) in vec3 vertex_coordinates;
layout (location = 1) in vec2 vertex_texture_uv;
layout (location = 2) in vec3 vertex_normal;

out vec3 front_color;
out vec2 texture_uv;

void main()
{
    vec4  normal   = normal_matrix * vec4(vertex_normal, 1.0);
    vec4  position = model_view_matrix * vec4(vertex_coordinates, 1.0);

    vec4  light_direction = light.position - position;
    float light_intensity = diffuse_intensity * max (dot (normalize (normal.xyz), normalize (light_direction.xyz)), 0.0);
    
    texture_uv = vertex_texture_uv;

    front_color = ambient_intensity * material_color + diffuse_intensity * light_intensity * light.color * material_color;
    //front_color = material_color + vec3(light.position);// light_intensity;// * light.color * material_color;
    gl_Position = projection_matrix * position;
}