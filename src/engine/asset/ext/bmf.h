/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/font/bitmap_font.h"

namespace ext {

class bmf {
public:
    bmf()
    {
        //CLOGF();
    }

	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname)
	{
		//CLOGF();

        auto p = std::make_shared<asset<GL::_2d::bitmap_font>>();
        return p;
    }
};

}; //ext