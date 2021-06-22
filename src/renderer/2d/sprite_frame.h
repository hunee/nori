/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "texture_frame.h"

namespace GL::_2d {

///
class sprite_frame
: public texture_frame {
public:
	virtual ~sprite_frame() {}

public:
	float fps_ = 16;

	float frame_index_ = 0;
	float last_frame_index_ = 0;

public:
	void _tick(double dt) override
	{
		///__method__

		frame_index_ += dt * fps_;
	
		if (frame_counts_ <= 1)
			frame_index_ = 0;
		else
		{
			// wrap
			frame_index_ -= ((int)frame_index_ / frame_counts_) * frame_counts_;
			if (last_frame_index_ != frame_index_)
			{
				last_frame_index_ = frame_index_;

				trc_->rect_.left = ((int)frame_index_ * frame_width_);
				//set_frame_index(frame_index_);
			//	trc_->is_renew_ = true;
			}
		}
	}

};

}; //GL::_2d