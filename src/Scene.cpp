/*

Author: Daniel Fernández
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
		""
		"void main()"
		"{"
		"   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
		"}";

	const string Scene::fragment_shader_code =
		"#version 330\n"
		""
		"out vec4 fragment_color;"
		""
		"void main()"
		"{"
		"    fragment_color = vec4(1.0, 1.0, 1.0, 1.0);"
		"}";

	Scene::Scene()
	{
		root = make_shared<Node>();

		shaders["default"].reset(new Shader_Program());
		//shaders["sky"].reset(new Shader_Program("assets/metal.vs", "assets/metal.fs"));

		/*shaders["default"]->attach(Vertex_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_vs.glsl")));
		shaders["default"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_fs.glsl")));*/
		shaders["default"]->attach(Vertex_Shader(Shader::Source_Code::from_string(vertex_shader_code)));
		shaders["default"]->attach(Fragment_Shader(Shader::Source_Code::from_string(fragment_shader_code)));

		shaders["default"]->link();

		model_view_matrix_id = shaders["default"]->get_uniform_id("model_view_matrix");
		projection_matrix_id = shaders["default"]->get_uniform_id("projection_matrix");
	}
}