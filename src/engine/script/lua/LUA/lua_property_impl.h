/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_PROPERTY_IMPL_H__
#define __LUA_PROPERTY_IMPL_H__


/**
 *
 */
struct lua_State;

class lua_property_impl
{
public:
	virtual void get(lua_State* L) = 0;
	virtual void set(lua_State* L) = 0;
};


#endif //__LUA_PROPERTY_IMPL_H__
