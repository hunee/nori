/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_VM_H__
#define __LUA_VM_H__

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

/**
 *
 */
class lua_vm {
private:
	lua_State* _L;
	
public:
	lua_vm();
	~lua_vm();
	
public:	
	int bootstrap(const char* path);
	
public:
	lua_State* get() const
	{
		return _L;
	}

	void setpath(const char* path);
	
public:
	static void _dealloc();

	static lua_vm* sharedVM();
	static lua_vm* self()
	{
		return _self;
	}
	
	static lua_vm* _self;	
};

#endif //__LUA_VM_H__
