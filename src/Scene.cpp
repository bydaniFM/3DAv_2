/*

Author: Daniel Fern�ndez
Date:	02/06/2018

*/

#include "Scene.hpp"

namespace oglsl
{
	using namespace std;
	
	Scene::Scene()
		:
		camera(0.5f, 5000.f)
	{
		root = make_shared<Node>();

		angle_around_x = 0.0f;
		angle_around_y = 0.0f;

		//Default shader

		shaders["default"].reset(new Shader_Program);

		shaders["default"]->attach(Vertex_Shader  (Shader::Source_Code::from_file("..\\..\\assets\\default_textured.vs")));
		shaders["default"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_textured.fs")));

		shaders["default"]->link();

		//Default lit shader

		shaders["default_lit"].reset(new Shader_Program);

		shaders["default_lit"]->attach(Vertex_Shader  (Shader::Source_Code::from_file("..\\..\\assets\\default_textured_lit.vs")));
		shaders["default_lit"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_textured_lit.fs")));

		shaders["default_lit"]->link();

		configure_light(shaders["default_lit"]);

		//Per fragment lit shader

		shaders["frag_lit"].reset(new Shader_Program);

		shaders["frag_lit"]->attach(Vertex_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_textured_lit_perfragment.vs")));
		shaders["frag_lit"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\default_textured_lit_perfragment.fs")));

		shaders["frag_lit"]->link();

		configure_light(shaders["frag_lit"]);

		//Sky shader

		shaders["sky"].reset(new Shader_Program);

		shaders["sky"]->attach(Vertex_Shader(Shader::Source_Code::from_file("..\\..\\assets\\skybox.vs")));
		shaders["sky"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\skybox.fs")));

		shaders["sky"]->link();

		skybox = make_shared<Skybox>("..\\..\\assets\\sky-cube-map-", shaders["sky"]);

		// Postprocessing shader

		shaders["postprocessing"].reset(new Shader_Program);

		shaders["postprocessing"]->attach(Vertex_Shader(Shader::Source_Code::from_file("..\\..\\assets\\postprocessing.vs")));
		shaders["postprocessing"]->attach(Fragment_Shader(Shader::Source_Code::from_file("..\\..\\assets\\postprocessing.fs")));

		shaders["postprocessing"]->link();

		framebuffer = make_shared<Framebuffer>(shaders["postprocessing"]);


		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

	}

	void Scene::configure_light(shared_ptr < Shader_Program > program)
	{
		program->use();

		GLint light_position	= program->get_uniform_id("light.position");
		GLint light_color		= program->get_uniform_id("light.color");
		GLint ambient_intensity = program->get_uniform_id("ambient_intensity");
		GLint diffuse_intensity = program->get_uniform_id("diffuse_intensity");

		program->set_uniform_value(light_position, glm::vec4(10.f, 10.f, 10.f, 1.f));
		program->set_uniform_value(light_color, glm::vec3(1.f, 1.f, 1.f));
		program->set_uniform_value(ambient_intensity, 0.2f);
		program->set_uniform_value(diffuse_intensity, 0.8f);
	}
}