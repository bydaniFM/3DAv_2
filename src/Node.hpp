/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

#include <vector>;
#include <memory>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective

using namespace std;

namespace example
{
	class Node
	{
		vector < shared_ptr < Node > > children;

		glm::mat4 transform;

	public:

		Node() = default;

		virtual void render(const glm::mat4 & parent_model_view)
		{
			for (auto & child : children)
			{
				child->render(parent_model_view);
			}
		}

		virtual void update()
		{
			for (auto & child : children)
			{
				child->update();
			}
		}

		void move(const glm::vec3 & displacement)
		{
			transform = glm::translate(transform, displacement);
		}

		void rotate_around_x(float angle)
		{
			transform = glm::rotate(transform, angle, glm::vec3(1, 0, 0));
		}
		void rotate_around_y(float angle)
		{
			transform = glm::rotate(transform, angle, glm::vec3(0, 1, 0));
		}
		void rotate_around_z(float angle)
		{
			transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
		}

		// ...

	};
}
