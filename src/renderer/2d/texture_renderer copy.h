
/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer.h"

#include "renderer/texture.h"
#include "renderer/GL/GL_texture.h"

/////
#include "tp_member.h"
#include "tp_method.h"

#include "object.h"

#include <functional>

namespace GL::_2d {

class texture_renderer : public ICLASS(renderer) {
public:
	texture_renderer()
	{
  ///__FUNC_YEL__		

	//va_ = std::make_unique<GL_vertex_array>();
	vb_ = std::make_unique<GL_buffer_<V2F_C4B_T2F, GL_ARRAY_BUFFER, GL_TRIANGLE_STRIP, GL_WRITE_ONLY>>(4);
	shader_ = asset_manager::get()->import<GL::shader>(asset_path("sprite.shader.xml"));
}

	texture_renderer(const std::shared_ptr<texture>& tex)
: tex0_(tex)
{
  ///__FUNC_YEL__

	rect_.width = tex->width;
	rect_.height = tex->height;

	//va_ = std::make_unique<GL_vertex_array>();
	vb_ = std::make_unique<GL_buffer_<V2F_C4B_T2F, GL_ARRAY_BUFFER, GL_TRIANGLE_STRIP, GL_WRITE_ONLY>>(4);
  shader_ = asset_manager::get()->import<GL::shader>(asset_path("font.shader.xml"));
}
	virtual ~texture_renderer() { /*__FUNC_YEL__*/ };


private:
	std::unique_ptr<ICLASS(tp_member)<std::shared_ptr<texture>>> pi_;
	std::unique_ptr<ICLASS(tp_member_ptr)> pii_;

	std::unique_ptr<tp_method<void>> pf_;
	std::function<void(int)> f1_;

public:
	std::shared_ptr<texture> tex0_;

	uint color_ = 0xffffffff;
	float alpha_ = 1.0f;
	
	rect rect_;
	bool is_renew_ = true;

public:
	void ddd()
	{
		//__method__
	}

	void ddd_1(int n)
	{
		//__method__
	}
/*
	const node_ * owner()
	{
		//component
		auto p = dynamic_cast <component_*>(this);
		COUT << "pname: " << p->name_ << " type: " << __typeid_name(*p) << " owner: " << p->owner() << ENDL;

		//node
	//	auto o = dynamic_cast <node_*>(p->owner());
//		COUT << "oname: " << o->name_ << " type: " << __typeid_name(*o) << ENDL;	

		//return p->owner();		
//return std::dynamic_pointer_cast<std::shared_ptr<node_>>(this);
	}
*/
	void set_texture(const std::shared_ptr<texture>& tex)
	{
/*		__FUNC_YEL__

//owner
		auto p = dynamic_cast <component_*>(this);
		auto owner = p->owner();
		COUT << "pname: " << p->name_ << " type: " << __typeid_name(*p) << " owner: " << p->owner() << ENDL;

		
		COUT << "oname: " << owner->name_ << " type: " << __typeid_name(*owner) << ENDL;	
*/
		///owner();

///
		tex0_ = tex;

		rect_.right = tex->width;
		rect_.bottom = tex->height;

		is_renew_ = true;

		pi_ = std::make_unique<tp_member<std::shared_ptr<texture>>>(this, &texture_renderer::tex0_);
		pii_ = std::make_unique<tp_member_ptr<std::shared_ptr<texture>>>(this, &texture_renderer::tex0_);

		pf_ = std::make_unique<tp_method<void>>(this, &texture_renderer::ddd);

		///COUT << "type: " << __typeid_name(*tex0_) << ", pointer: " << tex0_ << ENDL;

		auto pfi = pi_->get();
		//COUT << "type: " << __typeid_name(*pfi) << ", pointer: " << pfi << ENDL;

		auto pfii = pii_->get<std::shared_ptr<texture>>();
		//COUT << "type: " << __typeid_name(*pfii) << ", pointer: " << pfii << ENDL;

		(*pf_)();

		f1_ = std::bind(&texture_renderer::ddd, this);
		f1_(1);

		//StartGamePathButton->OnClicked.AddDynamic(this, &UInventoryPanelWidget::StartDialog);
		//sb->on_clicked = std::bind(&texture_renderer::ddd, this);

		/**
		 * Bind texture
		 */
		//auto p = std::dynamic_pointer_cast<GL::GL_handle> (tex0_);
		//(*shader_)["sprite_p0"]->set("TEX0", p->handle());
	}

public:

