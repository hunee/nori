/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "StdAfx.h"

#include "lua_helper.h"

#include "lua_metatable.h"


/**
 * lua_push...
 */
template <>
void lua_push(lua_State* L, char* val)
{
	lua_pushstring(L, val);
}

template <>
void lua_push(lua_State* L, const char* val)
{
	lua_pushstring(L, val);
}

template <>
void lua_push(lua_State* L, bool val)
{
	lua_pushboolean(L, val);
}

template <>
void lua_push(lua_State* L, int val)
{
	lua_pushinteger(L, val);
}

template <>
void lua_push(lua_State* L, unsigned int val)
{
	lua_pushinteger(L, val);
}

template <>
void lua_push(lua_State* L, float val)
{
	lua_pushnumber(L, val);
}

template <>
void lua_push(lua_State* L, double val)
{
	lua_pushnumber(L, val);
}

template <>
void lua_push(lua_State* L, void* val)
{
	lua_pushlightuserdata(L, val);
}

template <>
void lua_push(lua_State* L, const void* val)
{
	lua_pushlightuserdata(L, (void*) val);
}

/**
 * lua_to...
 */
template <>
int lua_to(lua_State* L, int idx)
{
	return (int) lua_tonumber(L, idx);
}

template <>
bool lua_to(lua_State* L, int idx)
{
	return (int) lua_toboolean(L, idx);
}

template <>
char* lua_to(lua_State* L, int idx)
{
	return (char*) lua_tostring(L, idx);
}

template <>
const char* lua_to(lua_State* L, int idx)
{
	return (const char*) lua_tostring(L, idx);
}

template <>
unsigned int lua_to(lua_State* L, int idx)
{
	return (unsigned int) lua_tonumber(L, idx);
}

template <>
float lua_to(lua_State* L, int idx)
{
	return (float) lua_tonumber(L, idx);
}

template <>
double lua_to(lua_State* L, int idx)
{
	return lua_tonumber(L, idx);
}

template <>
void* lua_to(lua_State* L, int idx)
{
	return (void*) lua_topointer(L, idx);
}

template <>
const void* lua_to(lua_State* L, int idx)
{
	return lua_topointer(L, idx);
}


/**
 * loadfile
 */
int lua_loadfile(lua_State* L, const char* path)
{
	if (luaL_loadfile(L, path))
	{
		const char* msg = lua_tostring(L, -1);
		if (msg == NULL)
			msg = "(error with no message)";
		
		TRACEA("ERROR: %s\n", msg);
		lua_pop(L, 1);
		
		return FALSE;
	}
	
	return TRUE;
}


/**
 * traceback (from lua.c)
 */
int lua_traceback(lua_State* L)
{
	if (!lua_isstring(L, 1))	// 'message' not a string?
		return 1;								// keep it intact
	
	lua_getfield(L, LUA_GLOBALSINDEX, "debug");
	if (!lua_istable(L, -1))
	{
		lua_pop(L, 1);
		return 1;
	}
	
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1))
	{
		lua_pop(L, 2);
		return 1;
	}
	
	lua_pushvalue(L, 1);			// pass error message
	lua_pushinteger(L, 2);		// skip this function and traceback
	lua_call(L, 2, 1);				// call debug.traceback
	
	return 1;
}

int lua_setmethod(lua_State* L, const char* method)
{
  lua_pushstring(L, method);
  lua_gettable(L, LUA_GLOBALSINDEX);
	if (!lua_isfunction(L, -1))
		return FALSE;
	
	return TRUE;
}

int lua_pcall(lua_State* L, int narg)
{
	int base = lua_gettop(L) - narg;					// function index
	lua_pushcfunction(L, lua_traceback);			// push traceback function
	lua_insert(L, base);											// put it under chunk and args
	
	int status = lua_pcall(L, narg, /*0*/LUA_MULTRET, base);
	lua_remove(L, base);											// remove traceback function
	
	if (status)
	{
		const char* msg = lua_tostring(L, -1);
		if (msg == NULL)
			msg = "(error with no message)";
		
		TRACEA("ERROR: %s\n", msg);
		lua_pop(L, 1);
		
		return FALSE;
	}
	
	return TRUE;
}

