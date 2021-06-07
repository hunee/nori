/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace GL::_2d {


class freetype_font : public font {

public:	
//font
size_t texture_width_ =	1024;
size_t texture_height_ = 1024;

public:
	freetype_font()
	: x_(0), y_(0)
	, library_(NULL)
	, face_(NULL)
	{
		/**
		 * Texture
		 */
		auto size = texture_width_ * texture_height_;

		fontdata_.reset(new unsigned char [size]);
		memset(fontdata_.get(),0, size);
	
		/**
		 * FT
		 */
		FT_Error error = FT_Init_FreeType(&library_);
		if (error)
		{
			//throw ...
			char e[255];
			sprintf(e, "freetype error %s", FT_Error_String(error));

			throw std::runtime_error(e);

		}
			//return;
	}

	~freetype_font()
	{
	FT_Done_Face(face_);
	FT_Done_FreeType(library_);
}

	
public:
	int new_face(const std::string& name, int width=10, int height=0)
{
	if (face_)
		return 1;

	FT_Error error = FT_New_Face(library_, name.c_str(), 0, &face_);
	///if (error == FT_Err_Unknown_File_Format)
	if (error)
	{
    //throw ...
		char e[255];
		sprintf(e, "freetype error %s", FT_Error_String(error));

		throw std::runtime_error(e);

	}

	error = FT_Select_Charmap(
		face_,										// target face object 
		FT_ENCODING_UNICODE);		// encoding           

#if 1
	error = FT_Set_Char_Size(
		face_,			// handle to face object           
		width*64,		// char_width in 1/64th of points  
		height*64,	// char_height in 1/64th of points
		75,					// horizontal device resolution    
		75);				// vertical device resolution      
#else
	error = FT_Set_Pixel_Sizes(
		face_,		// handle to face object 
		0,				// pixel_width           
		11);			// pixel_height          
#endif
	
	/**
	 * Texture
	 */
	///_texture = new GLtexture<GL_TEXTURE_2D, GL_LUMINANCE>(0, FONT_TEXTURE_WIDTH, FONT_TEXTURE_HEIGHT, _fontData);

	texture_ = std::make_shared<GL_texture_<GL_TEXTURE_2D, GL_LUMINANCE>>();
	texture_->texImage(0, texture_width_, texture_height_, fontdata_.get());

	return 1;
}

public:
	std::shared_ptr<font_cache> code(unsigned int c) override
	{
	auto fc = get(c);
	if (fc == nullptr)
	{
		// retrieve glyph index from character code
		FT_UInt glyph_index = FT_Get_Char_Index(face_, c);

		// load glyph image into the slot (erase previous one)
		FT_Error error = FT_Load_Glyph(face_, glyph_index, FT_LOAD_DEFAULT);

		// convert to an anti-aliased bitmap
		error = FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_NORMAL);

		
		// now, draw to our target surface
		draw_bitmap(&face_->glyph->bitmap, x_, y_);
		
		
		///
		fc = std::make_shared<font_cache>();
		
		// increment pen position
		fc->bitmap.x = face_->glyph->bitmap_left;
		fc->bitmap.y = height() - face_->glyph->bitmap_top;
		fc->bitmap.width = face_->glyph->advance.x >> 6;
		fc->bitmap.height = face_->glyph->bitmap.rows;

		fc->tx = (x_ / (float) texture_width_);
		fc->ty = (y_ / (float) texture_height_);
		fc->tw = ((x_ + fc->bitmap.width) / (float) texture_width_);
		fc->th = ((y_ + fc->bitmap.height) / (float) texture_height_);

		x_ += fc->bitmap.width + 1;
		if ((x_ + width()) >= texture_width_)
		{
			x_ = 0;
			y_ += height() + 1;
		}
		
		add(c, fc);
	}
	
	return fc;
}

	
/**
 * property
 */
public:
	const size_t width() const override
	{
		return face_->size->metrics.x_ppem;
	}
	const size_t height() const override
	{
		return face_->size->metrics.y_ppem;
	}

private:
	FT_Library library_;
	FT_Face face_;

	std::unique_ptr<unsigned char[]> fontdata_;
	int x_, y_;

private:
	void draw_bitmap(FT_Bitmap* bitmap, int x, int y)
{
	int i, j, p, q;
	int x_max = x + bitmap->width;
	int y_max = y + bitmap->rows;
	
	auto ptr = fontdata_.get();

	for (i = x, p = 0; i < x_max; ++i, ++p)
	{
		for (j = y, q = 0; j < y_max; ++j, ++q)
		{
			if ( i < 0 || j < 0 ||
				i >= texture_width_ || j >= texture_height_ )
				continue;

			ptr[j*texture_width_+i] |= bitmap->buffer[q * bitmap->width + p];
			//_fontData[j*texture_width_+i] |= 0xff;
		}
	}
	
	/**
	 * Texture
	 */
	//_texture->texImage(_fontData);
	texture_->texImage(0, texture_width_, texture_height_, ptr);
}


};

};//GL::_2d