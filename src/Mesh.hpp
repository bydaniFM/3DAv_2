/*

	Author: Daniel Fernández
	Date:	18705/2018

*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm\glm.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Color_Buffer_Rgba8888.hpp"

using namespace std;

namespace example
{
	//class   Color_Buffer_Rgba8888;
	typedef Color_Buffer_Rgba8888 Texture;

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	/*struct Texture {
		unsigned int id;
		string type;
		string path;
	};*/

	class Mesh
	{
	private:

		typedef glm::vec2 Point2f;
		typedef glm::vec3 Point3f;
		typedef glm::vec3 Vector3f;

		enum
		{
			COORDINATES_VBO,
			UVS_VBO,
			NORMALS_VBO,
			INDICES_VBO,
			VBO_COUNT
		};

		GLuint  vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
		GLuint  vao_id;                  // Id del VAO de la malla
		GLsizei number_of_indices;

		

	public:

		/*  Mesh Data  */
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		//(Mesh(const string & path);
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

		void render();
	};
}