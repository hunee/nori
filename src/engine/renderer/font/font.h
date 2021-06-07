/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/texture.h"

namespace GL::_2d {

struct font_data {
	GL::size bitmap;
	GL::size texture;	
	unsigned char* data;
};

struct font_cache {
	float tx, ty, tw, th;
	GL::rect bitmap;
};


/**
 * @brief 
 * 
 */
class font 
: std::map<unsigned int, std::shared_ptr<font_cache>> {
public:
	virtual ~font() {}
	
public:
	void add(unsigned int c, std::shared_ptr<font_cache> fc)
	{
		auto ret = insert({c, nullptr});
		if (ret.second == true)
		{
			ret.first->second = fc;
		}
	}

	std::shared_ptr<font_cache> get(unsigned int c)
	{
		auto it = find(c);
		if (it != end())
			return it->second;
		
		return nullptr;
	}

public:	
	virtual std::shared_ptr<font_cache> code(unsigned int c) =0;

	virtual const size_t width() const =0;
	virtual const size_t height() const =0;

public:
	std::shared_ptr<GL::texture> texture_;
	const std::shared_ptr<GL::texture>& texture() const
	{
		return texture_;
	}
};


};//GL::_2d