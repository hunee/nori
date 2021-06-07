/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "frame_rect.h"

#include "renderer/2d/texture_renderer.h"
#include "renderer/2d/texture_frame.h"

#include "component/button_input.h"


#include <iostream>
#include <fstream>


namespace GL::ui {

/**
 * @brief 
 * 
 */
class button 
: public frame_rect {


public:
	std::shared_ptr<component<GL::_2d::texture_renderer>> trc_;	
	std::shared_ptr<texture> tex0_;

	std::shared_ptr<component<GL::_2d::texture_frame>> tfc_;

public:
	std::string tex0_name_ = "blender_icons.tga";

public:
	button() { __method__ }

public:
	std::shared_ptr<component<GL::ui::button_input>> bic_;	
	void set_input(std::shared_ptr<component<GL::ui::button_input>>& bic)
	{
		bic_ = bic;
	}

public:

	template <typename T= component_>
	void add(const std::string& name, std::shared_ptr<T> component)
{
	object::add(name, component);
}

	template <>
	void add(const std::string& name, std::shared_ptr<asset_> asset)
{
__function__
//member::add(name, asset);
}

void _began() override
{
	frame_rect::_began();

////
	tex0_ = asset_manager::get()->import<GL::texture>(asset_path(tex0_name_));
	auto pp = std::dynamic_pointer_cast<asset_>(tex0_);
	add("tex0", pp);

///
	trc_ = std::make_shared<component<GL::_2d::texture_renderer>>("trc");
	add("trc", trc_);

	trc_->set_texture(tex0_);
	trc_->color_ = 0x00ffff00;

///
	tfc_ = std::make_shared<component<GL::_2d::texture_frame>>("tfc");
	add("tfc", tfc_);

	//sfc_->trc_ = trc_;
	tfc_->set_renderer(trc_);
	tfc_->set_frame_counts(3);

	///
	bic_ = std::make_shared<component<GL::ui::button_input>>("bic");
	add("bic", bic_);

	bic_->set_frame(tfc_);

///
	bic_->on_click_ = std::bind(&button::on_clicked, this, std::placeholders::_1);


};

void on_clicked(int n)
{
__method__
}
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

