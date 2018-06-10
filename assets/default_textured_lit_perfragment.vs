#version 330

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat4     normal_matrix;

layout (location = 0) in vec3 vertex_coordinates;
layout (location = 1) in vec2 vertex_texture_uv;
layout (location = 2) in vec3 vertex_normal;

uniform float ambient_intensity;
uniform float diffuse_intensity;

out vec4 N;
out vec4 v;
out vec2 texture_uv;

void main(void)  
{
	//vec4  position = model_view_matrix * vec4(vertex_coordinates, 1.0);

	texture_uv = vertex_texture_uv;

   	v = model_view_matrix * vec4(vertex_coordinates, 1.0);
   	N = normal_matrix * vec4(vertex_normal, 1.0);

   	gl_Position = projection_matrix * v;
}