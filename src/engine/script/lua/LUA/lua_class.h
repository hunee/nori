/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_CLASS_H__
#define __LUA_CLASS_H__

#include "lua_helper.h"

#include <new>



class lua_class;

template <> void lua_push(lua_State* L, lua_class* val);
template <> lua_class* lua_to(lua_State* L, int idx);


/**
 *
 */
class lua_class {
public:
	/**
	 * bind the lua object to a self table at index
	 */
	lua_class(lua_State* L, int idx)
	{
		//TRACEC();
		
		//Push the index onto the stack
		lua_pushvalue(L, idx);
		
		//Store the __c_pointer in the script table
		lua_pushstring(L, "this");
		lua_pushlightuserdata(L, this);
		lua_settable(L, -3);
		
		//Map the engine side pointer to the script side table through the lua registry.
		lua_pushlightuserdata(L, this);	
		lua_pushvalue(L, -2);
		lua_settable(L, LUA_REGISTRYINDEX);
		
		lua_pop(L, -1);
	}
	
	void pcall(lua_State* L, const char* method)
	{
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		lua_pushstring(L, method);
		lua_gettable(L, -2);
		lua_pushvalue(L, -2);
		lua_pcall(L, 1, 0, 0);
	}
	
	void pcall(lua_State* L, const char* method, const char* arg1)
	{
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		lua_pushstring(L, method);
		lua_gettable(L, -2);
		lua_pushvalue(L, -2);
		lua_pushstring(L, arg1);
		lua_pcall(L, 2, 0, 0);
	}
	
public:
	//called in lua to create a new lua object and bind the script/c++ sides
	static int bind(lua_State* L)
	{
		//Arg 1 is the "self" table from script.
		//lua_class* lc = new lua_class(L, 1);

		new (lua_newuserdata(L, sizeof(lua_class))) lua_class(L, 1);
		
		return 0;
	}
};
//lua_register(_L, "bind_class", lua_class::_alloc);


/**
 *
 */
class lua_shared_class : public lua_class {
public:
	lua_shared_class(lua_State* L, int idx)
	: lua_class(L, idx)
	{
		_self = this;
	}
	
	static lua_shared_class* self()
	{
		return _self;
	}
	static lua_shared_class* _self;
	
	//called in lua to create a new lua object and bind the script/c++ sides
	static int bind(lua_State *L)
	{
		//Arg 1 is the "self" table from script.
		//lua_shared_class* lc = new lua_shared_class(L, 1);
		new (lua_newuserdata(L, sizeof(lua_shared_class))) lua_shared_class(L, 1);
		
		return 0;
	}
};


//lua_register(_L, "bind_shared_class", lua_shared_class::_alloc);

#endif //__LUA_CLASS_H__
