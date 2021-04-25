/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "unique_ptr.h"

#include "GL_ext.h"

namespace GL {

/**
 * OpenGL coordnate
 *
 
 (-1,1 0,1)         (1,1 1,1)
 +(0)-----------+(1)
 |              |
 |              |
 |              |
 |              |
 |              |
 |              |
 +(2)-----------+(3)
 (-1,-1 0,0)       (1,-1 1,0)
*/

enum GLfsaa {
	FSAAOff = 0,
	FSAAFast = 1,
	FSAANice = 2,
};

#define _X(x) (x)
#define _Y(y)	height_ - y-1)

class GL_framebuffer : public unique_ptr<GL_framebuffer> {
public:
	virtual void begin()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	}

	virtual void end()
	{

	}

	virtual void set_viewport(const rect& rect)
	{
		if (rect.width == 0 || rect.height == 0)
			return;

	//	TRACEA("->> width: %d height:%d\n", width, height);
/*
	GLint viewportDims[4];
	glGetIntegerv(GL_VIEWPORT, viewportDims);
	 
	width_ = viewportDims[2];
	height_ = viewportDims[3];

//COUT << "w: " << width_ << "h: " << height_ << ENDL;
*/		
		size_.x = rect.width;
		size_.y = rect.height;

		//
		half_.x = (float) rect.width * 0.5f;
		half_.y = (float) rect.height * 0.5f;
	}

private:
	size size_;
	float2 half_;

public:
	/// make_rhw (x,y, 0, 0)
	float3 rhw(int x, int y)
	{
		return float3(((float) x - half_.x) / half_.x, ((float) y - half_.y) / - half_.y, 0.0f);
	}

	float rhw_x(int x)
	{
		return (((float) x - half_.x) / half_.x);
		//return (((2.0f * (GLfloat) x) / _width) - 1.0f);
	}
	float rhw_y(int y)
	{
		return (((float) y - half_.y) / - half_.y);
		//return -(((2.0f * (GLfloat) y) / _height) - 1.0f);
	}

	/*
	 GLfloat right, bottom;
	 GLfloat _11, _22;
	 GLfloat3 make_xyz(GLfloat x, GLfloat y, GLfloat z)
	 {
	 // Compute the vector of the pick ray in screen space
	 GLfloat3 v;
	 v.x = -(((2.0f * x) / right) - 1.0f) / _11;
	 v.y = (((2.0f * y) / bottom) - 1.0f) / _22;
	 v.z =  1.0f;
	 
	 v.x = v.x * z;
	 v.y = v.y * z;
	 v.z = v.z * z;
	 return v;
	 }
	 
	
	- (GLfloat2)make_x:(GLfloat)x y:(GLfloat)y
	{
		// Compute the vector of the pick ray in screen space
		GLfloat2 v;
		v.x = (((2.0f * x) / _bounds.size.width) - 1.0f);
		v.y = -(((2.0f * y) / _bounds.size.height) - 1.0f);
		
		return v;
	}*/
	

/**
 * property
 */
public:
	const size_t& width() const
	{
		return size_.x;
	}
	const size_t& height() const
	{
		return size_.y;
	}

};
};//GL