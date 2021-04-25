/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/2d/renderer.h"

namespace GL::_3d {

/**
 * @brief 
 * 
 */
class mesh_renderer : public ICLASS(renderer) {
public:
	mesh_renderer()
	{
  //CLOGF();		

	vb_ = std::make_unique<GL_buffer_<V2F_C4B, GL_ARRAY_BUFFER, GL_TRIANGLE_STRIP, GL_WRITE_ONLY>>(4);
	shader_ = asset_manager::get()->import<GL::shader>(asset_path("box.shader.xml"));
	}

	virtual ~mesh_renderer() {}

public:
	rect rect_;

	unsigned int highlight_color_;
	unsigned int dark_color_;
	unsigned int background_color_;

public:
	//abgr = 0x00BBGGRR
	void draw_rect(const rect& rect, unsigned int color = 0xffffffff)
	{

/**
 * OpenGL coordnate
 *
 (pos, uv)
 (-1,1 0,1)         (1,1 1,1)
 +(0)-----------+(2)
 |              |
 |              |
 |              |
 |              |
 |              |
 |              |
 +(1)-----------+(3)
 (-1,-1 0,0)       (1,-1 1,0)

	x = n
	y = 1 - n; flip_y
*/
	//backgroundColor = 0x00BBGGRR

	auto fb = GL_framebuffer::get();

  float rx = 0;//rect.x;//fb->rhw_x(rect.x);
	float ry = 0;//rect.y;//fb->rhw_y(rect.y);
	float rw = rect.z-rect.x;//fb->rhw_x(rect.z);
	float rh = rect.w-rect.y;//fb->rhw_y(rect.w);

//	float tx = 0;//rect.left / right;
//	float ty = 1;//1-(rect.top / bottom);
//	float tw = 1;//(rect.left + rect.right) / right;
//	float th = 0;//1-((rect.top + rect.bottom) / bottom);

	auto verts = static_cast<V2F_C4B*> (vb_->map());
	verts[0].position = float2(rx, ry);
	verts[1].position = float2(rx, rh);
	verts[2].position = float2(rw, ry);
	verts[3].position = float2(rw, rh);

	//verts[0].tex0 = float2(tx, ty);
	//verts[1].tex0 = float2(tx, th);
	//verts[2].tex0 = float2(tw, ty);	
	//verts[3].tex0 = float2(tw, th);

//color = 0xffffffff;
//alpha = 0;

	verts[0].color = color;
	verts[1].color = color;
	verts[2].color = color;
	verts[3].color = color;
	
	vb_->unmap();

GL::float3 pos(rect.x, rect.y, 0.0f);

GL::float4x4 model_;
model_.translation(pos);

try {
		(*shader_)["box_p0"]->use();
		
		(*shader_)["box_p0"]->set("projection", cc_->projection_);
		(*shader_)["box_p0"]->set("view", cc_->view_);

    (*shader_)["box_p0"]->set("model", model_);
}
catch (std::exception& e) {
	COUT << e.what() << ENDL;
}		

	ICLASS(renderer)::draw();
}


};

};//GL::_3d

