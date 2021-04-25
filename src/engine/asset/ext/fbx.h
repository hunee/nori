/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/3d/mesh.h"
#include "renderer/3d/skelmesh_animation.h"

#define USE_FBXSDK

#ifdef USE_FBXSDK

#include <fbxsdk.h>

namespace ext {

class fbx {
public:
fbx()
{
    //CLOGF();
}

std::shared_ptr<ICLASS(asset)> import(const std::string& pathname);

};

}; //ext

#endif //USE_FBXSDK