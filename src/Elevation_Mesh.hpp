
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on march of 2018                                          *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ELEVATION_MESH_HEADER
#define ELEVATION_MESH_HEADER

#include <memory>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace example
{

	class   Color_Buffer_Rgba8888;
	typedef Color_Buffer_Rgba8888 Texture;

    class Elevation_Mesh
    {
    private:

		typedef glm::vec2 Point2f;
		typedef glm::vec3 Point3f;
		typedef glm::vec3 Vector3f;

        // Índices para indexar el array vbo_ids:

        enum
        {
            COORDINATES_VBO,
            UVS_VBO,
			NORMALS_VBO,
			INDICES_VBO,
            VBO_COUNT
        };

    private:

        GLuint  vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
		GLuint  vao_id;                  // Id del VAO de la malla
		GLsizei number_of_indices;

    public:

		Elevation_Mesh(int cols, int rows, float width, float depth, float elevation);
        ~Elevation_Mesh();

		//Point3f calculateNormal(Point3f p0, Point3f p1, Point3f p2, Point3f p3, Point3f p4);
		glm::vec3 calculate_normal(const Point3f & p0, const Point3f & p1, const Point3f & p2);

		glm::vec3 calculate_normal
		(
			const Point3f & p0, const Point3f & p1, const Point3f & p2,
			const Point3f & p3, const Point3f & p4, const Point3f & p5,
			const Point3f & p6, const Point3f & p7, const Point3f & p8
		);
		

        void render ();

	private:

		bool   has_texture;
		GLuint texture_id;

		std::auto_ptr< Texture > load_texture(const char * texture_file_path);

    };

}

#endif
