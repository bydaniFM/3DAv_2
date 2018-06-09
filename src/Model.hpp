/*

Author: Daniel Fernández
Date:	18705/2018

*/

#pragma once

#include <iostream>

#include <scene.h>
#include <Importer.hpp>
#include <postprocess.h>

#include "Node.hpp"
#include "Mesh.hpp"

using namespace std;

namespace oglsl
{
	/// Represents a 3D model with several meshes
	class Model : public Node
	{
		vector<Mesh> meshes;

		GLint			model_view_matrix_id;
		GLint			normal_matrix_id;
		GLuint			texture_id;
		GLint			main_color_id;
		GLint			has_texture_id;

		/// Base color in case of no texture
		/// It is white by default when using texture
		glm::vec3		main_color;

		///Meshes will share only one shader, while having different colors/textures
		shared_ptr < Shader_Program > shader;

		string directory;
		bool has_texture;

	public:

		/// Initialices shader ids and loads model
		Model(char *path, shared_ptr<Shader_Program> shader)
			:
			shader(shader),
			has_texture(false)
		{
			model_view_matrix_id = shader->get_uniform_id("model_view_matrix");
			normal_matrix_id     = shader->get_uniform_id("normal_matrix");
			main_color_id        = shader->get_uniform_id("material_color");
			has_texture_id		 = shader->get_uniform_id("no_texture");

			main_color = glm::vec3(1, 1, 1);
			
			loadModel(path);

		}

		/// Initialices shader ids, loads model and sets base color
		Model(char *path, shared_ptr<Shader_Program> shader, glm::vec3 color)
			:
			shader(shader),
			has_texture(false)
		{
			model_view_matrix_id = shader->get_uniform_id("model_view_matrix");
			normal_matrix_id	 = shader->get_uniform_id("normal_matrix");
			main_color_id		 = shader->get_uniform_id("material_color");
			has_texture_id       = shader->get_uniform_id("no_texture");

			main_color = color;

			loadModel(path);
		}

		/// Sets texture and uniforms, and render all meshes
		void render(const glm::mat4 & parent_model_view) override;

	private:

		void loadModel(string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		void processTexture(string path);
		auto_ptr< Texture > loadTexture(string path);
	};
}