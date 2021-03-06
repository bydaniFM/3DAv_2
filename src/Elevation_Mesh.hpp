
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by �ngel on march of 2018                                          *
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

#include "Node.hpp"
#include "Shader_Program.hpp"

namespace oglsl
{

	class   Color_Buffer_Rgba8888;
	typedef Color_Buffer_Rgba8888 Texture;

	/// Represents a terrain mesh created from an elevation texture.
	/// The texture works in B/W scale or red scale.
    class Elevation_Mesh : public Node
    {
    private:

		typedef glm::vec2 Point2f;
		typedef glm::vec3 Point3f;
		typedef glm::vec3 Vector3f;

        // �ndices para indexar el array vbo_ids:

        enum
        {
            COORDINATES_VBO,
            UVS_VBO,
			NORMALS_VBO,
			INDICES_VBO,
            VBO_COUNT
        };

		/// Must be an unlit shader for now.
		shared_ptr < Shader_Program > shader;

		GLint   model_view_matrix_id;

        GLuint  vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
		GLuint  vao_id;                  // Id del VAO de la malla
		GLsizei number_of_indices;

		bool   has_texture;

		GLuint texture_id;
		GLint  main_color_id;
		GLint  has_texture_id;

    public:

		/// Creates an elevetion mesh with texture.
		Elevation_Mesh(int cols, int rows, float width, float depth, float elevation, shared_ptr < Shader_Program > shader);
        ~Elevation_Mesh();

		//Point3f calculateNormal(Point3f p0, Point3f p1, Point3f p2, Point3f p3, Point3f p4);
		glm::vec3 calculate_normal(const Point3f & p0, const Point3f & p1, const Point3f & p2);

		glm::vec3 calculate_normal
		(
			const Point3f & p0, const Point3f & p1, const Point3f & p2,
			const Point3f & p3, const Point3f & p4, const Point3f & p5,
			const Point3f & p6, const Point3f & p7, const Point3f & p8
		);
		
		/// Renders the mesh.
        void render (const glm::mat4 & parent_model_view) override;

	private:
		
		std::auto_ptr< Texture > load_texture(const char * texture_file_path);

    };

}

#endif
