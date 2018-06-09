
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Skybox.hpp"
#include <SFML/OpenGL.hpp>
#include "Vertex_Shader.hpp"
#include "Fragment_Shader.hpp"

namespace example
{

    namespace
    {
        GLfloat coordinates[] =
        {
            -1.0f, +1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            +1.0f, -1.0f, -1.0f,
            +1.0f, -1.0f, -1.0f,
            +1.0f, +1.0f, -1.0f,
            -1.0f, +1.0f, -1.0f,
            -1.0f, -1.0f, +1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, +1.0f, -1.0f,
            -1.0f, +1.0f, -1.0f,
            -1.0f, +1.0f, +1.0f,
            -1.0f, -1.0f, +1.0f,
            +1.0f, -1.0f, -1.0f,
            +1.0f, -1.0f, +1.0f,
            +1.0f, +1.0f, +1.0f,
            +1.0f, +1.0f, +1.0f,
            +1.0f, +1.0f, -1.0f,
            +1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, +1.0f,
            -1.0f, +1.0f, +1.0f,
            +1.0f, +1.0f, +1.0f,
            +1.0f, +1.0f, +1.0f,
            +1.0f, -1.0f, +1.0f,
            -1.0f, -1.0f, +1.0f,
            -1.0f, +1.0f, -1.0f,
            +1.0f, +1.0f, -1.0f,
            +1.0f, +1.0f, +1.0f,
            +1.0f, +1.0f, +1.0f,
            -1.0f, +1.0f, +1.0f,
            -1.0f, +1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, +1.0f,
            +1.0f, -1.0f, -1.0f,
            +1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, +1.0f,
            +1.0f, -1.0f, +1.0f,
        };
	}

    Skybox::Skybox(const std::string & texture_base_path, std::shared_ptr < Shader_Program > shader)
    :
        texture_cube(texture_base_path),
		shader(shader)
    {
        assert(texture_cube.is_ok ());
				
        model_view_matrix_id = shader->get_uniform_id("model_view_matrix");
        projection_matrix_id = shader->get_uniform_id ("projection_matrix");

        // Se generan índices para los VBOs del cubo:

        glGenBuffers (1, &vbo_id);
        glGenVertexArrays (1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray (vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_id);
        glBufferData (GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

        glEnableVertexAttribArray (0);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray (0);
    }

    Skybox::~Skybox()
    {
        // Se libera el VBO y el VAO usados:

        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (1, &vbo_id);
    }

    void Skybox::render (const Camera & camera)
    {
		shader->use ();

        texture_cube.bind ();

        glm::mat4 model_view_matrix = glm::scale(camera.get_model_view(), glm::vec3(1000, 1000, 1000));
        glm::mat4 projection_matrix = camera.get_projection ();

        glUniformMatrix4fv (model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));
        glUniformMatrix4fv (projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glDepthMask (GL_FALSE);

        glBindVertexArray  (vao_id);
        glDrawArrays (GL_TRIANGLES, 0, 36);
        glBindVertexArray  (0);

        glDepthMask (GL_TRUE);

		shader->disable ();
    }

}
