	
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <string>
    #include <GL/glew.h>            // Debe incluirse antes que gl.h
    #include "Cube.hpp"
	#include "Elevation_Mesh.hpp"
	#include "Model.hpp"

    namespace example
    {

        class View
        {
        private:

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

			GLint  model_view_matrix_id;
			GLint  projection_matrix_id;

            float  light_direction[4];

            Cube   cube;
            float  angle;

			Elevation_Mesh elevation_mesh;
			Model model_example;

        public:

            View(int width, int height);

            void   update ();
            void   render ();
            void   resize (int width, int height);

        private:

            GLuint compile_shaders        ();
            void   show_compilation_error (GLuint  shader_id);
            void   show_linkage_error     (GLuint program_id);

        };

    }

#endif
