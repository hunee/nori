/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL {

class camera {
public:
	GL::float4x4 projection_;
	GL::float4x4 view_;

camera()
{
// 1 | 2
// --+--
// 3 | 4
//
// 1:
// 2:
// 3:
// 4: 0,w,h,0
auto fb = GL_framebuffer::get();
projection_.ortho(0,fb->width(), fb->height(),0, -1024.0f, 1024.0f);
//projection_.perspective_fovy(45.0f, (float)fb->width() / (float)fb->height(), 0.1f, 2000.0f);
//view_.identity();

//GL::float3 vpos(0,0, -500.f);
//view_.translation(vpos);

}

void ortho()
{
	auto fb = GL_framebuffer::get();
	w_ = fb->width();
	h_ = fb->height();

	projection_.ortho(0,w_, h_,0, -1024.0f, 1024.0f);
}

float w_,h_;
void _tick(double dt) 
{
	auto fb = GL_framebuffer::get();
	if (w_ != fb->width() || h_ != fb->height())
	{
		w_ = fb->width();
		h_ = fb->height();

		projection_.ortho(0,w_, h_,0, -1024.0f, 1024.0f);	
	}
};

};

};//GL

