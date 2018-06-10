/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

#include <map>
#include <memory>
//#include <variant>
#include "Variant.hpp"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

using namespace std;
using namespace sf;

namespace oglsl
{
	/// Controls user input
	class Input
	{
	public:

		enum input_type
		{
			close,
			resize,
			axis_x,
			axis_y,
			button_forward,
			button_back,
			button_pan
		};

		typedef shared_ptr < map < input_type, Variant > > InputData;

	private:

		shared_ptr<Window> window;
		Event event;

		InputData input_data;

		Vector2i mouse_pos;
		Vector2i prev_mouse_pos;

		float mouse_sensibility;

	public:

		/// Initialises inputs
		Input(shared_ptr<Window> window)
			:
			window(window)
		{
			input_data = make_shared < map < input_type, Variant > >();

			(*input_data)[close] = false; // = false;
			(*input_data)[resize] = false; // = false;
			(*input_data)[axis_x] = 0.f; // = 0.f;
			(*input_data)[axis_y] = 0.f; // = 0.f;
			(*input_data)[button_forward] = false; // = false;
			(*input_data)[button_back] = false; // = false;
			(*input_data)[button_pan] = false; // = false;

			mouse_pos = Vector2i();
			prev_mouse_pos = Vector2i();

			mouse_sensibility = 100;
		}

		/// Checks for all inputs, saves them in input_data and returns it
		InputData check()
		{
			bool mouse_moved = false;
			bool did_resize = false;

			while (window->pollEvent(event))
			{
				switch (event.type)
				{
					case Event::Closed:
					{
						(*input_data)[close] = true;
						break;
					}

					case Event::Resized:
					{
						did_resize = true;
						break;
					}

					case Event::MouseMoved:
					{
						mouse_moved = true;

						mouse_pos = sf::Mouse::getPosition();
						(*input_data)[axis_x] = glm::clamp(mouse_sensibility * (mouse_pos.x - prev_mouse_pos.x) / window->getSize().x, -1.f, 1.f);
						(*input_data)[axis_y] = glm::clamp(mouse_sensibility * (mouse_pos.y - prev_mouse_pos.y) / window->getSize().y, -1.f, 1.f);
						prev_mouse_pos = mouse_pos;
					}

					case Event::KeyPressed:
					{
						if (event.key.code == sf::Keyboard::W)
						{
							(*input_data)[button_forward] = true;
						}
						else if (event.key.code == sf::Keyboard::S)
						{
							(*input_data)[button_back] = true;
						}

						break;
					}

					case Event::KeyReleased:
					{
						if (event.key.code == sf::Keyboard::W)
						{
							(*input_data)[button_forward] = false;
						} 
						else if (event.key.code == sf::Keyboard::S)
						{
							(*input_data)[button_back] = false;
						}

						break;
					}

					case Event::MouseButtonPressed:
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							(*input_data)[button_pan] = true;
						}
						break;
					}

					case Event::MouseButtonReleased:
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							(*input_data)[button_pan] = false;
						}
						break;
					}
				}
			}

			if (!mouse_moved)
			{
				(*input_data)[axis_x] = 0.f;
				(*input_data)[axis_y] = 0.f;
			}

			(*input_data)[resize] = did_resize;

			return input_data;
		}

		InputData getInput()
		{
			return input_data;
		}
	};
}
