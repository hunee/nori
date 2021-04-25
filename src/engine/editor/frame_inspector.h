/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "asset/asset_manager.h"
#include "core/object.h"

#include "renderer/2d/frame_renderer.h"
#include "renderer/2d/texture_renderer.h"

#include "renderer/font/font_renderer.h"
#include "renderer/font/bitmap_font.h"

#include "frame_anchor.h"

#include "ui/panel.h"
#include "ui/sprite.h"
#include "ui/button.h"
#include "ui/label.h"

namespace GL {

class frame_inspector
: public object {
	std::unique_ptr<_2d::frame_renderer> frr_;
	std::unique_ptr<_2d::bitmap_font> bmfont_;
	std::unique_ptr<_2d::texture_renderer> trr_;
	//std::unique_ptr<_2d::texture_renderer> trr2_;	
	
	std::shared_ptr<component<_2d::texture_renderer>> trr2_;	
	//std::shared_ptr<ICLASS(component)> trr2_;	

	std::shared_ptr<texture> tex0_;

unsigned int _backgroundColor;
unsigned int _highlightColor;
unsigned int _darkColor;

public:
	frame_inspector()
	: frr_(std::make_unique<_2d::frame_renderer>())
	, bmfont_(std::make_unique<_2d::bitmap_font>())
	,_backgroundColor(0xff2b2b2b)
	,_highlightColor(0xfffb9700)
	,_darkColor(0xff636262)
	{
		///YLOGF();

		trr_ = std::make_unique<_2d::texture_renderer>(bmfont_->texture());
  	tex0_ = asset_manager::get()->import<GL::texture>(asset_path("artplant_poster.tga"));

	}

void init()
{
	{
				{
		//std::make_unique<GL::node<GL::frame_rect> >("frame_rect");
		trr2_ = std::make_shared<component<_2d::texture_renderer>>("trr2");
		///COUT << "name: " << trr2_->name_ << " type: " << typeid_name(*trr2_) << ", use_count: " << trr2_.use_count() << " owner: " << trr2_->owner() << ENDL;
		
		add("trr2", trr2_);
		
		//COUT << "name: " << trr2_->name_ << " type: " << typeid_name(*trr2_) << ", use_count: " << trr2_.use_count() << " owner: " << trr2_->owner() << ENDL;
		//auto owner = trr2_->owner();
		//COUT << "oname: " << owner->name_ << " type: " << typeid_name(*owner) << ", use_count: " << owner.use_count() << ENDL;

		trr2_->set_texture(tex0_);

		trr2_->color_ = 0x00ffffff;
		//trr2_->rect_.right = 200;
		//trr2_->rect_.bottom = 200;
		
		//COUT << "type: " << typeid_name(*trr2_) << ", use_count: " << trr2_.use_count() << ENDL;
				}

	//throw std::runtime_error("e");
	//assert(0);

		//trr2_->tex0_ = tex0_;

		//auto pp = std::dynamic_pointer_cast<_2d::texture_renderer>(trr2_);
		//pp->set_texture(tex0_);

		//std::dynamic_pointer_cast<_2d::texture_renderer>(trr2_)->set_texture(tex0_);
		
		//(*this)["1"] = trr2_;
		//(*this)["1"] = dynamic_pointer_cast<ICLASS(component)>(trr2_);
		//add("1", trr2_);
		}

		auto owner = node_ptr()->owner();

		auto fp = std::make_shared<GL::node<GL::ui::panel> >("ui_panel", owner)->add();
		{
			auto p = dynamic_pointer_cast<GL::ui::frame_rect>(fp);
			p->transform_.x = 50;
			p->transform_.y = 50;

			p->rect_.right = 400;
			p->rect_.bottom = 400;

			p->_began();
		}

		auto fa = std::make_shared<GL::node<GL::frame_anchor> >("ui_anchor", fp)->add();
		{
			auto p = dynamic_pointer_cast<GL::ui::frame_rect>(fa);
			p->color_ = p->highlight_color_;

			p->_began();
		}

		auto fp2 = std::make_shared<GL::node<GL::ui::sprite> >("ui_sprite", fa)->add();
		{
			auto p = dynamic_pointer_cast<GL::ui::sprite>(fp2);
			p->color_ = p->dark_color_;
			p->tex0_name_ = "c0.tga";

			p->_began();
			p->sfc_->set_frame_counts(13);
			p->sfc_->fps_ = 13;
		}

		auto ft = std::make_shared<GL::node<GL::ui::label> >("ui_label", fa)->add();
		{
			auto p = dynamic_pointer_cast<GL::ui::label>(ft);
			p->transform_.y = 200;
			p->text_ = "c0.tga";
			
			p->_began();
		}

		auto ft2 = std::make_shared<GL::node<GL::ui::button> >("ui_button", fa)->add();
		{
			auto p = dynamic_pointer_cast<GL::ui::button>(ft2);
			p->transform_.y = 300;
			p->tex0_name_ = "deco_btn01.png";

			p->_began();
		}
}

//began()
//end()
//tick()

void _began() override
{
	//CLOGF();

	init();	
		
		/*auto n = node_ptr();
		COUT << "oname: " << n->name_ << " type: " << typeid_name(*n) << ENDL;
		COUT << "this: " << this << " node_ptr: " << n << ENDL;
*/
//add("trr2", trr2_);
}

void _tick(double dt) override
{
	///YLOGF();
	object::_tick(dt);

	auto fb = GL_framebuffer::get();

	float fps = 30;

	transform_.x += dt * fps;
	if (transform_.x > fb->width())
		transform_.x = 0;
}

	void _draw() override
	{
		//CLOGF();

/*
		auto fb = GL_framebuffer::get();
		auto right = fb->width();
		auto bottom = fb->height();

		GL::size size_(200,200);
		GL::rect rect_(0,0, right, bottom);

		uint align = _2d::ALIGN_RIGHT | _2d::ALIGN_TOP;
		auto pos = get_align(align, rect_, size_);
	
		transform_.x = pos.x;
		transform_.y = pos.y;

		//pos.x += transform_.x;
		//pos.y += transform_.y;
*/

	/////
		//GL::rect rect(pos.x,pos.y, pos.x+size_.width, pos.y+size_.height);
		
		//frr_->draw_rect(rect, _backgroundColor);

/*
		GL::rect rect2(300,300, 400,400);
		frr_->draw_rect(rect2, _highlightColor, _darkColor, _backgroundColor);

		GL::point pos(100,300);
		trr_->draw(pos);
*/

		//GL::point pos2(400,100);

		//find
		//auto pp = get<_2d::texture_renderer>("trr2");
		//pp->draw(pos2);

		//auto p = dynamic_cast <node<frame_rect>*>(this);
/*
		//owner
		auto n = node_ptr(); //node
		auto o = n->owner(); //component, parent

		COUT << "name: " << n->name_ << " type: " << typeid_name(*n) << ENDL;
		COUT << "oname: " << o->name_ << " type: " << typeid_name(*o) << ENDL;

		//auto p = std::dynamic_pointer_cast<ICLASS(object)>(o);
		auto p = std::dynamic_pointer_cast<ICLASS(node)>(o);
		if (p)
			COUT << "type: " << typeid_name(*p) << ENDL;
*/

		transform_.x = 0;
		GL::point pos2(transform_.x + 200,200);
		trr2_->draw(pos2);

	}

};

};//GL
