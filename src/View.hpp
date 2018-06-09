	
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
	//#include "Elevation_Mesh.hpp"
	//#include "Model.hpp"
	#include "Scene.hpp"
	#include "Input.hpp"

    namespace oglsl
    {

        class View
        {
        private:

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

			glm::mat4 model_view_matrix;

			GLint  model_view_matrix_id;
			GLint  projection_matrix_id;

            float  light_direction[4];

            Cube   cube;
            float  angle;

			/*Elevation_Mesh elevation_mesh;
			Model model_example;*/
			shared_ptr<Scene> scene;

        public:

			/// Creates a view with the specified dymensions
			/// And sets the scene which is going to be rendered
            View(int width, int height, shared_ptr<Scene> scene);

			/// Applies the imput data to the view
			/// Now it's rotating and translating the view
            void   update (Input::InputData input_data);

			/// Renders every node in the scene
            void   render ();

			/// Resizes the view given the window dimensions
			/// @param width window width
			/// @param width window height
            void   resize (int width, int height);

        private:

			/// Compiles the view shaders
            GLuint compile_shaders        ();

            void   show_compilation_error (GLuint  shader_id);
            void   show_linkage_error     (GLuint program_id);

        };

    }

#endif
