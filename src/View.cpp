
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "View.hpp"
#include <iostream>
#include <cassert>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace example
{

    using namespace std;

    const string View::vertex_shader_code =
		"#version 330\n"
		""
		"uniform mat4 model_view_matrix;"
		"uniform mat4 projection_matrix;"
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		""
		"void main()"
		"{"
		"   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
		"}";
      /*"void main()"
        "{"
        "    vec3  normal          = normalize (gl_NormalMatrix * gl_Normal);"
        "    vec3  light_direction = normalize (vec3(gl_LightSource[0].position));"
        "    float intensity       = max (dot (normal, light_direction), 0.0);"
        ""
        "    gl_FrontColor = intensity * gl_LightSource[0].diffuse * gl_Color;"
        "    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;"
        "}";*/
	  /*"void main()"
		"{"
		"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
		"}";*/

    const string View::fragment_shader_code =
		"#version 330\n"
		""
		"out vec4 fragment_color;"
		""
		"void main()"
		"{"
		"    fragment_color = vec4(1.0, 1.0, 1.0, 1.0);"
		"}";
        /*"void main()"
        "{"
        "    gl_FragColor = gl_Color;"
		"    //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
        "}";*/

    View::View(int width, int height, shared_ptr<Scene> scene)
    :
        angle(0),
		scene(scene)
    {
        // Se habilita el backface culling, una luz y materiales básicos:

        glEnable (GL_CULL_FACE);
		glEnable (GL_DEPTH_TEST);

        // Se inicializan los parámetros relativos a la iluminación:

        light_direction[0] = 0.1f;
        light_direction[1] = 100.0f;
        light_direction[2] = 1.0f;
        light_direction[3] = 0.0f;



        // Se compilan y se activan los shaders:

        GLuint program_id = compile_shaders ();

        glUseProgram (program_id);

		model_view_matrix_id = glGetUniformLocation(program_id, "model_view_matrix");
		projection_matrix_id = glGetUniformLocation(program_id, "projection_matrix");

		resize (width, height);
    }

    void View::update (Input::InputData input_data)
    {
        angle += 0.5f;

		if (input_data->at(Input::button_forward))
		{
			cout << "Moving camera forward" << endl;
		}

		cout << "Mouse pos: " << input_data->at(Input::axis_x) << " " << input_data->at(Input::axis_y) << endl;

		glm::mat4 model_view_matrix;

		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.f, 0.f, -6.f));
		model_view_matrix = glm::rotate(model_view_matrix, 10.f, glm::vec3(1.f, 0.f, 0.f));
		model_view_matrix = glm::rotate(model_view_matrix, angle, glm::vec3(0.f, 1.f, 0.f));
		model_view_matrix = glm::scale(model_view_matrix, glm::vec3(0.01f, 0.01f, .01f));
		model_view_matrix = glm::rotate(model_view_matrix, 10.f, glm::vec3(input_data->at(Input::axis_x), input_data->at(Input::axis_y), 0));

		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

    }

    void View::render ()
    {
		glClearColor (.4f, .4f, .4f, 1.f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		/*elevation_mesh.render ();
		model_example.render();*/

		scene->render();
    }

    void View::resize (int width, int height)
    {
        glViewport (0, 0, width, height);

		glm::mat4 projection_matrix = glm::perspective(20.f, GLfloat(width) / height, 1.f, 500.f);

		glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));
    }

    GLuint View::compile_shaders ()
    {
        GLint succeeded = GL_FALSE;

        // Se crean objetos para los shaders:

        GLuint   vertex_shader_id = glCreateShader (GL_VERTEX_SHADER  );
        GLuint fragment_shader_id = glCreateShader (GL_FRAGMENT_SHADER);

        // Se carga el código de los shaders:

        const char *   vertex_shaders_code[] = {          vertex_shader_code.c_str () };
        const char * fragment_shaders_code[] = {        fragment_shader_code.c_str () };
        const GLint    vertex_shaders_size[] = { (GLint)  vertex_shader_code.size  () };
        const GLint  fragment_shaders_size[] = { (GLint)fragment_shader_code.size  () };

        glShaderSource  (  vertex_shader_id, 1,   vertex_shaders_code,   vertex_shaders_size);
        glShaderSource  (fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        // Se compilan los shaders:

        glCompileShader (  vertex_shader_id);
        glCompileShader (fragment_shader_id);

        // Se comprueba que si la compilación ha tenido éxito:

        glGetShaderiv   (  vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (  vertex_shader_id);

        glGetShaderiv   (fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (fragment_shader_id);

        // Se crea un objeto para un programa:

        GLuint program_id = glCreateProgram ();

        // Se cargan los shaders compilados en el programa:

        glAttachShader  (program_id,   vertex_shader_id);
        glAttachShader  (program_id, fragment_shader_id);

        // Se linkan los shaders:

        glLinkProgram   (program_id);

        // Se comprueba si el linkage ha tenido éxito:

        glGetProgramiv  (program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) show_linkage_error (program_id);

        // Se liberan los shaders compilados una vez se han linkado:

        glDeleteShader (  vertex_shader_id);
        glDeleteShader (fragment_shader_id);

        return (program_id);
    }

    void View::show_compilation_error (GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

    void View::show_linkage_error (GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

}
