/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/texture.h"

///
#include "GL_handle.h"


namespace GL {

/**
 * @brief 
 * 
 */
template <GLenum target>
class GL_texture_base 
: public texture 
, public GL_handle {
public:
  GL_texture_base() 
	{
		glGenTextures(1, &handle_);
		glBindTexture(target, handle_);		

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	}
	virtual ~GL_texture_base()
	{
		if (is_validate())
			glDeleteTextures(1, &handle_);
	}

public:
	void bind() override
	{
		//__method__

		glBindTexture(target, handle_);		
	}
};


/**
 * @brief 
 * 
 */
template <GLenum target = GL_TEXTURE_2D, GLint format = GL_RGB>
class GL_texture_ 
: public GL_texture_base<target> {
public:
	void texImage(int level, size_t width, size_t height, const void* pixels)
	{
		//__method__

		size::x = width; 
		size::y = height;

		glBindTexture(target, GL_handle::handle_);		
		glTexImage2D(target,
								 0,
								 format,
								 width,
								 height,
								 0,
								 format,
								 GL_UNSIGNED_BYTE,
								 pixels);
	}
};

/**
 * @brief 
 * 
 */
template <>
class GL_texture_<GL_TEXTURE_2D, GL_RGBA> 
: public GL_texture_base<GL_TEXTURE_2D> {
public:
	void texImage(int level, size_t width, size_t height, const void* pixels)
	{
		size::x = width; 
		size::y = height;

		glBindTexture(GL_TEXTURE_2D, GL_handle::handle_);
		glTexImage2D(GL_TEXTURE_2D,
								 0,
								 GL_RGBA,
								 width,
								 height,
								 0,
								 GL_RGBA,
								 GL_UNSIGNED_BYTE,
								 pixels);
	}
};


/**
 *
 */
template <>
class GL_texture_<GL_TEXTURE_2D, GL_LUMINANCE>
: public GL_texture_base<GL_TEXTURE_2D> {
public:

	void texImage(int level, size_t width, size_t height, const void* pixels)
	{
		//__method__

		size::x = width;
		size::y = height;

		glBindTexture(GL_TEXTURE_2D, GL_handle::handle_);
		glTexImage2D(GL_TEXTURE_2D,
								 0,
								 GL_RED,
								 width,
								 height,
								 0,
								 GL_RED,
								 GL_UNSIGNED_BYTE,
								 pixels);
	}
};

};//GL