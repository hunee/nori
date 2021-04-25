/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_PROPERTY_H__
#define __LUA_PROPERTY_H__

#include "lua_property_impl.h"


/**
 *
 */
template <typename T, typename V>
class lua_property : public lua_property_impl {
	typedef V (T::*Getter)();
	typedef void (T::*Setter)(V);
	
	Getter _getter;
	Setter _setter;
	
public:
	lua_property(V (T::*getter)(), void (T::*setter)(V))
	: _getter(getter)
	, _setter(setter)
	{
		
	}
	
	void get(lua_State* L)
	{
		//printf("%s\n", __FUNCTION__);
		
		lua_userdata_impl<T>* udata = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		lua_push(L, ((T*)udata->_self->*_getter)());
	}
	void set(lua_State* L)
	{
		//printf("%s\n", __FUNCTION__);
		
		lua_userdata_impl<T>* udata = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		((T*)udata->_self->*_setter)(lua_to<V>(L, 3));
	}
};


/**
 *
 */
template <typename T, typename V>
class lua_property_member : public lua_property_impl {
	typedef V T::*M;
	M _member;
	
public:
	lua_property_member(V T::*member)
	: _member(member)
	{
		
	}
	
	void get(lua_State* L)
	{
		//printf("%s\n", __FUNCTION__);
		
		lua_userdata_impl<T>* udata = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		lua_push(L, udata->_self->*_member);
	}
	void set(lua_State* L)
	{
		//printf("%s\n", __FUNCTION__);
		
		lua_userdata_impl<T>* udata = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		udata->_self->*_member = lua_to<V>(L, 3);
	}
};


//#define DELEGATE(type, target, selector) delegate<type, target>(this, &target::selector)
//#define DELEGATE_ARGS1(type, target, arg, selector) delegate_arg1<type, target, arg>(this, &target::selector)
//#define DELEGATE_ARGS2(type, target, arg1, arg2, selector) delegate_arg2<type, target, arg1, arg2>(this, &target::selector)
//#define DELEGATE_ARGS3(type, target, arg1, arg2, arg3, selector) delegate_arg3<type, target, arg1, arg2, arg3>(this, &target::selector)

#endif //__LUA_PROPERTY_H__
