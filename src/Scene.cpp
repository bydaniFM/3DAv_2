/*

Author: Daniel Fern�ndez
Date:	02/06/2018

*/

#include "Scene.hpp"

namespace example
{

	using namespace std;

	const string Scene::vertex_shader_code =
		"#version 330\n"
		""
		"uniform mat4 model_view_matrix;"
		"uniform mat4 projection_matrix;"
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		"layout (location = 1) in vec3 vertex_texture_uv;"
		""
		"out vec2 texture_uv;"
		""
		"void main()"
		"{"
		"    texture_uv = vertex_texture_uv;"
		"   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
		"}";

	const string Scene::fragment_shader_code =
		"#version 330\n"
		""
		"uniform  sampler2D sampler;"
		"in  vec2 texture_uv;"
		"out vec4 fragment_color;"
		""
		"void main()"
		"{"
		//"    fragment_color = vec4(1.0, 1.0, 1.0, 1.0);"
		"    fragment_color = vec4(texture(sampler, texture.st).rgb, 1.0);"
		"}";

	Scene::Scene()
		:
		camera(1.f, 1000.f)
	{
		root = make_shared<Node>();

		angle_around_x = 0.0f;
		angle_around_y = 0.0f;

		//Default shader

		shaders["default"].reset(new Shader_Program);

		shaders["default"]->attach(Vertex_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_textured.vs")));
		shaders["default"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_textured.fs")));
		/*shaders["default"]->attach(Vertex_Shader(Shader::Source_Code::from_string(vertex_shader_code)));
		shaders["default"]->attach(Fragment_Shader(Shader::Source_Code::from_string(fragment_shader_code)));*/

		shaders["default"]->link();

		model_view_matrix_id = shaders["default"]->get_uniform_id("model_view_matrix");
		projection_matrix_id = shaders["default"]->get_uniform_id("projection_matrix");
		//GLint main_color_id = shaders["default"]->get_uniform_id("main_color");

		//Sky shader

		//shaders["sky"].reset(new Shader_Program("assets/metal.vs", "assets/metal.fs"));

		// Se habilita el backface culling, una luz y materiales b�sicos:

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}
}