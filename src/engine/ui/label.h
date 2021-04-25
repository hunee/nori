/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "core/object.h"

#include "renderer/font/font_renderer.h"
#include "renderer/font/freetype_font.h"

namespace GL::ui {

/**
 * @brief 
 * 
 */
class label
: public frame_rect {
public:
	std::string text_;
  //unsigned int color_;

	std::shared_ptr<component<GL::_2d::font_renderer>> frc_;
	std::shared_ptr<GL::_2d::font> font_;

public:
label()
//: color_(0xff2b2b2b)
{
}

public:
  void _began() override
  {
		frame_rect::_began();

		font_ = asset_manager::get()->import<GL::_2d::font>(asset_path("AsiaKHANM-SONY_p20.TTF"));
		{
			auto p = std::dynamic_pointer_cast<GL::_2d::freetype_font> (font_);
			p->new_face(asset_path("AsiaKHANM-SONY.TTF"), 20);
		}

		frc_ = std::make_shared<component<GL::_2d::font_renderer>>("frc");
    add("frc", frc_);

		frc_->set_font(font_);

		rect_.right = frc_->width(text_.c_str());
		rect_.bottom = frc_->height(text_.c_str());
  };

	virtual void _draw() override
	{
		frame_rect::_draw();

		///CLOGF();
    GL::point pos(transform_.x2,transform_.y2);
    frc_->textout(pos, text_.c_str(), 0xffffffff);
	}
};

};//GL::ui

