/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_USERDATA_IMPL_H__
#define __LUA_USERDATA_IMPL_H__


/**
 * lua_userdata_impl
 */

template<typename T>
struct lua_userdata_impl {
	T* _self;
	
	lua_userdata_impl(T* self)
	{
		_self = self;
	}
	virtual ~lua_userdata_impl()
	{
	}
};

#endif //__LUA_USERDATA_IMPL_H__
