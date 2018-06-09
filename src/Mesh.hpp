/*

	Author: Daniel Fernández
	Date:	18705/2018

*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Color_Buffer_Rgba8888.hpp"
#include "Shader_Program.hpp"

using namespace std;

namespace example
{
	typedef Color_Buffer_Rgba8888 Texture;

	class Mesh
	{
	private:

		///Base color of the model
		Texture::Color color;

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

		//(Mesh(const string & path);
		Mesh
		(
			vector<glm::vec3>		positions, 
			vector<glm::vec3>		normals, 
			vector<glm::vec2>		texCoords, 
			vector<unsigned int> &	indices, 
			vector<Texture>      &	textures
		);

		void render(Shader_Program & shader);
	};
}