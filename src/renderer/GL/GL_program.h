/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/program.h"

#include "GL_shader.h"

namespace GL {

class GL_program
: public program
, public GL_handle
, public std::vector<std::unique_ptr<GL_shader>> {
public:
	~GL_program()
	{
	if (is_validate())
	{
		glDeleteProgram(handle_);
		glUseProgram(0);
	}	
}

public:
	void link()
{
	//__method__
	
	handle_ = glCreateProgram();


  /**
	 * Bind attribute locations
   * this needs to be done prior to linking
	 */

	/*
	glBindAttribLocation(handle_, ATTRIB_POSITION, "POSITION");
	glBindAttribLocation(handle_, ATTRIB_NORMAL, "NORMAL");
	glBindAttribLocation(handle_, ATTRIB_COLOR, "COLOR");
	glBindAttribLocation(handle_, ATTRIB_TEXCOORD0, "TEXCOORD0");
	glBindAttribLocation(handle_, ATTRIB_TEXCOORD1, "TEXCOORD1");
	glBindAttribLocation(handle_, ATTRIB_TANGENT, "TANGENT");
	glBindAttribLocation(handle_, ATTRIB_BINORMAL, "BINORMAL");
	glBindAttribLocation(handle_, ATTRIB_BONEWEIGHT, "BONEWEIGHT");
	glBindAttribLocation(handle_, ATTRIB_BONEINDEX, "BONEINDEX");
	*/

	/**
	 * Attach shader to program
	 */
	auto v = dynamic_cast<std::vector<std::unique_ptr<GL_shader>>*>(this);
	for (auto&& shader : *v)
	{
		//COUT << "shader: " << shader->handle() << ENDL;
	
		glAttachShader(handle_, shader->handle());
	}

#ifdef __GL_GEOMETRY_SHADER_EXT
#if defined (CGL_VERSION_1_3)

#else
#if !defined (__TARGET_EGL__)
	/**
	 * Bind geometry shader
	 */
	glProgramParameteriEXT(_program, GL_GEOMETRY_INPUT_TYPE_EXT, GL_LINES);
	glProgramParameteriEXT(_program, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_LINE_STRIP);
	
	int temp;
	glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &temp);
	glProgramParameteriEXT(_program, GL_GEOMETRY_VERTICES_OUT_EXT, temp);
#endif //__TARGET__EGL__
#endif //CGL_VERSION_1_3
#endif //__GL_GEOMETRY_SHADER_EXT
	

	/**
	 * Link
	 */
	glLinkProgram(handle_);
	
	GLint linked;
	glGetProgramiv(handle_, GL_LINK_STATUS, &linked);
	if (linked == 0)
	{
		GLsizei length;
		char infoLog[2048];
		glGetProgramInfoLog(handle_, sizeof(infoLog), &length, infoLog);
		//glDeleteProgram(handle_);

    //throw ...
		char e[255];
		sprintf(e, "ERROR: GL_LINK_STATUS: %s", infoLog);

		throw std::runtime_error(e);	
	}

/*	
	const GLint v1 = glGetAttribLocation(handle_, "POSITION");
  const GLint v2 = glGetAttribLocation(handle_, "COLOR");
  const GLint v3 = glGetAttribLocation(handle_, "TEXCOORD0");

COUT << v1 << ENDL;
COUT << v2 << ENDL;
COUT << v3 << ENDL;
*/

	/**
	 * Validate
	 */
	glValidateProgram(handle_);
	
	GLint validated;
	glGetProgramiv(handle_, GL_VALIDATE_STATUS, &validated);
	if (validated == 0)
	{
		GLsizei length;
		char infoLog[2048];
		glGetProgramInfoLog(handle_, sizeof(infoLog), &length, infoLog);
		//glDeleteProgram(handle_);
			
    //throw ...
		char e[255];
		sprintf(e, "ERROR: GL_VALIDATE_STATUS: %s", infoLog);

		throw std::runtime_error(e);	
	}


	/**
	 *
	 */
	glUseProgram(handle_);

	
	/**
	 * Bind Sampler
	 */
	/*char TEX[PATH_MAX];
	for (int n=0; n<MAX_TEXTURE_IMAGE_UNITS; n++)
	{
		sprintf(TEX, "TEX%d", n);
	 
		GLint location = glGetUniformLocation(handle_, TEX);
		if (location != GL_INVALID_HANDLE_VALUE)
			glUniform1i(location, n);
	}*/
}

	void use() override
	{
		glUseProgram(handle_);
	}


	//
	void bind() override
	{
		//__method__

		/**
		 * bind shader program
		 */
		glUseProgram(handle_);

		program::bind();
	}

template <typename V = float>
void set(const std::string& name, V v)
{
	glUniform1f(glGetUniformLocation(handle_, name.c_str()), v);	
}

template <>
void set(const std::string& name, int v)
{
	glUniform1i(glGetUniformLocation(handle_, name.c_str()), v);	
}

template <>
void set(const std::string& name, unsigned int v)
{
	GLint location = glGetUniformLocation(handle_, name.c_str());
	if (location != GL_INVALID_HANDLE_VALUE) {
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GL_TEXTURE_2D, v);
	}
}

};

};//GL
