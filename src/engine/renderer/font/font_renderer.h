/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "font.h"

#include "renderer/2d/renderer.h"

#include "asset/asset_manager.h"

namespace GL::_2d {

#define FONT_TAB_SIZE 2

class font_renderer 
: public GL::base_renderer {
public:
	std::shared_ptr<font> font_;
	
private:
	size_t num_verts_;

public:
	bool is_renew_ = true;

public:
	font_renderer()
	: font_(nullptr)
	, num_verts_(0)
	{
		vb_ = std::make_unique<GL_buffer_<V2F_C4B_T2F, GL_ARRAY_BUFFER, GL_TRIANGLES, GL_WRITE_ONLY>>(PATH_MAX * 6);
		shader_ = asset_manager::get()->import<GL::shader>(asset_path("font.shader.xml"));
	}
	
public:
	///
void set_font(std::shared_ptr<font>& font)
{
	//__method__

	font_ = font;

	is_renew_ = true;
	
	//(*shader_)["font_p0"]->use();

	//auto p = std::dynamic_pointer_cast<GL::GL_handle> (font_->texture());
	//(*shader_)["font_p0"]->set("TEX0", p->handle());


//	COUT << "font_->handle: " << p->handle() << ENDL;

}
	//abgr = 0x00BBGGRR
	template <typename T>
	void textout(const point& pos, const T text, uint color=0xffffffff)
	{
/**
 * OpenGL coordnate
 *
 (pos, uv)
 (-1,1 0,1)         (1,1 1,1)
 +(0)-----------+(2)
 |              |
 |              |
 |              |
 |              |
 |              |
 |              |
 +(1)-----------+(3)
 (-1,-1 0,0)       (1,-1 1,0)

	x = n
	y = 1 - n; flip_y
*/

		///__FUNC_YEL__
		if (is_renew_)
		{
			int x = 0;//pos.x;
			int y = 0;//pos.y;

			num_verts_ = 0;

			auto fb = GL_framebuffer::get();

			V2F_C4B_T2F* vert = (V2F_C4B_T2F*) vb_->map();

			T ptr = (T) text;
			while (*ptr)
			{
				if (*ptr == '\n')
				{
					x = 0;//pos.x;
					y += font_->width() + 1;
				}
				else if (*ptr == '\t')
				{
					x += FONT_TAB_SIZE * (font_->width() + 1);
				}
				else if (*ptr == '#')
				{
					
				}
				else
				{
					auto fc = font_->code(*ptr);
					
					int xx = x + fc->bitmap.x;
					int yy = y + fc->bitmap.y;
					
					float rx = xx;//fb->rhw_x(xx);
					float ry = yy;//fb->rhw_y(yy);
					float rw = xx + fc->bitmap.width;//fb->rhw_x(xx + fc->bitmap.width);
					float rh = yy + fc->bitmap.height;//fb->rhw_y(yy + fc->bitmap.height);

					float tx = fc->tx;
					float ty = fc->ty;
					float tw = fc->tw;
					float th = fc->th;

					// left, top
					vert->position = float2(rx, ry);
					vert->color = color;
					vert->tex0 = float2(tx, ty);
					vert ++;
					
					// right, top
					vert->position = float2(rw, ry);
					vert->color = color;
					vert->tex0 = float2(tw, ty);
					vert ++;
					
					// right, bottom
					vert->position = float2(rw, rh);
					vert->color = color;
					vert->tex0 = float2(tw, th);
					vert ++;

					// right, bottom
					vert->position = float2(rw, rh);
					vert->color = color;
					vert->tex0 = float2(tw, th);
					vert ++;

					// left, bottom
					vert->position = float2(rx, rh);
					vert->color = color;
					vert->tex0 = float2(tx, th);
					vert ++;

					// left, top
					vert->position = float2(rx, ry);
					vert->color = color;
					vert->tex0 = float2(tx, ty);
					vert ++;

					num_verts_ += 6;

					x += fc->bitmap.width + 1;
				}

				//
				if ((x + (font_->width() + 1)) >= fb->width())
				{
					x = 0;//pos.x;
					y += font_->height() + 1;
				}

				ptr ++;
			}
			
			vb_->unmap();
		}

		//base_renderer::draw();

GL::float3 vpos(pos.x, pos.y, 0.0f);

GL::float4x4 model_;
model_.translation(vpos);

try {
		(*shader_)["font_p0"]->use();
		
		(*shader_)["font_p0"]->set("projection", cc_->projection_);
		(*shader_)["font_p0"]->set("view", cc_->view_);

    (*shader_)["font_p0"]->set("model", model_);

		auto p = std::dynamic_pointer_cast<GL::GL_handle> (font_->texture());
		(*shader_)["font_p0"]->set("TEX0", p->handle());
}
catch (std::exception& e) {
	COUT << e.what() << ENDL;
}		


		/**
		 * bind vertex arrays object
		 */	
		va_->bind();

		for (auto&& p : *shader_)
		{
			p.second->bind();

			//vb_->draw();
			glDrawArrays(GL_TRIANGLES, 0, num_verts_);
			//glDrawElements(GL_LINES, 2* MAP_NUM_LINES , GL_UNSIGNED_INT, 0);

		}
	}


	template <typename T>
	void textout(const GL::rect& rect, const T text, uint color = 0xffffffff, int align = ALIGN_ANY)
	{
		int x = rect.x;
		int y = rect.y;

		if (align & ALIGN_LEFT)
		{
			x += width();
			y += (rect.w - height(text)) / 2;
		}
		else if (align & ALIGN_RIGHT)
		{
			x += rect.z - (width(text) + width());
			y += (rect.w - height(text)) / 2;
		}
		
		else if (align & ALIGN_CENTER)
		{
			x += (rect.z - width(text)) / 2;
			y += (rect.w - height(text)) / 2;
		}
		
		// IMAGE
		if (align & ALIGN_IMAGE)
			x += 14;
		
		textout(GL::point(x, y), text, color);
	}

public:
	template <typename T>
	size_t width(const T text)
	{
		size_t length = 0;
		
		T ptr = (T) text;
		while (*ptr)
		{
			if (*ptr == '\n')
			{
			}
			else if (*ptr == '\t')
			{
				length += FONT_TAB_SIZE * (width() + 1);
			}
			else if (*ptr == '&')
			{
				
			}
			else
			{
				auto p = font_->code(*ptr);
				length += p->bitmap.width + 1;
			}
			
			++ptr;
		}
		
		return length;

	}

	template <typename T>
	size_t height(const T text)
	{
		size_t length = 0;
		
		T ptr = (T) text;
		while (*ptr)
		{
			if (*ptr == '\n')
			{
			}
			else if (*ptr == '\t')
			{
				
			}
			else if (*ptr == '&')
			{
				
			}
			else
			{
				auto p = font_->code(*ptr);
				int _height = height() - p->bitmap.y;
				
				//int _height = _slot->metrics.height >> 6;
				if (length < (size_t) _height)
					length = _height;
			}
			
			++ptr;
		}
		
		return height() + (length/2);

	}

/**
 * property
 */
public:
	size_t width() const
	{
		return font_->width();
	}
	size_t height() const
	{
		return font_->height();
	}
};

};//GL::_2d