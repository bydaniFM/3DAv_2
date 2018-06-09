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
		float helix_angle;

	public:

		myScene();

		void processInput(Input::InputData input_data) override;
		void update() override;
	};
}
