/*

Author: Daniel Fernández
Date:	02/06/2018

*/

#pragma once

#include "Scene.hpp"
#include "Elevation_Mesh.hpp"
#include "Model.hpp"

using namespace std;

namespace oglsl
{
	/// Custom Scene for this specific example.
	/// Contains the different customizable elements of the scene.
	class myScene : public Scene
	{
		float angle;

	public:

		myScene();

		void processInput(Input::InputData input_data) override;
		void update() override;
	};
}
