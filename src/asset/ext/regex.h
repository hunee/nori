/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace ext {

class png {
public:
	std::shared_ptr<asset_> import(const std::string& pathname);
};

}; //ext