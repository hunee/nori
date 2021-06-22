/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_REF_H__
#define __LUA_REF_H__

#include "lua_metatable.h"

template <typename T>
class lua_ref_ {
protected:
	lua_State* _L;

	int _ref;
	T* _self;
	
public:
	lua_ref_(lua_State* L, const char* method, T* self)
	: _L(L)
	, _ref(0)
	, _self(self)
	{
		/**
		 * metatable
		 */
		luaL_getmetatable(_L, lua_metatable<T>::_name);
		if (!lua_istable(L, -1))
			return;
		
		lua_setmetatable(_L, -2);
		
		
		/**
		 * method
		 */
		lua_pushstring(_L, method);
		lua_gettable(_L, -2);
		if (!lua_isfunction(_L, -1))	
			return;	
		
		_ref = luaL_ref(_L, LUA_REGISTRYINDEX);
		
		// ???
		lua_pop(L, 1);
	}
	~lua_ref_()
	{
		luaL_unref(_L, LUA_REGISTRYINDEX, _ref);
	}
	
	
	/**
	 *
	 */
	inline void pushuserdata()
	{
		/**
		 * set ref (fast???)
		 */
		lua_rawgeti(_L, LUA_REGISTRYINDEX, _ref);	
		
		//push userdata
		//luaL_getmetatable(_L, type_name<T>());						// lookup metatable in Lua registry
		//lua_setmetatable(_L, -2);
		
		//push userdata
		lua_metatable<T>::pushuserdata(_L, _self);		
		//lua_pushvalue(_L, -2);
	}
	
	inline int pcall(int narg)
	{
		int base = lua_gettop(_L) - narg;					// function index
		lua_pushcfunction(_L, lua_traceback);					// push traceback function
		lua_insert(_L, base);											// put it under chunk and args
		
		int status = lua_pcall(_L, narg, 0, base);
		lua_remove(_L, base);											// remove traceback function 
		
		if (status)
		{
			const char* msg = lua_tostring(_L, -1);
			if (msg == NULL)
				msg = "(error with no message)";
			
			TRACEA("ERROR: %s\n", msg);
			lua_pop(_L, 1);
			
			return FALSE;
		}
		
		return TRUE;
	}
};

#endif //__LUA_REF_H__
