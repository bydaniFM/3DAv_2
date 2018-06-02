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

namespace example
{
	class Model : public Node
	{
		vector<Mesh> meshes;

		GLint          model_view_matrix_id;
		GLint          projection_matrix_id;

		shared_ptr < Shader_Program > shader;	//Meshes will share only one shader, while having different colors/textures

		string directory;

	public:

		Model(char *path)
		{
			loadModel(path);
		}

		void render(const glm::mat4 & parent_model_view) override;

	private:

		void loadModel(string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	};
}