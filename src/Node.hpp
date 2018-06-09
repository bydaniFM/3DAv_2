/*

Author: Daniel Fernández
Date:	30/05/2018

*/

#pragma once

#include <map>
#include <vector>
#include <memory>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective

using namespace std;

namespace oglsl
{
	/// Represents an object in the scene graph
	class Node
	{
		map < string, shared_ptr < Node > > children;

	protected:

		glm::mat4 transform;

	public:

		Node() = default;
		virtual ~Node() = default;

		/// Renders child nodes
		virtual void render(const glm::mat4 & parent_model_view)
		{
			for (auto & child : children)
			{
				child.second->render(parent_model_view);
			}
		}

		/// Updates child nodes
		virtual void update()
		{
			for (auto & child : children)
			{
				child.second->update();
			}
		}

		/// Adds a new child to this node
		void addChild(string name, shared_ptr<Node> child)
		{
			children[name] = child;
		}

		/// Returns a map with this node's children
		map < string, shared_ptr < Node > > getChildren()
		{
			return children;
		}

		/// Displaces the current transform
		void move(const glm::vec3 & displacement)
		{
			transform = glm::translate(transform, displacement);
		}

		/// Rotates transform around x axis
		void rotate_around_x(float angle)
		{
			transform = glm::rotate(transform, angle, glm::vec3(1, 0, 0));
		}
		/// Rotates transform around y axis
		void rotate_around_y(float angle)
		{
			transform = glm::rotate(transform, angle, glm::vec3(0, 1, 0));
		}
		/// Rotates transform around z axis
		void rotate_around_z(float angle)
		{
			transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
		}

		/// Scales the transform in all axes
		void scale(float scale)
		{
			transform = glm::scale(transform, glm::vec3(scale, scale, scale));
		}

		// ...

	};
}
