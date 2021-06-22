/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef LUA_CLASS_DELEGATE_H
#define LUA_CLASS_DELEGATE_H

#include "delegate_impl.h"

#include "lua_class_ref.h"


/**
 * lua_class_delegate
 */
template <typename T, typename Target>
class lua_class_delegate : public lua_class_ref_<Target>, public delegate_impl<T> {
public:
	lua_class_delegate(lua_State* L, Target* target, const char* method)
	: lua_class_ref_<Target>(L, target, method)
	{
	}
	
	
	/**
	 *
	 */
	T operator() ()
	{
		lua_class_ref_<Target>::pushuserdata();
		
		return lua_class_ref_<Target>::pcall(1);
	}
	
	T operator() () const
	{
		return (*this) ();
	}	
};



/**
 * luaC_class_delegate_arg1
 */
template <typename T, typename Target, typename Arg>
class lua_class_delegate_arg1 : public lua_class_ref_<Target>, public delegate_arg1_impl<T, Arg> {
public:
	lua_class_delegate_arg1(lua_State* L, Target* target, const char* method)
	: lua_class_ref_<Target>(L, target, method)
	{
	}
	
	
	/**
	 *
	 */
	T operator() (Arg arg)
	{
		lua_class_ref_<Target>::pushuserdata();
		
		
		/**
		 * arg
		 */
		lua_push(lua_class_ref_<Target>::_L, arg);
		
		return lua_class_ref_<Target>::pcall(2);
	}
	
	T operator() (Arg arg) const
	{
		return (*this) (arg);
	}	
};

#define LUA_CLASS_DELEGATE(L, type, target, selector) lua_class_delegate<type, lua_class>(L, target, selector)
#define LUA_CLASS_DELEGATE_ARG1(L, type, target, arg1, selector) lua_class_delegate_arg1<type, lua_class, arg1>(L, target, selector)

#endif //LUA_CLASS_DELEGATE_H
