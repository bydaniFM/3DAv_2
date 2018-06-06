/*

Author: Daniel Fernández
Date:	02/06/2018

*/

#include "myScene.hpp"

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

using namespace glm;

namespace example
{
	myScene::myScene()
		/*:
		scene()*/
	{
		//scene = make_shared<Scene>();

		add(make_shared<Elevation_Mesh>(500, 500, 20.f, 20.f, 2.f));
		add(make_shared<Model>((char*)"..\\..\\assets\\mill.obj"));
	}

	void myScene::processInput(Input::InputData input_data)
	{
		if (input_data->at(Input::button_forward))
		{
			cout << "Moving camera forward" << endl;
		}

		//cout << "Mouse pos: " << input_data->at(Input::axis_x) << " " << input_data->at(Input::axis_y) << endl;
		//cout << input_data->at(Input::button_pan) << endl;

		//glm::mat4 model_view_matrix;



		//Input transformation
		/*if (input_data->at(Input::button_pan)) {
			if (input_data->at(Input::axis_x) || input_data->at(Input::axis_y))
			{
				model_view_matrix = glm::rotate(model_view_matrix, 1.f, glm::vec3(input_data->at(Input::axis_y), input_data->at(Input::axis_x), 0.f));
			}
		}
		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.f, 0.f, -input_data->at(Input::button_forward).as_float() * 1.0f));
		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.f, 0.f, input_data->at(Input::button_back).as_float() * 1.0f));


		glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(glm::inverse(model_view_matrix)));*/
	}
}