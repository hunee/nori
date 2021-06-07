/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "frame_rect.h"

namespace GL::ui {

/**
 * @brief 
 * 
 */
class panel 
: public frame_rect {
public:

public:

void _began() override
{
	frame_rect::_began();
}

void _tick(double dt) override
{
	frame_rect::_tick(dt);

	///
	float fps = 120;
	auto fb = GL_framebuffer::get();

	//transform_.x += dt * fps;
	//if (transform_.x2 > fb->width())
//		transform_.x = 0;

}

void _draw() override
{
		///__method__

	frame_rect::_draw();
}

};

};//GL::ui

