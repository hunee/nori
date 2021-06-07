/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL {

/**
 * @brief 
 * 
 */
class texture : public GL::size, public __type_info<texture> {
public:
	virtual ~texture()
	{
		//__method__		
	}

public:
	virtual void bind() {};
	virtual void texImage(int level, size_t width, size_t height, const void* pixels) {};
};

};//GL

