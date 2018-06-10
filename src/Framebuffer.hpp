/*

Author: Daniel Fernández
Date:	10/06/2018

*/

#pragma once

#include <memory>

#include "Shader_Program.hpp"

namespace oglsl
{
	class Framebuffer
	{
	private:

		std::shared_ptr < Shader_Program > shader;

		static const GLsizei framebuffer_width = 1024;
		static const GLsizei framebuffer_height = 1024;
		
		GLuint framebuffer_id;
		GLuint depthbuffer_id;
		GLuint out_texture_id;

		GLuint triangle_vbo0;
		GLuint triangle_vbo1;

	public:

		Framebuffer(std::shared_ptr < Shader_Program > shader);

		void render(int width, int height);
		void setFramebuffer();

	};
}