	///
	//abgr = 0x00BBGGRR
	void renew(const int& x, const int& y, std::shared_ptr<texture>& tex, const rect& rect, uint color = 0xffffffff, float alpha = 1.0f)
	{
	/**
	 *
	 */
	float right = (float) tex->width;
	float bottom = (float) tex->height;
		

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
  float rx = -x;
	float ry = -y;
	float rw = rect.right-x;
	float rh = rect.bottom-y;

	float tx = 0;//rect.left / right;
	float ty = 1;//1-(rect.top / bottom);
	float tw = 1;//(rect.left + rect.right) / right;
	float th = 0;//1-((rect.top + rect.bottom) / bottom);

	V2F_C4B_T2F* verts = static_cast<V2F_C4B_T2F*> (vb_->map());
	verts[0].position = float2(rx, ry);
	verts[1].position = float2(rx, rh);
	verts[2].position = float2(rw, ry);
	verts[3].position = float2(rw, rh);

	verts[0].tex0 = float2(tx, ty);
	verts[1].tex0 = float2(tx, th);
	verts[2].tex0 = float2(tw, ty);	
	verts[3].tex0 = float2(tw, th);

//color = 0xffffffff;
//alpha = 0;

	verts[0].color = color;
	verts[1].color = color;
	verts[2].color = color;
	verts[3].color = color;
	vb_->unmap();
}

float __y = 0;
	void renew(const point& pos, std::shared_ptr<texture>& tex, const rect& rect, uint color = 0xffffffff, float alpha = 1.0f)
	{
		renew(pos.x, pos.y, tex, rect, color, alpha);
	}

		GL::float4x4 projection_;
		GL::float4x4 view_;

    GL::float4x4 model_;

	void draw()
	{
//__method__


	auto fb = GL_framebuffer::get();

// 1 2
// 3 4
//
// 1:
// 2:
// 3:
// 4: 0,w,h,0

projection_.ortho(0,fb->width(), fb->height(),0, -1024.0f, 1024.0f);
//projection_.perspective_fovy(45.0f, (float)fb->width() / (float)fb->height(), 0.1f, 2000.0f);
//view_.identity();

//GL::float3 vpos(0,0, -500.f);
//view_.translation(vpos);

GL::float3 pos(pos_.x, pos_.y, 0.0f);
model_.translation(pos);

	float right = (float) tex0_->width;
	float bottom = (float) tex0_->height;

//int c=13; int r=1;
//static int x=0; int y=0;
//x++;
//if ( x> c) x=0;

GL::float4 v;
//v.x = x * (right / c / right); // TODO(Joey): check for int precision loss
//v.y = y * (bottom / r / bottom);
//v.z = right / c / right;
//v.w = bottom / r / bottom;

v.x = rect_.left / right;
v.y = rect_.top / bottom;
v.z = rect_.right / right;
v.w = rect_.bottom / bottom;

GL::float4x4 rot;
rot.rotation_z(__y);
GL::float4x4 m = /*rot */ model_;

__y += -.1f;
try {
    (*shader_)["sprite_p0"]->set("projection", projection_);
		(*shader_)["sprite_p0"]->set("view", view_);
    (*shader_)["sprite_p0"]->set("model", m);

		(*shader_)["sprite_p0"]->set("offset", v);

		auto p = std::dynamic_pointer_cast<GL::GL_handle> (tex0_);
		(*shader_)["sprite_p0"]->set("TEX0", p->handle());
}
catch (std::exception& e) {
	COUT << e.what() << ENDL;
}		

	ICLASS(renderer)::draw();
}

	GL::point pos_;

	void draw(const point& pos, uint color = 0xffffffff, float alpha = 1.0f)
	{
		if (is_renew_)
			renew(100,100, tex0_, rect_, color, alpha);

		is_renew_ = false;

	  pos_ = pos;

		draw();
	}
};

};//GL::_2d
