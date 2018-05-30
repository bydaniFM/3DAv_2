/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

namespace example
{
	class Node
	{
		//Scene & scene;

	public:

		/*Node(int cols, int rows, float width, float depth, float elevation)
			:
			Elevation_Mesh(cols, rows, width, depth, elevation)
		{
		}

		Node(char *path)
			:
			Model(path)
		{
		}*/

		/*Node(Scene & scene)
			:
			scene(scene)
		{
		}*/

		Node() {}

		virtual void render()
		{
		}
	};
}
