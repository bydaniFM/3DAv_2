
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include <vector>
#include <memory>
#include "Camera.hpp"
#include "Texture_Cube.hpp"
#include "Shader_Program.hpp"

namespace example
{

    class Skybox
    {
    private:

        GLuint         vbo_id;                      // Id del VBO de las coordenadas
        GLuint         vao_id;                      // Id del VAO del cubo

        GLint          model_view_matrix_id;
        GLint          projection_matrix_id;

        Texture_Cube   texture_cube;

		std::shared_ptr < Shader_Program > shader;

    public:

        Skybox(const std::string & texture_path, std::shared_ptr < Shader_Program > shader);
        ~Skybox();

    public:

        void render (const Camera & camera);

    };

}