static const char* _lua_type_name[] =
{
	"LUA_TNIL",
	"LUA_TBOOLEAN",
	"LUA_TLIGHTUSERDATA",
	"LUA_TNUMBER",
	"LUA_TSTRING",
	"LUA_TTABLE",
	"LUA_TFUNCTION",
	"LUA_TUSERDATA",
	"LUA_TTHREAD",
};

const char* lua_typename(int type)
{
	return _lua_type_name[type];
}

class T {};

const char* lua_typetostring(lua_State* L, int idx)
{
	static char _typename[PATH_MAX];
	
	int type = lua_type(L, idx);
	//TRACELA(" (%s): ", lua_typename(type));
	switch (type)
	{
		case LUA_TNIL:
			break;
		case LUA_TBOOLEAN:
			sprintf(_typename, "%s", lua_toboolean(L, idx) ? "TRUE" : "FALSE");
			break;
		case LUA_TLIGHTUSERDATA:
			sprintf(_typename, "%p", lua_touserdata(L, idx));
			break;
		case LUA_TNUMBER:
			sprintf(_typename, "%ld", lua_tointeger(L, idx));
			break;
		case LUA_TSTRING:
			sprintf(_typename, "%s", lua_tostring(L, idx));
			break;
		case LUA_TTABLE:
		{
			lua_pushnil(L);
			
			while (lua_next(L, -2))
			{
				TRACEA("->> %s: %s = ", lua_typename(lua_type(L, -1)), lua_typetostring(L, -2));
				TRACELA("%s\n", lua_typetostring(L, -1));
				
				lua_pop(L, 1);
			};
		}
			break;
		case LUA_TFUNCTION:
			break;
		case LUA_TUSERDATA:
		{
			lua_userdata<T>* udata = static_cast<lua_userdata<T>*>(lua_touserdata(L, idx));
			sprintf(_typename, "%p", udata->_self);
		}
			break;
		case LUA_TTHREAD:
			break;
	}
	
	return _typename;
}

int lua_checknarg(lua_State* L)
{
	int narg = lua_gettop(L);
	//TRACEA("->> narg: %d\n", narg);
	
	for (int n=1; n<narg+1; ++n)
	{
		int type = lua_type(L, n);
		TRACEA("->> arg%d (%s): ", n, lua_typename(type));
		switch (type)
		{
			case LUA_TNIL:
				break;
			case LUA_TBOOLEAN:
				TRACELA("%s", lua_toboolean(L, n) ? "TRUE" : "FALSE");
				break;
			case LUA_TLIGHTUSERDATA:
				TRACELA("%p", lua_touserdata(L, n));
				break;
			case LUA_TNUMBER:
				TRACELA("%d", lua_tointeger(L, n));
				break;
			case LUA_TSTRING:
				TRACELA("%s", lua_tostring(L, n));
				break;
			case LUA_TTABLE:
			{
				lua_pushnil(L);
				
				while (lua_next(L, -2))
				{
					TRACELA("\n");
					
					TRACEA("->> %s: %s = ", lua_typename(lua_type(L, -1)), lua_typetostring(L, -2));
					TRACELA("%s", lua_typetostring(L, -1));
					
					lua_pop(L, 1);
				};
				//lua_pop(L, 1);
			}
				break;
			case LUA_TFUNCTION:
				break;
			case LUA_TUSERDATA:
			{
				lua_userdata<T>* udata = static_cast<lua_userdata<T>*>(lua_touserdata(L, n));
				TRACELA("%p", udata->_self);
			}
				break;
			case LUA_TTHREAD:
				break;
		}
		TRACELA("\n");
	}
	
	return narg;
}


