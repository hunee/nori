/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/font/freetype_font.h"

namespace ext {

class ftf {
public:
    ftf()
    {
        //CLOGF();
    }

	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname)
	{
		///CLOGF();

        auto p = std::make_shared<asset<GL::_2d::freetype_font>>();
        ///p->new_face(pathname);

        return p;
    }
};

}; //ext