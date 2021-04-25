
/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "int2.h"


namespace GL {

/**
 * @brief 
 * 
 */
class texture : public int2, public _type_info<texture> {
public:
	virtual ~texture()
	{
		CLOGF();		
	}

public:
	virtual void bind() =0;
};

};//GL

