
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

namespace oglsl
{
	/// Represents the cubemap texture rendered as the scene background.
    class Skybox
    {
    private:

        GLuint         vbo_id;                      // Id del VBO de las coordenadas
        GLuint         vao_id;                      // Id del VAO del cubo

        GLint          model_view_matrix_id;
        GLint          projection_matrix_id;

        Texture_Cube   texture_cube;

		/// Skybox shader.
		std::shared_ptr < Shader_Program > shader;

    public:

		/// Creates the cube ans inits the skybox shader.
        Skybox(const std::string & texture_path, std::shared_ptr < Shader_Program > shader);
        ~Skybox();

    public:

		/// Renders the skybox.
		/// Be careful when setting the camera near pane, as the skybox cube is 1x1x1. 0.5 is a safe value.
		/// @param camera Scene camera.
        void render (const Camera & camera);

    };

}
