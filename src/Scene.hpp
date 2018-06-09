/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Node.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"
#include "Shader_Program.hpp"
#include "Vertex_Shader.hpp"
#include "Fragment_Shader.hpp"
#include "Input.hpp"

using namespace std;

namespace example
{
	class Scene
	{
		//vector<shared_ptr<Node>> graph;

		shared_ptr< Node > root;
		
		GLint model_view_matrix_id;
		GLint projection_matrix_id;

	protected:

		Camera camera;
		
		shared_ptr < Skybox > skybox;

		float angle_around_x;
		float angle_around_y;

		map < string, shared_ptr< Shader_Program > > shaders;

	public:

		Scene();

		void add(shared_ptr<Node> node)
		{
			root->addChild(node);
		}

		void render()
		{

			glClearColor(.4f, .4f, .4f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			skybox->render(camera);

			//root->render(glm::inverse(camera.get_model_view()));
			root->render(camera.get_model_view());
		}

		void update()
		{
			root->update();
		}

		void resize(int width, int height)
		{
			camera.set_ratio(float(width) / height);
			glViewport(0, 0, width, height);

			glm::mat4 projection_matrix = camera.get_projection();

			for (auto & shader : shaders)
			{
				GLuint proj_id = shader.second->get_uniform_id("projection_matrix");
				shader.second->use();
				shader.second->set_uniform_value(proj_id, projection_matrix);
			}
		}

		virtual void processInput(Input::InputData input_data)
		{
		}

		virtual void configure_light(shared_ptr < Shader_Program > program);
	};
}