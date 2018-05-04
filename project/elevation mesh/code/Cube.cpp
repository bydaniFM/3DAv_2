
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Cube.hpp"
#include <SFML/OpenGL.hpp>

namespace example
{

    const GLfloat Cube::coordinates[][3] =
    {
        { -1.f, -1.f, +1.f },   // 0
        { +1.f, -1.f, +1.f },   // 1
        { +1.f, +1.f, +1.f },   // 2
        { -1.f, +1.f, +1.f },   // 3
        { -1.f, -1.f, -1.f },   // 4
        { +1.f, -1.f, -1.f },   // 5
        { +1.f, +1.f, -1.f },   // 6
        { -1.f, +1.f, -1.f },   // 7
    };

    const GLubyte Cube::colors[][3] =
    {
        {   0,   0, 255 },      // 0    Representa un cubo RGB
        { 255,   0, 255 },      // 1
        { 255, 255, 255 },      // 2
        {   0, 255, 255 },      // 3
        {   0,   0,   0 },      // 4
        { 255,   0,   0 },      // 5
        { 255, 255,   0 },      // 6
        {   0, 255,   0 },      // 7
    };

    const GLubyte Cube::indices[][3] =
    {
        { 0, 1, 2 },            // front
        { 0, 2, 3 },
        { 4, 0, 3 },            // left
        { 4, 3, 7 },
        { 7, 5, 4 },            // back
        { 7, 6, 5 },
        { 1, 5, 6 },            // right
        { 1, 6, 2 },
        { 3, 2, 6 },            // top
        { 3, 6, 7 },
        { 5, 0, 4 },            // bottom
        { 5, 1, 0 },
    };

	const GLfloat Cube::normals[][3] =
	{
		{ 0,  0, +1 },         // front
		{ 0,  0, +1 },
		{ -1,  0,  0 },         // left
		{ -1,  0,  0 },
		{ 0,  0, -1 },         // back
		{ 0,  0, -1 },
		{ +1,  0,  0 },         // right
		{ +1,  0,  0 },
		{ 0, +1,  0 },         // top
		{ 0, +1,  0 },
		{ 0, -1,  0 },         // bottom
		{ 0, -1,  0 },
	};

    Cube::Cube()
    {
        // Se generan índices para los VBOs del cubo:

        glGenBuffers (VBO_COUNT, vbo_ids);

        // Se suben a un VBO los datos de coordenadas:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

        // Se suben a un VBO los datos de color:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		// Se suben a un VBO los datos de normales:

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

        // Se suben a un VBO los datos de índices:

        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_VBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Se dejan activados los estados usados:

        glEnableClientState (GL_VERTEX_ARRAY);
        glEnableClientState (GL_COLOR_ARRAY );
		glEnableClientState (GL_NORMAL_ARRAY);
    }

    Cube::~Cube()
    {
        // Se liberan los VBOs usados:

        glDeleteBuffers (VBO_COUNT, vbo_ids);
    }

    void Cube::render ()
    {
        // Se selecciona el VBO de coordenadas y se hace que VertexPointer apunte a él:

        glBindBuffer    (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glVertexPointer (3, GL_FLOAT, 0, 0);

        // Se selecciona el VBO de colores y se hace que ColorPointer apunte a él:

        glBindBuffer    (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glColorPointer  (3, GL_UNSIGNED_BYTE, 0, 0);

		// Se selecciona el VBO de colores y se hace que ColorPointer apunte a él:

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		glNormalPointer(GL_FLOAT, 0, 0);

        // Se selecciona el VBO de índices y se llama a glDrawElements(), que lo usa implícitamente:

        glBindBuffer    (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_VBO]);
        glDrawElements  (GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
    }

}
