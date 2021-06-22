/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/font/freetype_font.h"

namespace ext {

class ftf {
public:
    ftf()
    {
        //__method__
    }

	std::shared_ptr<asset_> import(const std::string& pathname)
	{
		///__method__

        auto p = std::make_shared<asset<GL::_2d::freetype_font>>();
        ///p->new_face(pathname);

        return p;
    }
};

}; //ext