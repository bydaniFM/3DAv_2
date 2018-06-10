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
#include "Framebuffer.hpp"
#include "Shader_Program.hpp"
#include "Vertex_Shader.hpp"
#include "Fragment_Shader.hpp"
#include "Input.hpp"

using namespace std;

namespace oglsl
{
	/// Default scene setup.
	/// Can implement custom children scenes.
	class Scene
	{
		/// Scene graph's parent node.
		shared_ptr< Node > root;

		/// Framebuffer to render the scene and apply post processing effects.
		shared_ptr< Framebuffer > framebuffer;

		/// Screen dymensions.
		int w_width, w_height;
		
	protected:

		/// Main camera.
		Camera camera;
		
		/// Default skybox.
		shared_ptr < Skybox > skybox;

		/// Camera angle around x axis.
		float angle_around_x;
		/// Camera angle around y axis.
		float angle_around_y;

		/// Available shaders for the scene.
		map < string, shared_ptr< Shader_Program > > shaders;

	public:

		/// Sets up scene variables and default shaders.
		Scene();

		/// Ads a new object to the scene.
		void add(string name, shared_ptr<Node> node)
		{
			root->addChild(name, node);
		}

		/// Gets and object from the scene root.
		shared_ptr < Node > getObject(string name)
		{
			return root->getChildren()[name];
		}

		/// Renders the scene.
		/// First renders the skybox and then all the objects in the graph.
		void render()
		{
			framebuffer->setFramebuffer();

			//glClearColor(.4f, .4f, .4f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			skybox->render(camera);

			//root->render(glm::inverse(camera.get_model_view()));
			root->render(camera.get_model_view());

			framebuffer->render(w_width, w_height);
		}

		/// Updates the graph root.
		virtual void update()
		{
			root->update();
		}

		/// Resizes the camera and projection_matrix of all shaders.
		void resize(int width, int height)
		{
			w_width = width;
			w_height = height;

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

		/// Processes input data.
		/// To implement in child scene.
		virtual void processInput(Input::InputData input_data)
		{
		}

		/// Configures lights.
		/// Default setup.
		/// @param program Shader to apply light parameters. Must support lightning.
		virtual void configure_light(shared_ptr < Shader_Program > program);
	};
}