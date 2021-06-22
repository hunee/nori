/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "frame_rect.h"

namespace GL::hud {

/**
 * @brief 
 * 
 */
class anchor
: public frame_rect {
public:

public:
	unsigned int align_ = GL::ALIGN_RIGHT | GL::ALIGN_BOTTOM;
	GL::size size_;

public:

void began()
{
	frame_rect::began();

	size_ = GL::size(200,200);
};

	GL::point get_align(uint align, const GL::rect& rect, const GL::size& size)
	{
		point pos;

		if (align & GL::ALIGN_LEFT)
			pos.x = rect.left;
		else if (align & GL::ALIGN_RIGHT)
			pos.x = rect.right - size.width;

		if (align & GL::ALIGN_TOP)
			pos.y = rect.top;
		else if (align & GL::ALIGN_BOTTOM)
			pos.y = rect.bottom - size.height;

		return pos;
	}

	void tick(double dt)
	{
		frame_rect::tick(dt);

		if (dt > 0.1f)
			dt = 0.1f;

		float fps = 120;

/*
	_frameIndex += dt * _fps;
	
	if (_frameCount <= 1)
		_frameIndex = 0;
	else
	{
		// wrap
		_frameIndex -= (int)(_frameIndex / (_frameCount-1)) * (_frameCount-1);
	}
*/
	auto fb = GL_framebuffer::get();

	//transform_.x += dt * fps;
	//if (transform_.x2 > fb->width())
	//	transform_.x = 0;


    //owner
    GL::rect rect;
    auto owner = node_ptr()->owner(); //component, parent
    if (owner)
    {
      auto o = std::dynamic_pointer_cast<frame_rect>(owner);
      if (o) 
        rect = o->rect_;
    }
		else
		{
			// framebuffer
			auto fb = GL_framebuffer::get();
			auto right = fb->width()-4;
			auto bottom = fb->height()-4;

			rect = GL::rect(4,4, right, bottom);
		}

///rect_ = rect;
///
	
	auto apos = get_align(align_, rect, size_);

	transform_.x2 += apos.x;
	transform_.y2 += apos.y;
}

	void draw()
	{
		//__method__

		frame_rect::draw();
	}
};

};//GL::hud

