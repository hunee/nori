/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "core/object.h"

#include "os/input.h"

#include "renderer/picker.h"

namespace GL::ui {

class input
: public owner_ptr {
public:

input()
{
}

int button_=0;
int button_action_ =0;

GL::float2 cursor_;
GL::float2 distance_;

bool focus_ = false;
bool drag_ = false;

bool moveable_ = false;

void _tick(double dt) override
{
//CLOGF();
	auto in = ::input::get();

	auto o = owner<object>();
	if (o) 
	{
		/// cursor event
		if (cursor_.x != in->cursor_.x || cursor_.y != in->cursor_.y)
		{
			cursor_ = in->cursor_;
			if (drag_ || o->contains(cursor_.x, cursor_.y))
			{
				focus_ = true;

				auto p = picker::get();
				p->picked_.push_back(o);

			}
			else
				focus_ = false;
		}

		// button event
		if (button_ != in->button_ || button_action_ != in->button_action_)
		{
			button_ = in->button_;
			button_action_ = in->button_action_;

			if (focus_ && button_ == GLFW_MOUSE_BUTTON_LEFT && button_action_ == GLFW_PRESS)
			{
				drag_ = true;

				distance_.x = cursor_.x - o->transform_.x;
				distance_.y = cursor_.y - o->transform_.y;
			}

			if (button_ == GLFW_MOUSE_BUTTON_LEFT && button_action_ == GLFW_RELEASE)
			{
				drag_ = false;
			}
		}
		
		if (drag_ && moveable_)
		{	
			o->transform_.x = cursor_.x - distance_.x;
			o->transform_.y = cursor_.y - distance_.y;
		}	
	}
};

};

};//GL::ui


