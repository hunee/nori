/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

/////
#include "tp_member.h"
#include "tp_method.h"

#include <functional>

namespace GL::_2d {

///
class moveto 
: public owner_ptr {
public:
	float fps_ = 120;

	std::function<void(double)> to_;
	//void moveto_to(double dt);

public:
void _began()
{
		//mtc_->to_ = std::bind(&sprite::moveto_to, this, std::placeholders::_1);		
		//to_(dt);

		//StartGamePathButton->OnClicked.AddDynamic(this, &UInventoryPanelWidget::StartDialog);
		//sb->on_clicked = std::bind(&texture_renderer::ddd, this);
}

public:
	void _tick(double dt) 
	{
		auto o = owner<object>();
		if (o)
			to_(dt * fps_);
	}
};

}; //GL::_2d