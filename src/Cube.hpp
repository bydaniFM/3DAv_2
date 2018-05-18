
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUBE_HEADER
#define CUBE_HEADER

    #include <SFML/OpenGL.hpp>

    namespace example
    {

        class Cube
        {
        private:

            // Índices para indexar el array vbo_ids:

            enum
            {
                COORDINATES_VBO,
                COLORS_VBO,
				NORMALS_VBO,
				INDICES_VBO,
                VBO_COUNT
            };

            // Arrays de datos del cubo base:

            static const GLfloat coordinates[][3];
            static const GLubyte colors     [][3];
            static const GLubyte indices    [][3];
			static const GLfloat normals	[][3];


        private:

            GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan

        public:

            Cube();
           ~Cube();

            void render ();

        };

    }

#endif
