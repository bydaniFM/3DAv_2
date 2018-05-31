/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

#include <memory>
#include <map>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

using namespace std;
using namespace sf;

namespace example
{
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
			button_pan
		};

		typedef shared_ptr<map<input_type, float>> InputData;

	private:

		shared_ptr<Window> window;
		Event event;

		InputData input_data;

		Vector2i mouse_pos;
		Vector2i prev_mouse_pos;

		float mouse_sensibility;

	public:

		Input(shared_ptr<Window> window)
			:
			window(window)
		{
			input_data = make_shared<map<input_type, float>>();

			(*input_data)[close] = 0;
			(*input_data)[resize] = 0;
			(*input_data)[axis_x] = 0;
			(*input_data)[axis_y] = 0;
			(*input_data)[button_forward] = 0;
			(*input_data)[button_pan] = 0;

			mouse_pos = Vector2i();
			prev_mouse_pos = Vector2i();

			mouse_sensibility = 100;
		}

		InputData check()
		{
			bool mouse_moved = false;

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
						(*input_data)[resize] = true;
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

						break;
					}

					case Event::KeyReleased:
					{
						if (event.key.code == sf::Keyboard::W)
						{
							(*input_data)[button_forward] = false;
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

			return input_data;
		}

		InputData getInput()
		{
			return input_data;
		}
	};
}
