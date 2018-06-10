/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#include <cassert>
#include <string>
#include "myScene.hpp"
#include "View.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Input.hpp"

using namespace sf;
using namespace oglsl;

int main ()
{
    shared_ptr<Window> window = make_shared<Window>(VideoMode(800, 600), "OpenGL Scene loader", Style::Default, ContextSettings(32));

    window->setVerticalSyncEnabled (true);

	// Init Glew after OpenGL context is created

    GLenum glew_initialization =  glewInit ();

    assert(glew_initialization == GLEW_OK);

	//Inicialización del grafo de escena

	shared_ptr < myScene > scene(new myScene);
	scene->resize(800, 600);

	Input input(window);

    // Se ejecuta el bucle principal:

    bool running = true;

    do
    {
		Input::InputData input_data = input.check();

		if (input_data->at(Input::close))
			running = false;

		if (input_data->at(Input::resize).as_bool())
		{
			Vector2u window_size = window->getSize();
			 scene->resize(window_size.x, window_size.y);
		}

		scene->processInput(input_data);
		scene->update();
		scene->render ();

        window->display ();
    }
    while (running);

    return (EXIT_SUCCESS);
}
