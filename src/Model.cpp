/*

Author: Daniel Fernández
Date:	18705/2018

*/

#include "Model.hpp"

namespace example
{
	void Model::render(const glm::mat4 & parent_model_view)
	{
		//for (unsigned int i = 0; i < meshes.size(); i++)
		//	meshes[i].render(/*shader*/);

		glm::mat4 model_view = parent_model_view * Node::transform;

		shader->use();
		shader->set_uniform_value(model_view_matrix_id, model_view);

		for (auto & mesh : meshes)
		{
			mesh.render(*shader);
		}

		Node::render(model_view);			// llama al método render() de la clase Node
	}

	void Model::loadModel(string path)
	{
		Assimp::Importer import;
		//const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		vector<glm::vec3> positions;
		vector<glm::vec3> normals;
		vector<glm::vec2> texCoords;

		vector<unsigned int> indices;
		vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			glm::vec3 position;
			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;
			positions.push_back(position);

			glm::vec3 normal;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;

			glm::vec2 texCoord;
			//if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			//{
			//	vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			//	vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			//} else
			//	vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			texCoord = glm::vec2(0.0f, 0.0f);
			texCoords.push_back(texCoord);

		}
		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(mesh->mFaces[i].mIndices[j]);
		}

		// process material
		/*if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}*/

		return Mesh(positions, normals, texCoords, indices, textures);
	}

	//See optimization
	/*vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
		}
		return textures;
	}*/
}