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

		static const std::string   vertex_shader_code;
		static const std::string fragment_shader_code;

		GLint model_view_matrix_id;
		GLint projection_matrix_id;

	protected:

		Camera camera;

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

			glm::mat4 projection_matrix = camera.get_projection();

			for (auto & shader : shaders)
			{
				shader.second->use();
				shader.second->set_uniform_value(projection_matrix_id, projection_matrix);
			}
		}

		virtual void processInput(Input::InputData input_data)
		{
		}
	};
}