/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL::_2d {

///
class texture_frame
: public owner_ptr {
public:
	virtual ~texture_frame() {}

public:
	size_t frame_width_ = 0;
	size_t frame_counts_ = 0;

public:
	virtual void _tick(double dt) {}
	
public:
	std::shared_ptr<component<GL::_2d::texture_renderer>> trc_;	

	void set_renderer(std::shared_ptr<component<GL::_2d::texture_renderer>>& trc)
	{
		trc_ = trc;
	}

public:

	void set_frame_counts(size_t frame_counts)
	{
		frame_counts_ = frame_counts - 1;
		frame_width_ = trc_->tex0_->width / frame_counts;

		trc_->rect_.right = frame_width_;
	}	

	void set_frame_index(float index)
	{
		trc_->rect_.left = ((int)index * frame_width_);
	}	

};

}; //GL::_2d