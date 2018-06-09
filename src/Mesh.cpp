/*

Author: Daniel Fernández
Date:	18/05/2018

*/

#include "Mesh.hpp"

using namespace std;

namespace oglsl
{
	Mesh::Mesh
	(
		vector<glm::vec3>		positions, 
		vector<glm::vec3>		normals, 
		vector<glm::vec2>		texCoords, 
		vector<unsigned int> &  indices, 
		vector<Texture>      &	textures
	)
	{

		number_of_indices = indices.size();

		//Setup Mesh

		glGenVertexArrays(1, &vao_id);
		glGenBuffers(1, &vbo_ids[COORDINATES_VBO]);
		glGenBuffers(1, &vbo_ids[UVS_VBO]);
		glGenBuffers(1, &vbo_ids[NORMALS_VBO]);
		glGenBuffers(1, &vbo_ids[INDICES_VBO]);
		glBindVertexArray(vao_id);
		/*glGenBuffers(VBO_COUNT, vbo_ids);
		glGenVertexArrays(1, &vao_id);
		glBindVertexArray(vao_id);*/

		// Se configuran el atributo de coordenadas de posición:

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Se configuran el atributo de coordenadas de textura:

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[UVS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// Se configuran el atributo de normales:

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Se configuran los índices:

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_VBO]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


		glBindVertexArray(0);
	}

	void Mesh::render(Shader_Program & shader)
	{
		//unsigned int diffuseNr = 1;
		//unsigned int specularNr = 1;
		//for (unsigned int i = 0; i < textures.size(); i++)
		//{
		//	glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		//									  // retrieve texture number (the N in diffuse_textureN)
		//	string number;
		//	string name = textures[i].type;
		//	if (name == "texture_diffuse")
		//		number = std::to_string(diffuseNr++);
		//	else if (name == "texture_specular")
		//		number = std::to_string(specularNr++);

		//	//shader.setFloat(("material." + name + number).c_str(), i);
		//	glBindTexture(GL_TEXTURE_2D, textures[i].id);
		//}
		//glActiveTexture(GL_TEXTURE0);



		// draw mesh

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);

		glBindVertexArray(vao_id);
		glDrawElements(GL_TRIANGLES, number_of_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
}