/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "font.h"

#include "renderer/GL/GL_texture.h"

namespace GL::_2d {

static unsigned char __sys_fontdata[] = {
#include "fontdata.inl"
};

class bitmap_font : public font {
private:
//font
size_t bitmap_width_ =	8;
size_t bitmap_height_ = 9;

size_t texture_width_ =	128;
size_t texture_height_ = 128;

unsigned char* fontdata_;

public:
	bitmap_font()
	: fontdata_(__sys_fontdata)
{
	/**
	 * Texture
	 */
	texture_ = std::make_shared<GL_texture_<GL_TEXTURE_2D, GL_LUMINANCE>>();
	texture_->texImage(0, texture_width_, texture_height_, fontdata_);
}

public:
	std::shared_ptr<font_cache> code(unsigned int c) override
	{
		auto fc = get(c);
		if (fc == nullptr)
		{
			fc = std::make_shared<font_cache>();
			fc->tx = make_left(c);
			fc->ty = make_top(c);
			fc->tw = make_right(c);
			fc->th = make_bottom(c);
			
			fc->bitmap.x = 0;
			fc->bitmap.y = 0;
			fc->bitmap.z = width();
			fc->bitmap.w = height();
			
			add(c, fc);
		}
		
		return fc;
	}

/**
 * property
 */
public:	
	const size_t width() const override
	{
		return bitmap_width_;
	}
	const size_t height() const override
	{
		return bitmap_height_;
	}

private:
	float make_left(unsigned int c) const
	{
		return (float)(((unsigned int) c % 16) * width()) / (float) texture_width_;
	}
	float make_right(unsigned int c) const
	{
		return (float)((((unsigned int) c % 16) * width()) + width()) / (float) texture_width_;
	}
	float make_top(unsigned int c) const
	{
		return (float)(((((unsigned int) c / 16) - 2) * height()) + 1) / (float) texture_height_;
	}
	float make_bottom(unsigned int c) const 
	{
		return (float)(((((unsigned int) c / 16) - 2) * height()) + height() + 1) / (float) texture_height_;
	}
	
};


};//GL::_2d