/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

#include <memory>
#include <vector>

#include "Node.hpp"

using namespace std;

namespace example
{
	class Scene
	{
		vector<shared_ptr<Node>> graph;

	public:

		Scene()
		{
		}

		void add(shared_ptr<Node> node)
		{
			graph.push_back(node);
		}

		void render()
		{
			for (auto node : graph)
			{
				node->render();
			}
		}
	};
}