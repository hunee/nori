/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_CLASS_REF_H__
#define __LUA_CLASS_REF_H__

#include "lua_helper.h"

template <typename T>
class lua_class_ref_ {
protected:
	lua_State* _L;
	
	int _ref;
	T* _target;
	const char* _method;
	
public:
	lua_class_ref_(lua_State* L, T* target, const char* method)
	: _L(L)
	, _ref(0)
	, _target(target)
	, _method(method)
	{
		if (target)
			setTarget(target);
		
	}
	~lua_class_ref_()
	{
		luaL_unref(_L, LUA_REGISTRYINDEX, _ref);
	}
	
	void setTarget(T* target)
	{
		_target = target;
		
		/**
		 * metatable
		 */
		lua_pushlightuserdata(_L, target);
		lua_gettable(_L, LUA_REGISTRYINDEX);
		
		
		/**
		 * method
		 */
		lua_pushstring(_L, _method);
		lua_gettable(_L, -2);
		if (!lua_isfunction(_L, -1))
			return;
		
		_ref = luaL_ref(_L, LUA_REGISTRYINDEX);
		
		// ??
		//lua_pop(_L, 1);
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
		
		// push userdata
		lua_pushlightuserdata(_L, _target);
		lua_gettable(_L, LUA_REGISTRYINDEX);

		//lua_pushvalue(_L, -2);			
	}
	
	inline int pcall(int narg)
	{
		int base = lua_gettop(_L) - narg;					// function index
		lua_pushcfunction(_L, lua_traceback);			// push traceback function
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

#endif //__LUA_CLASS_REF_H__
