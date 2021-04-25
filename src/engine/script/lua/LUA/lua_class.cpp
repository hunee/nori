/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "StdAfx.h"

#include "lua_class.h"

lua_shared_class* lua_shared_class::_self =0;


template <>
void lua_push(lua_State* L, lua_class* val)
{
	lua_pushlightuserdata(L, val);
}

template <>
lua_class* lua_to(lua_State* L, int idx)
{
	return (lua_class*) lua_topointer(L, idx);
}

