/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_USERDATA_H__
#define __LUA_USERDATA_H__

#include "lua_userdata_impl.h"


/**
 * lua_userdata
 */
struct lua_State;

template<typename T>
struct lua_userdata : public lua_userdata_impl<T> {
	lua_userdata(lua_State* L)
	: lua_userdata_impl<T>(new T(L))
	{
	}
	~lua_userdata()
	{
		if (lua_userdata_impl<T>::_self)
		{
			delete lua_userdata_impl<T>::_self;
			lua_userdata_impl<T>::_self = NULL;
		}
	}
};


#endif //__LUA_USERDATA_H__
