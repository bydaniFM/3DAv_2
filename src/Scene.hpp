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

		map < string, shared_ptr< Shader_Program > > shaders;

		Camera camera;

	public:

		Scene();

		void add(shared_ptr<Node> node)
		{
			root->addChild(node);
		}

		void render()
		{
			root->render(camera.get_projection());
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
				shader.second->use(); // use();
				shader.second->set_uniform_value(projection_matrix_id, projection_matrix);
			}
		}

		virtual void processInput(Input::InputData input_data)
		{
		}
	};
}