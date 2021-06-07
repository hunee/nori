/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/buffer.h"
#include "renderer/shader.h"

#include "renderer/GL/GL_buffer.h"
#include "renderer/GL/GL_framebuffer.h"

#include "renderer/camera.h"

namespace GL {

/****/
const int	ALIGN_ANY = 0;
const int	ALIGN_LEFT = 1;
const int	ALIGN_TOP = 2;
const int	ALIGN_RIGHT = 4;
const int	ALIGN_BOTTOM = 8;
const int	ALIGN_CENTER = 16;
const int	ALIGN_IMAGE = 32;


class base_renderer {
protected:
	std::unique_ptr<vertex_array> va_;
	
	std::unique_ptr<buffer> vb_;
	std::shared_ptr<shader> shader_;
	
public:
	base_renderer()
	{
		///__FUNC_YEL__

	  va_ = std::make_unique<GL_vertex_array>();

	  //vb_ = std::make_unique<GL_buffer_<V2F_C4B_T2F, GL_ARRAY_BUFFER, GL_TRIANGLE_STRIP, GL_WRITE_ONLY>>(4);
    //shader_ = asset_manager::get()->import<GL::shader>(asset_path("sprite.shader.xml"));

		cc_ = std::make_shared<component<GL::camera>>("cc");		
		cc_->ortho();

	}
	virtual ~base_renderer()
	{	
	}

public:
	std::shared_ptr<component<GL::camera>> cc_;	

	void set_camera(std::shared_ptr<component<GL::camera>>& cc)
	{
		cc_ = cc;
	}


public:
	void _tick(double dt) { cc_->_tick(dt); };
	
	void draw()
	{
		///__method__

    /**
     * bind vertex arrays object
     */	
    va_->bind();

    for (auto&& p : *shader_)
    {
      p.second->bind();

      vb_->draw();
      //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      //glDrawElements(GL_LINES, 2* MAP_NUM_LINES , GL_UNSIGNED_INT, 0);

    }
	}
};

};//GL
