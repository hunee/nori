/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "GL_handle.h"

namespace GL {

class GL_shader
: public GL_handle {
public:
	GL_shader(GLenum type, const GLchar* string)
	{
		/**
		 * A couple of defines to make life easier for HLSL users
		 */
		const char * version_string = "#version 330 core";
		const char * shader_strings[3];
		shader_strings[0] = version_string;//glGetShaderLanguageVersion();
		shader_strings[1] = "#define saturate(x) clamp(x,0.0,1.0)\n"
		                    "#define lerp mix\n";
		shader_strings[2] = string;
		
		/**
		 *
		 */
		handle_ = glCreateShader(type);

		glShaderSource(handle_, 3, shader_strings, NULL);
		//glShaderSource(handle_, 1, &string, NULL);
		glCompileShader(handle_);

		GLint compiled = 0;
		glGetShaderiv(handle_, GL_COMPILE_STATUS, &compiled);
		if (compiled == 0)
		{
			GLsizei length;
			glGetShaderiv(handle_, GL_INFO_LOG_LENGTH, &length);

			char infoLog[2048];
			glGetShaderInfoLog(handle_, sizeof(infoLog), &length, infoLog);
			//glDeleteShader(handle_);

			//throw ...
			char e[255];
			sprintf(e, "ERROR: GL_COMPILE_STATUS: %s", infoLog);

			throw std::runtime_error(e);	
		}
	}
	~GL_shader()
	{
		if (is_validate())
		{
			glDeleteShader(handle_);
		}
	}
};


/**
	GL_VERTEX_SHADER;
	GL_FRAGMENT_SHADER;
	GL_GEOMETRY_SHADER_EXT;
*/
template <GLenum type>
class GL_shader_ : public GL_shader {
public:
	GL_shader_(const GLchar* string)
		: GL_shader(type, string)
	{
	}
};

};//GL