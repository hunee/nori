/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_CLASS_PROPERTY_H__
#define __LUA_CLASS_PROPERTY_H__

#include "property_impl.h"

#include "lua_class_ref.h"

/**
 *
 */
template <typename T, typename Target>
class lua_class_property_member : public property_impl<T> {
	lua_State* _L;
	const char* _member;
	
	Target * _target;

public:
	lua_class_property_member(lua_State* L, Target* target, const char* member)
	: _L(L)
	, _target(target)
	, _member(member)
	{
	}
	
	T get()
	{
		/**
		 * metatable
		 */
		lua_pushlightuserdata(_L, _target);
		lua_gettable(_L, LUA_REGISTRYINDEX);
		
		
		/**
		 * member
		 */
		lua_getfield(_L, -1, _member);

		T v = lua_to<T>(_L, -1);
		
		lua_pop(_L, 1);
		
		return v;
	}
	void set(T v)
	{
		/**
		 * metatable
		 */
		lua_pushlightuserdata(_L, _target);
		lua_gettable(_L, LUA_REGISTRYINDEX);
		
		
		/**
		 * member
		 */
		lua_push(_L, v);
		
		lua_setfield(_L, -2, _member);
		lua_pop(_L, 1);
	}
	
	void setTarget(Target* target)
	{
		_target = target;
	}
};


#define LUA_CLASS_PROPERTY(L, type, target, member) lua_class_property_member<type, lua_class>(L, target, member)

#endif //__LUA_CLASS_PROPERTY_H__
