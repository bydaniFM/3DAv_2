/*

Author: Daniel Fernández
Date:	02/06/2018

*/

#include "myScene.hpp"

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

using namespace glm;

namespace oglsl
{
	myScene::myScene()
	{
		//scene = make_shared<Scene>();

		add("terrain", make_shared<Elevation_Mesh>(50, 50, 20.f, 20.f, 2.f, shaders["default"]));
		add("mill",    make_shared<Model>((char*)"..\\..\\assets\\mill.obj", shaders["default_lit"], glm::vec3(1, 0, 0)));
		add("plane",   make_shared<Model>((char*)"..\\..\\assets\\spitfire.FBX", shaders["default_lit"]));

		getObject("terrain")->move(glm::vec3(0, -2000, 1000));
		getObject("terrain")->scale(500.f);

		getObject("mill")->addChild("mill_blades", make_shared<Model>((char*)"..\\..\\assets\\blades.obj", shaders["default_lit"], glm::vec3(0, 1, 0)));
		getObject("mill")->scale(0.3f);
		getObject("mill")->move(glm::vec3(-70, 0, 0));

		getObject("plane")->move(glm::vec3(0, -180, 400));
		getObject("plane")->rotate_around_x(-90);

		camera.move(glm::vec3(0.f, 10.f, -60.f));

		angle = 0.1f;
	}

	void myScene::update()
	{
		getObject("plane")->rotate_around_z(angle);

		Scene::update();
	}

	void myScene::processInput(Input::InputData input_data)
	{
		if (input_data->at(Input::button_forward))
		{
			cout << "Moving camera forward" << endl;
		}

		//cout << "Mouse pos: " << input_data->at(Input::axis_x) << " " << input_data->at(Input::axis_y) << endl;
		//cout << input_data->at(Input::button_pan) << endl;

		float angle_delta_x = 0;
		float angle_delta_y = 0;
		
		//Input transformation
		if (input_data->at(Input::button_pan)) {
			if (input_data->at(Input::axis_x) || input_data->at(Input::axis_y))
			{
				//camera.rotate(glm::rotate(camera.get_model_view(), 1.f, glm::vec3(input_data->at(Input::axis_y), input_data->at(Input::axis_x), 0.f)));
				/*camera.rotate
				(
					glm::lookAt
					(
						glm::vec3(camera.get_location().x, camera.get_location().y, camera.get_location().z),
						glm::vec3(camera.get_target().x, camera.get_target().y, camera.get_target().z),
						glm::vec3(0, 1, 0)
					) + 0.001f
				);*/
				angle_delta_x = input_data->at(Input::axis_x).as_float() * 0.02f;
				angle_delta_y = input_data->at(Input::axis_y).as_float() * 0.02f;
			}
		}

		angle_around_x += angle_delta_x;
		angle_around_y -= angle_delta_y;

		//Apply camera rotation
		glm::mat4 camera_rotation;

		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_x), glm::vec3(0.f, 1.f, 0.f));
		camera_rotation = glm::rotate(camera_rotation, glm::degrees(angle_around_y), glm::vec3(1.f, 0.f, 0.f));

		camera.set_target(0, 0, -1);
		camera.rotate(camera_rotation);

		//Camera movement

		float movement = input_data->at(Input::button_forward).as_float() + input_data->at(Input::button_back).as_float();

		/*camera.move(glm::vec3
		(
			camera.get_target().x,
			camera.get_target().y,
			camera.get_target().z
		) + glm::vec3(1,1,1) * movement);*/

		camera.move(glm::vec3(0.f, 0.f, input_data->at(Input::button_forward).as_float()));
		camera.move(glm::vec3(0.f, 0.f,  -input_data->at(Input::button_back).as_float()));
	}
}
