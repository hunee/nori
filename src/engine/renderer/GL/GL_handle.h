/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "GL_ext.h"

namespace GL {
	
/**
 * @brief 
 * 
 */
class GL_handle {
public:
	GL_handle()
	: handle_(GL_INVALID_HANDLE_VALUE)
	{
	}
  virtual ~GL_handle()
  {
    handle_ = GL_INVALID_HANDLE_VALUE;
  }

public:
	int is_validate() 
	{ 
		return (handle_ != GL_INVALID_HANDLE_VALUE); 
	}

	GLuint handle() 
	{ 
		return handle_; 
	}

protected:
	GLuint handle_;
};


};//GL