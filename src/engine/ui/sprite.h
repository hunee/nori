/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "frame_rect.h"

#include "renderer/2d/moveto.h"
#include "renderer/2d/sprite_frame.h"
#include "renderer/2d/texture_renderer.h"

namespace GL::ui {

/**
 * @brief 
 * 
 */
class sprite 
: public frame_rect {
public:
	std::shared_ptr<component<GL::_2d::texture_renderer>> trc_;	
	std::shared_ptr<texture> tex0_;

	std::shared_ptr<component<GL::_2d::sprite_frame>> sfc_;
	std::shared_ptr<component<GL::_2d::moveto>> mtc_;	

public:
	std::string tex0_name_ = "blender_icons.tga";

public:
	sprite() { __method__ }

private:
	void moveto_to(double dt)
	{
		transform_.x += dt;

		auto fb = GL_framebuffer::get();
		if (transform_.x2 > fb->width())
			transform_.x = 0;
	}
	
public:

void _began() override
{
	frame_rect::_began();

////
	tex0_ = asset_manager::get()->import<GL::texture>(asset_path(tex0_name_));

///
	trc_ = std::make_shared<component<GL::_2d::texture_renderer>>("trc");
	add("trc", trc_);

	trc_->set_texture(tex0_);
	trc_->color_ = 0x00ffff00;

///
	sfc_ = std::make_shared<component<GL::_2d::sprite_frame>>("sfc");
	add("sfc", sfc_);

	//sfc_->trc_ = trc_;
	sfc_->set_renderer(trc_);
	
	//sfc_->set_frame_counts(13);

	mtc_ = std::make_shared<component<GL::_2d::moveto>>("mtc");
	add("mtc", mtc_);

	mtc_->to_ = std::bind(&sprite::moveto_to, this, std::placeholders::_1);

};

	void _draw() override
	{
		///__method__

		frame_rect::_draw();

		/////
		//GL::rect rect(transform_.x2,transform_.y2, transform_.x2+size_.width, transform_.y2+size_.height);
		
		GL::point pos(transform_.x2,transform_.y2);

		//find
		auto trc = get<GL::_2d::texture_renderer>("trc");
		trc->draw(pos);

	//	trc->is_renew_ = false;

		//trc_->draw(pos);

		///trc_->is_renew_ = false;
	}

};

};//GL::ui

