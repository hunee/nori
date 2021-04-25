/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace ext {

class EXT_jpeg {
public:
	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname)
	{
		//CLOGF();

        auto p = std::make_shared<asset_ptr<GLtexture>>();
        ///p->reset(new GLtexture());

        return p;
    }
};

}; //ext