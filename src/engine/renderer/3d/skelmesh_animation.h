
/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


namespace GL::_3d {

/**
 * @brief 
 * 
 */
class skelmesh_animation {
public:
	virtual ~skelmesh_animation()
	{
		CLOGF();		
	}

public:
	virtual void bind() =0;
};

};//GL::_3d

