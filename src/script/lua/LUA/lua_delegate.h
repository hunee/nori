/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_DELEGATE_H__
#define __LUA_DELEGATE_H__

#include "delegate_impl.h"

#include "lua_ref.h"


/**
 * lua_delegate
 */
template <typename T, typename Target>
class lua_delegate : public lua_ref_<Target>, public delegate_impl<T> {
public:
	lua_delegate(lua_State* L, Target* self, const char* method)
	: lua_ref_<Target>(L, method, self)
	{
	}

	
	/**
	 *
	 */
	T operator() ()
	{
		lua_ref_<Target>::pushuserdata();

		return lua_ref_<Target>::pcall(1);
	}
	
	T operator() () const
	{
		return (*this) ();
	}	
};


template <typename T, typename Target, typename Arg>
class lua_delegate_arg1 : public lua_ref_<Target>, public delegate_arg1_impl<T, Arg> {
public:
	lua_delegate_arg1(lua_State* L, Target* self, const char* method)
	: lua_ref_<Target>(L, method, self)
	{
	}
	

	/**
	 *
	 */
	T operator()(Arg arg)
	{
		lua_ref_<Target>::pushuserdata();
		
		
		/**
		 * arg
		 */
		lua_push(lua_ref_<Target>::_L, arg);
		
		return lua_ref_<Target>::pcall(2);
	}
	
	T operator() (Arg arg) const
	{
		return (*this) (arg);
	}	
};


template <typename T, typename Target, typename Arg1, typename Arg2>
class lua_delegate_arg2 : public lua_ref_<Target>, public delegate_arg2_impl<T, Arg1, Arg2> {
public:
	lua_delegate_arg2(lua_State* L, Target* self, const char* method)
	: lua_ref_<Target>(L, method, self)
	{
	}
	

	/**
	 *
	 */
	T operator() (Arg1 arg1, Arg2 arg2)
	{
		lua_ref_<Target>::pushuserdata();
		
		
		/**
		 * arg
		 */
		lua_push(lua_ref_<Target>::_L, arg1);
		lua_push(lua_ref_<Target>::_L, arg2);
		
		return lua_ref_<Target>::pcall(3);
	}
	
	T operator() (Arg1 arg1, Arg2 arg2) const
	{
		return (*this)(arg1, arg2);
	}	
};

template <typename T, typename Target, typename Arg1, typename Arg2, typename Arg3>
class lua_delegate_arg3 : public lua_ref_<Target>, public delegate_arg3_impl<T, Arg1, Arg2, Arg3> {
public:
	lua_delegate_arg3(lua_State* L, Target* self, const char* method)
	: lua_ref_<Target>(L, method, self)
	{
	}
	

	/**
	 *
	 */
	T operator() (Arg1 arg1, Arg2 arg2, Arg3 arg3)
	{
		lua_ref_<Target>::pushuserdata();
		
		
		/**
		 * arg
		 */
		lua_push(lua_ref_<Target>::_L, arg1);
		lua_push(lua_ref_<Target>::_L, arg2);
		lua_push(lua_ref_<Target>::_L, arg3);
		
		return lua_ref_<Target>::pcall(4);
	}
	
	T operator() (Arg1 arg1, Arg2 arg2, Arg3 arg3) const
	{
		return (*this)(arg1, arg2, arg3);
	}	
};

#define LUA_DELEGATE(L, type, target, selector) lua_delegate<type, target>(L, this, selector)
#define LUA_DELEGATE_ARGS1(L, type, target, arg, selector) lua_delegate_arg1<type, target, arg>(L, this, selector)
#define LUA_DELEGATE_ARGS2(L, type, target, arg1, arg2, selector) lua_delegate_arg2<type, target, arg1, arg2>(L, this, selector)
#define LUA_DELEGATE_ARGS3(L, type, target, arg1, arg2, arg3, selector) lua_delegate_arg3<type, target, arg1, arg2, arg3>(L, this, selector)

#define LUA_DELEGATE_TARGET(L, type, target, self, selector) lua_delegate<type, target>(L, dynamic_cast<target*>(self), selector)
#define LUA_DELEGATE_TARGET_ARGS1(L, type, target, self, arg, selector) lua_delegate_arg1<type, target, arg>(L, self, selector)
#define LUA_DELEGATE_TARGET_ARGS2(L, type, target, self, arg1, arg2, selector) lua_delegate_arg2<type, target, arg1, arg2>(L, self, selector)
#define LUA_DELEGATE_TARGET_ARGS3(L, type, target, self, arg1, arg2, arg3, selector) lua_delegate_arg3<type, target, arg1, arg2, arg3>(L, self, selector)

#endif //__LUA_DELEGATE_H__
