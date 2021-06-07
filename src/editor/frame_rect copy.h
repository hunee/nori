/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "2d/frame_renderer.h"
#include "2d/bitmap_font.h"
#include "2d/font_renderer.h"
#include "2d/texture_renderer.h"

#include "asset_manager.h"

#include "object.h"

namespace GL {

class frame_rect
: public ICLASS(object) {
	std::unique_ptr<_2d::frame_renderer> frr_;
	std::unique_ptr<_2d::bitmap_font> bmfont_;
	std::unique_ptr<_2d::texture_renderer> trr_;
	//std::unique_ptr<_2d::texture_renderer> trr2_;	
	
	std::shared_ptr<component<_2d::texture_renderer>> trr2_;	
	//std::shared_ptr<component_> trr2_;	

	std::shared_ptr<texture> tex0_;

uint _backgroundColor;
uint _highlightColor;
uint _darkColor;

public:
	frame_rect()
	: frr_(std::make_unique<_2d::frame_renderer>())
	, bmfont_(std::make_unique<_2d::bitmap_font>())
	,_backgroundColor(0xff2b2b2b)
	,_highlightColor(0xfffb9700)
	,_darkColor(0xff636262)
	{
///		__FUNC_YEL__

		trr_ = std::make_unique<_2d::texture_renderer>(bmfont_->texture());

  	tex0_ = asset_manager::get()->import<GL::texture>(asset_path("map0.tga"));
		
//init();

		///dump();
	}

void init()
{
		{
		//std::make_unique<GL::node<GL::frame_rect> >("frame_rect");
		trr2_ = std::make_shared<component<_2d::texture_renderer>>("trr2");
		///COUT << "name: " << trr2_->name_ << " type: " << __typeid_name(*trr2_) << ", use_count: " << trr2_.use_count() << " owner: " << trr2_->owner() << ENDL;
		
		add("trr2", trr2_);
		
		///COUT << "name: " << trr2_->name_ << " type: " << __typeid_name(*trr2_) << ", use_count: " << trr2_.use_count() << " owner: " << trr2_->owner() << ENDL;
		auto owner = trr2_->owner();
		///COUT << "oname: " << owner->name_ << " type: " << __typeid_name(*owner) << ", use_count: " << owner.use_count() << ENDL;

		trr2_->set_texture(tex0_);

		trr2_->color_ = 0x00ffffff;
		trr2_->rect_.right = 200;
		trr2_->rect_.bottom = 200;

		trr2_->is_renew_ = true;
		
		///COUT << "type: " << __typeid_name(*trr2_) << ", use_count: " << trr2_.use_count() << ENDL;

	//throw std::runtime_error("e");
	//assert(0);

		//trr2_->tex0_ = tex0_;

		//auto pp = std::dynamic_pointer_cast<_2d::texture_renderer>(trr2_);
		//pp->set_texture(tex0_);

		//std::dynamic_pointer_cast<_2d::texture_renderer>(trr2_)->set_texture(tex0_);
		
		//(*this)["1"] = trr2_;
		//(*this)["1"] = dynamic_pointer_cast<component_>(trr2_);
		//add("1", trr2_);
		}

}

//began()
//end()
//tick()

void began()
{
///	__method__

	init();	
		
		/*auto n = node_ptr();
		COUT << "oname: " << n->name_ << " type: " << __typeid_name(*n) << ENDL;
		COUT << "this: " << this << " node_ptr: " << n << ENDL;
*/
//add("trr2", trr2_);
}

void tick(float dt)
{

}

	void draw()
	{
		//__method__
		
		GL::rect rect1(100,100, 200,200);
		frr_->draw_rect(rect1, _backgroundColor);

		GL::rect rect2(300,300, 400,400);
		frr_->draw_rect(rect2, _highlightColor, _darkColor, _backgroundColor);

		GL::point pos(100,300);
		trr_->draw(pos);

{
		GL::point pos2(200,100);

		//find
		auto pp = get<_2d::texture_renderer>("trr2");
		pp->draw(pos2);
}

		//auto p = dynamic_cast <node<frame_rect>*>(this);
/*
		//owner
		auto n = node_ptr(); //node
		auto o = n->owner(); //component, parent

		COUT << "name: " << n->name_ << " type: " << __typeid_name(*n) << ENDL;
		COUT << "oname: " << o->name_ << " type: " << __typeid_name(*o) << ENDL;

		//auto p = std::dynamic_pointer_cast<ICLASS(object)>(o);
		auto p = std::dynamic_pointer_cast<node_>(o);
		if (p)
			COUT << "type: " << __typeid_name(*p) << ENDL;
*/

		transform_.x = 100;
	{	
		GL::point pos2(transform_.x + 300,200);
		trr2_->draw(pos2);
	}

	}

};

};//GL
