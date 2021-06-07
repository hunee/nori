/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "core/object.h"

#include "renderer/2d/frame_renderer.h"

#include "renderer/font/font_renderer.h"
#include "renderer/font/bitmap_font.h"
#include "renderer/font/freetype_font.h"

#include "component/input.h"

namespace GL::ui {

/**
 * @brief 
 * 
 */
class frame_rect
: public object {
public:
	rect rect_;

	unsigned int highlight_color_;
	unsigned int dark_color_;
	unsigned int background_color_;
  unsigned int color_;

	std::shared_ptr<component<GL::_2d::frame_renderer>> frc_;	

	std::shared_ptr<component<GL::_2d::font_renderer>> bmfrc_;
	std::shared_ptr<GL::_2d::font> bmfont_;

	std::shared_ptr<component<GL::_2d::font_renderer>> ftfrc_;
	std::shared_ptr<GL::_2d::font> ftfont_;

public:
frame_rect()
: rect_(0,0,200,200)
,	background_color_(0xff2b2b2b)
,	highlight_color_(0xfffb9700)
,	dark_color_(0xff636262)
, color_(background_color_)
{
	//__method__
}

public:

	std::shared_ptr<component<GL::ui::input>> ic_;	
	void set_input(std::shared_ptr<component<GL::ui::input>>& ic)
	{
		ic_ = ic;
	}

  void _began() override
  {
		//__method__

    frc_ = std::make_shared<component<GL::_2d::frame_renderer>>("frc");		
    add("frc", frc_);

		bmfont_ = asset_manager::get()->import<GL::_2d::font>(asset_path("sys.bmf"));
		
		bmfrc_ = std::make_shared<component<GL::_2d::font_renderer>>("bmfrc");
    add("bmfrc", bmfrc_);

		bmfrc_->font_ = bmfont_;

		ftfont_ = asset_manager::get()->import<GL::_2d::font>(asset_path("AsiaKHANM-SONY_p10.TTF"));
		{
			auto p = std::dynamic_pointer_cast<GL::_2d::freetype_font> (ftfont_);
			p->new_face(asset_path("AsiaKHANM-SONY.TTF"), 10);
		}

		ftfrc_ = std::make_shared<component<GL::_2d::font_renderer>>("ftfrc");
    add("ftfrc", ftfrc_);

		ftfrc_->set_font(ftfont_);

		///
		ic_ = std::make_shared<component<GL::ui::input>>("ic");
		add("ic", ic_);
  };

	bool contains(int x, int y) override
	{
		if (x > transform_.x2+rect_.left && x < transform_.x2+rect_.right && 
		    y > transform_.y2+rect_.top && y < transform_.y2+rect_.bottom)
			return true;

		return false;
	}

	virtual void _draw() override
	{
		///__method__

GL::rect rect(transform_.x2,transform_.y2, transform_.x2+rect_.width, transform_.y2+rect_.height);

if (ic_->focus_)// && action_ == GLFW_PRESS && key_ == GLFW_MOUSE_BUTTON_LEFT)
{
		frc_->draw_rect(rect, highlight_color_,dark_color_, background_color_);

    char fps[PATH_MAX];
    std::sprintf(fps, "%s(%s)\n: %.f,%.f (%.f, %.f)", ptr()->name_.c_str(), __typeid_name(*this), transform_.x2,transform_.y2, transform_.x,transform_.y);

    GL::point pos(transform_.x2,transform_.y2);
    bmfrc_->textout(pos, fps, 0xffffffff);
		//ftfrc_->textout(pos, fps, 0xffffffff);
}
else
{
	frc_->draw_rect(rect, color_);
}

	}
};

};//GL::ui

