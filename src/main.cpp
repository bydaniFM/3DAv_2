
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
#include <string>
#include "myScene.hpp"
#include "View.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Input.hpp"

using namespace sf;
using namespace example;

int main ()
{
    shared_ptr<Window> window = make_shared<Window>(VideoMode(800, 600), "OpenGL Examples: Texturing", Style::Default, ContextSettings(32));

    window->setVerticalSyncEnabled (true);

    // Una vez se ha creado el contexto de OpenGL ya se puede inicializar Glew:

    GLenum glew_initialization =  glewInit ();

    assert(glew_initialization == GLEW_OK);

	//Inicialización del grafo de escena

	myScene scene;

    // Una vez se ha inicializado GLEW se puede crear una instancia de View:

    View view(800, 600, make_shared<Scene>(scene));

	Input input(window);

    // Se ejecuta el bucle principal:

    bool running = true;

    do
    {
		Input::InputData input_data = input.check();

		if (input_data->at(Input::close))
			running = false;

		if (input_data->at(Input::resize))
		{
			Vector2u window_size = window->getSize();
			view.resize(window_size.x, window_size.y);
		}

		view.update(input_data);
        view.render ();

        window->display ();
    }
    while (running);

    return (EXIT_SUCCESS);
}
