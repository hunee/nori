/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "ui/frame_rect.h"

namespace GL::ui {

class anchor
: public owner_ptr {
public:

unsigned int align_;// = GL::ALIGN_RIGHT | GL::ALIGN_BOTTOM;

anchor()
{
	//__method__
}

GL::point get_align(unsigned int align, const GL::rect& rect, const GL::size& size)
{
	GL::point pos;

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

//void _tick(double dt) override
void align()
{
	//__method__

	//owner
	GL::rect rect;

	auto o = owner<GL::ui::frame_rect>();
	if (o) 
	{
		///frame_rect
		auto fr = o->owner<GL::ui::frame_rect>();
		if (fr) 
			rect = fr->rect_;
		else
		{
			// framebuffer
			auto fb = GL_framebuffer::get();
			auto right = fb->width()-4;
			auto bottom = fb->height()-4;

			rect = GL::rect(4,4, right, bottom);
		}

		auto pos = get_align(align_, rect, GL::size(o->rect_.right, o->rect_.bottom));

		o->transform_.x = pos.x;
		o->transform_.y = pos.y;
	}
}

};

};//GL::ui


