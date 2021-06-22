/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "core/object.h"

#include "renderer/2d/texture_frame.h"

#include "os/input.h"

namespace GL::ui {

class button_input
: public owner_ptr {
public:

button_input()
{
	__method__
}

int button_=0;
int button_action_ =0;

GL::float2 cursor_;

bool focus_ = false;
bool drag_ = false;

int frame_index_ = 0;

public:
	std::function<void(int)> on_click_;

	//void moveto_to(double dt);

public:
	std::shared_ptr<component<GL::_2d::texture_frame>> tfc_;	

	void set_frame(std::shared_ptr<component<GL::_2d::texture_frame>>& tfc)
	{
		tfc_ = tfc;
	}

public:
void _tick(double dt) override
{
//__method__
	auto in = ::input::get();

	auto o = owner<object>();
	if (o) 
	{
		/// cursor event
		if (cursor_.x != in->cursor_.x || cursor_.y != in->cursor_.y)
		{
			cursor_ = in->cursor_;
			if (o->contains(cursor_.x, cursor_.y))
				focus_ = true;
			else
				focus_ = false;

      if (drag_ && focus_) frame_index_ = 2;
      else if (focus_) frame_index_ = 1;
      else frame_index_ = 0;

      tfc_->set_frame_index(frame_index_);
		}

		// button event
		if (button_ != in->button_ || button_action_ != in->button_action_)
		{
			button_ = in->button_;
			button_action_ = in->button_action_;

			if (focus_ && button_ == GLFW_MOUSE_BUTTON_LEFT && button_action_ == GLFW_PRESS)
			{
				drag_ = true;
        frame_index_ = 2;
			}

			if (drag_ && button_ == GLFW_MOUSE_BUTTON_LEFT && button_action_ == GLFW_RELEASE)
			{
				drag_ = false;
                
        if (focus_) 
          on_click_(1);

        if (focus_) frame_index_ = 1;
        else frame_index_ = 0;
			}

      tfc_->set_frame_index(frame_index_);
		}
	}
};

};

};//GL::ui


