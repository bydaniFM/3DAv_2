/*

Author: Daniel Fernández
Date:	02/06/2018

*/

#pragma once

#include "Scene.hpp"
#include "Elevation_Mesh.hpp"
#include "Model.hpp"

using namespace std;

namespace example
{
	class myScene : public Scene
	{
		shared_ptr < Scene > scene;

	public:

		myScene()
		{
			scene = make_shared<Scene>();

			scene->add(make_shared<Elevation_Mesh>(500, 500, 20.f, 20.f, 2.f));
			scene->add(make_shared<Model>((char*)"..\\..\\assets\\mill.obj"));
		}

		void processInput(Input::InputData input_data) override;
	};
}
