/*

Author: Daniel Fernández
Date:	18705/2018

*/

#include "Model.hpp"

extern "C"
{
#include <targa.h>
}

namespace example
{
	void Model::render(const glm::mat4 & parent_model_view)
	{
		if (has_texture)
		{
			glBindTexture(GL_TEXTURE_2D, texture_id);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glm::mat4 model_view = parent_model_view * Node::transform;
		glm::mat4 normal_matrix = glm::transpose(glm::inverse(model_view));

		shader->use();
		shader->set_uniform_value(model_view_matrix_id, model_view);
		shader->set_uniform_value(normal_matrix_id, normal_matrix);
		shader->set_uniform_value(main_color_id, main_color);
		shader->set_uniform_value(has_texture_id, !has_texture);

		for (auto & mesh : meshes)
		{
			mesh.render(*shader);
		}

		Node::render(model_view);

		shader->disable();
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

		processTexture(path);
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
			normals.push_back(normal);

			glm::vec2 texCoord;
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				texCoord.x = mesh->mTextureCoords[0][i].x;
				texCoord.y = mesh->mTextureCoords[0][i].y;
			} else
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

	void Model::processTexture(string path)
	{
		path = path.substr(0, path.find_last_of('.')) + ".tga";
		const char * texture_path = path.c_str();

		if (texture_path != 0)
		{
			std::auto_ptr< Texture > texture = loadTexture(texture_path);

			has_texture = texture.get() != 0;

			if (has_texture)
			{
				// Se habilitan las texturas, se genera un id para un búfer de textura,
				// se selecciona el búfer de textura creado y se configuran algunos de
				// sus parámetros:

				glEnable(GL_TEXTURE_2D);
				glGenTextures(1, &texture_id);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				// Se suben los colores de la textura a la memoria de vídeo:

				glTexImage2D
				(
					GL_TEXTURE_2D,
					0,
					GL_RGBA,
					texture->get_width(),
					texture->get_height(),
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture->colors()
				);
			}
		}
	}

	auto_ptr< Texture > Model::loadTexture(string path)
	{
		std::auto_ptr< Texture > texture;
		tga_image                loaded_image;

		if (tga_read(&loaded_image, path.c_str()) == TGA_NOERR)
		{
			// Si se ha podido cargar la imagen desde el archivo, se crea un búfer para una textura:

			texture.reset(new Texture(loaded_image.width, loaded_image.height));

			// Se convierte el formato de píxel de la imagen cargada a RGBA8888:

			tga_convert_depth(&loaded_image, texture->bits_per_color());
			tga_swap_red_blue(&loaded_image);

			// Se copian los pixels del búfer de la imagen cargada al búfer de la textura:

			Texture::Color * loaded_image_pixels = reinterpret_cast< Texture::Color * >(loaded_image.image_data);
			Texture::Color * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
			Texture::Color * image_buffer_pixels = texture->colors();

			while (loaded_image_pixels <  loaded_image_pixels_end)
			{
				*image_buffer_pixels++ = *loaded_image_pixels++;
			}

			tga_free_buffers(&loaded_image);
		}

		return (texture);
	}
}