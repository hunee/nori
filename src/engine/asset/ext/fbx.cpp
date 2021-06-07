/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "asset/asset_manager.h"

#include "fbx.h"

#ifdef USE_FBXSDK

#include <iostream>

namespace ext {

std::shared_ptr<asset_> fbx::import(const std::string& pathname)
{
	//__method__

	auto p = std::make_shared<asset<GL::_3d::mesh>>();
	return p;
}

}; //ext

#endif //USE_FBXSDK
