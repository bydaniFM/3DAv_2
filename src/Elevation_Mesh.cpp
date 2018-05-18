
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2018                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <vector>
#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Elevation_Mesh.hpp"
#include <SFML/OpenGL.hpp>
#include "Color_Buffer_Rgba8888.hpp"

extern "C"
{
#include <targa.h>
}

using std::vector;
using namespace glm;

namespace example
{

	Elevation_Mesh::Elevation_Mesh(int cols, int rows, float width, float depth, float elevation)
    {
		unsigned number_of_vertices =  cols      *  rows;
				 number_of_indices  = (cols - 1) * (rows - 1) * 2 * 3;

		std::vector< Point3f  > positions(number_of_vertices);
		std::vector< Point3f  > normals  (number_of_vertices);
		std::vector< Point2f  > uvs      (number_of_vertices);
		std::vector< unsigned > indices;

		indices.reserve (number_of_indices);

		// 1 CARGAR TEXTURA DE ELEVACION
		std::auto_ptr< Texture > texture = load_texture("..\\..\\assets\\elevation_texture.tga");//(texture_path);
		/*
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
		*/
		// Se generan los datos de las posiciones:

		float x_step = width / (cols - 1);
		float z_step = depth / (rows - 1);

		float z = -width / 2.f;

		for (int row = 0, i = 0; row < rows; ++row)		// row = z's
		{
			float x = -width / 2.f;

			for (int col = 0; col < cols; ++col)		// col = x's
			{
				float h = 0.f;
				// 1 SAMPLEAR LA TEXTURA USANDO COL Y ROW, Y GUARDAR LA ALTURA EN h
				h = texture->get_pixel( col * (texture->get_width() / cols),
										row * (texture->get_height() / rows)) / 255.f * elevation;
				positions[i++] = Point3f{ x, h, z };

				// Calcular las normales
				//for de 5, producto vectorial por triángulo, media de los productos
				/*for (int n = 0; n < 5; n++)
				{
					normals[i] = calculateNormal(	positions[row   * col   ],
													positions[row+1 * col   ],
													positions[row   * col-1 ],
													positions[row-1 * col   ],
													positions[row   * col+1 ]
					);
				}*/
				//normals[i] = positions[i] * positions[i-1]

				x += x_step;
			}

			z += z_step;
		}

		// Se generan los datos de los índices:

		for (int row = 0; row < rows - 1; ++row)				// r = z's
		{
			int i = row * cols;

			for (int col = 0; col < cols - 1; ++col, ++i)		// c = x's
			{
				// Se añade el primer triángulo:

				indices.push_back(i + 1);
				indices.push_back(i);
				indices.push_back(i + cols);

				// Se añade el segundo triángulo:

				indices.push_back(i + cols);
				indices.push_back(i + cols + 1);
				indices.push_back(i + 1);
			}
		}

		// Se generan índices para los VBOs del cubo:

		glGenBuffers(VBO_COUNT, vbo_ids);
		glGenVertexArrays(1, &vao_id);

		glBindVertexArray(vao_id);

		// Se suben a un VBO los datos de coordenadas:

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(Point3f), positions.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Se suben a un VBO los datos de color:

		/*glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
		glBufferData (GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);*/

		// Se suben a un VBO los datos de normales:

		// DESCOMENTAR CUANDO ESTËN LAS NORMALES
		//glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals.data(), GL_STATIC_DRAW);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// NO ES NECESARIO EN OPENGL MODERNO:
		// Se dejan activados los estados usados:
		//glEnableClientState (GL_VERTEX_ARRAY);
		//glEnableClientState (GL_COLOR_ARRAY );
		//glEnableClientState (GL_NORMAL_ARRAY);

		// Se suben a un VBO los datos de índices:

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_VBO]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


		glBindVertexArray(0);
    }

	Elevation_Mesh::~Elevation_Mesh()
    {
        // Se liberan los VBOs y el VAO usados:

		glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers (VBO_COUNT, vbo_ids);
    }

	/*Elevation_Mesh::Point3f Elevation_Mesh::calculateNormal(Point3f p0, Point3f p1, Point3f p2, Point3f p3, Point3f p4)
	{
		Point3f normal{ 0,0,0 };



		return normal;
	}*/

	glm::vec3 Elevation_Mesh::calculate_normal(const Point3f & p0, const Point3f & p1, const Point3f & p2)
	{
		// calcular los dos vectores del triángulos y retornar su producto vectorial...
		return glm::vec3();
	}

	glm::vec3 Elevation_Mesh::calculate_normal
	(
		const Point3f & p0, const Point3f & p1, const Point3f & p2,
		const Point3f & p3, const Point3f & p4, const Point3f & p5,
		const Point3f & p6, const Point3f & p7, const Point3f & p8
	)
	{
		glm::vec3 normal  = calculate_normal(p1, p4, p3);
		          normal += calculate_normal(p1, p2, p4);
		// calcular las otras 5 normales...

		// retornar la media aritmética

		return normal / 6.f;
	}

    void Elevation_Mesh::render ()
    {
		// Se selecciona el VAO que contiene los datos de la malla y se dibujan sus elementos:

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindVertexArray(vao_id);
		glDrawElements(GL_TRIANGLES, number_of_indices, GL_UNSIGNED_INT, 0);
    }

	std::auto_ptr< Texture > Elevation_Mesh::load_texture(const char * texture_file_path)
	{
		std::auto_ptr< Texture > texture;
		tga_image                loaded_image;

		if (tga_read(&loaded_image, texture_file_path) == TGA_NOERR)
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
