/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "StdAfx.h"

#include "lua_vm.h"

#include "lua_helper.h"

/**
 * lua_vm
 */
lua_vm* lua_vm::_self = 0;

lua_vm* lua_vm::sharedVM()
{
	if (_self == NULL)
	{
		_self = new lua_vm;
		
		///
		atexit(_dealloc);
	}
	
	return _self;
}

void lua_vm::_dealloc()
{
	if (_self)
	{
		SAFE_DELETE(_self);
	}
}


/**
 *
 */
lua_vm::lua_vm()
{
	_self = this;
	
	
	/**
	 * open lua
	 */
	_L = lua_open();
	luaL_openlibs(_L);
}

lua_vm::~lua_vm()
{
	_self = NULL;

	lua_gc(_L, LUA_GCCOLLECT, 0);  // collected garbage
	lua_close(_L);
}

int lua_vm::bootstrap(const char* path)
{
	if (lua_loadfile(_L, path) == FALSE)
		return FALSE;
	
	if (lua_pcall(_L, 0) == FALSE)
		return FALSE;
	
	lua_setmethod(_L, "main");
	lua_pcall(_L, 0);
	
	return TRUE;
}

void lua_vm::setpath(const char* path)
{
	lua_getglobal(_L, "package");
	lua_getfield(_L, -1, "path"); // get field "path" from table at top of stack (-1)
	
	const char* curpath = lua_tostring(_L, -1); // grab path string from top of stack

	char fullpath[PATH_MAX];
	strcpy(fullpath, curpath);
	strcat(fullpath, ";"); // do your path magic here
	strcat(fullpath, path);
	strcat(fullpath, "?.lua;");
	
	strcat(fullpath, curpath);
	strcat(fullpath, ";"); // do your path magic here
	strcat(fullpath, path);
	strcat(fullpath, "?.bin");
		
	lua_pop(_L, 1); // get rid of the string on the stack we just pushed on line 5
	
	lua_pushstring(_L, fullpath); // push the new one
	lua_setfield(_L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(_L, 1); // get rid of package table from top of stack
}

