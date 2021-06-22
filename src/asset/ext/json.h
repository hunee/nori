/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace ext {

class EXT_json {
public:
    json()
    {
        //__method__
    }

	std::shared_ptr<asset_> import(const std::string& pathname)
	{
		__method__

        auto p = std::make_shared<asset_ptr<GLtexture>>();
        ///p->reset(new GLtexture());

        return p;
    }
};

}; //ext