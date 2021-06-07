/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "ui/frame_rect.h"

#include "ui/component/anchor.h"

#include "asset/asset_manager.h"

#include "renderer/3d/mesh.h"
#include "renderer/3d/mesh_renderer.h"

namespace GL {

/**
 * @brief 
 * 
 */
class frame_anchor
: public GL::ui::frame_rect {
public:
	std::shared_ptr<component<GL::ui::anchor>> ac_;	

	frame_anchor() {
		__method__
	}

	void set_ancher(std::shared_ptr<component<GL::ui::anchor>>& ac)
	{
		ac_ = ac;
	}

	std::shared_ptr<component<_3d::mesh_renderer>> mrc_;	
	//std::shared_ptr<component_> trr2_;	

	std::shared_ptr<GL::_3d::mesh> mesh_;

void _began() override
{
	frame_rect::_began();

	rect_.right = 200;
	rect_.bottom = 200;

	ac_ = std::make_shared<component<GL::ui::anchor>>("ac");
	add("ac", ac_);

	ac_->align_ = GL::ALIGN_RIGHT | GL::ALIGN_BOTTOM;
	ac_->align();


	mesh_ = asset_manager::get()->import<GL::_3d::mesh>(asset_path("Spore_01.fbx"));
	mrc_ = std::make_shared<component<_3d::mesh_renderer>>("mrc");

};

	void _draw() override
	{
		//__method__

		frame_rect::_draw();
	}
};

};//GL

