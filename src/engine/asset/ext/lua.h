/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace ext {

class lua_shader {
public:
	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname);
};

}; //ext