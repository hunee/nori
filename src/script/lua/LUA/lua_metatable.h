/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __LUA_METATABLE_H__
#define __LUA_METATABLE_H__


extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <new>


#include "lua_userdata.h"
#include "lua_property.h"


template <typename M>
static void lua_push_method_userdata(lua_State* L, M method)
{
	union {
		M m;
		unsigned char b[sizeof(M)];
	} _mu;
	
	_mu.m = method;
	
	unsigned char* ptr = (unsigned char *) lua_newuserdata(L, sizeof(M));
	for (size_t i=0; i<sizeof(M); ++i)
		ptr[i] = _mu.b[i];
}


/**
 *
 */
template<typename T>
class lua_metatable {
public:
	static const char* _name;
	
public:
	static int __gc_T(lua_State* L)
	{
		//TRACEF();
		
		lua_userdata_impl<T>* udata = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		if (udata)
			udata->~lua_userdata_impl();
		
		return 0;
	}
	
	static int __call_T(lua_State* L)
	{
		//TRACEF();
		
		lua_remove(L, 1);
		
		
		/**
		 *
		 */
		new (lua_newuserdata(L, sizeof(lua_userdata<T>))) lua_userdata<T>(L);
		
		
		/**
		 *
		 */
		setmetatable(L);
		lua_setmetatable(L, -2);
		
		return 1;
	}
	
	static int __tostring_T(lua_State* L)
	{
		//TRACEF();
		
		char buff[32];
		lua_userdata_impl<T>* ud = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		sprintf(buff, "%p", ud->_self);
		
		lua_pushfstring(L, "%s (%s)", _name, buff);
		
		return 1;
	}
	
	static int __index_T(lua_State* L)
	{
		//TRACEF();
		
		//lua_checknarg(L);
		
		/**
		 *
		 */
		lua_getmetatable(L, 1);
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);
		
		if (lua_isuserdata(L, -1))
		{
			lua_property_impl* property = static_cast<lua_property_impl*>(lua_touserdata(L, -1));
			property->get(L);
			
			lua_remove(L, -2);
		}
		else if (lua_isnil(L, -1))
		{
			lua_remove(L, -1);
		}
		
		lua_remove(L, -2);
		
		return 1;
	}
	
	static int __newindex_T(lua_State* L)
	{
		//TRACEF();
		
		//lua_checknarg(L);
		
		lua_getmetatable(L, 1);
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);
		
		if (lua_isuserdata(L, -1))
		{
			lua_property_impl* property = static_cast<lua_property_impl*>(lua_touserdata(L, -1));
			property->set(L);
		}
		else if (lua_isnil(L, -1))
		{
			lua_pushvalue(L, 2);
			lua_pushvalue(L, 3);
			lua_rawset(L, -4);
		}
		
		lua_settop(L, 3);
		
		return 0;
	}
	
	static int invoke_T(lua_State* L)
	{
		//TRACEF();
		
		//lua_checknarg(L);
		
		lua_userdata_impl<T>* ud = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, 1));
		if (!ud)
		{
			luaL_typerror(L, 1, _name);
			
			return 0;
		}
		
		lua_remove(L, 1);
		
		typedef int (T::*M)(lua_State* L);
		M* methodptr = static_cast<M*> (lua_touserdata(L, lua_upvalueindex(1)));
		
		M method = *methodptr;
		return ((T*)ud->_self->*method)(L);
	}
	
	static void pushuserdata(lua_State* L, T* self)
	{
		new (lua_newuserdata(L, sizeof(lua_userdata_impl<T>))) lua_userdata_impl<T>(self);
		
		setmetatable(L);
		lua_setmetatable(L, -2);
	}
	
	
	static T* touserdata(lua_State* L, int idx)
	{
		lua_userdata_impl<T>* udata = static_cast<lua_userdata_impl<T>*>(lua_touserdata(L, idx));
		if (!udata)
			luaL_typerror(L, idx, _name);
		
		return udata->_self;
	}
	
	static void setmetatable(lua_State* L)
	{
		lua_pushstring(L, _name);
		lua_gettable(L, LUA_GLOBALSINDEX);
	}
	
	static void newtable(lua_State* L, const char* name)
	{
		_name = name;
		

		/**
		 *
		 */
		lua_pushstring(L, _name);
		lua_newtable(L);

		
		/**
		 *
		 */
		lua_pushvalue(L, -1);
		lua_pushstring(L, "__mode");
		lua_pushstring(L, "v");
		lua_rawset(L, -3);
		lua_setmetatable(L, -2);
		
		/**
		 *
		 */
		lua_pushstring(L, "__index");
		lua_pushcclosure(L, __index_T, 0);
		lua_rawset(L, -3);
		
		lua_pushstring(L, "__newindex");
		lua_pushcclosure(L, __newindex_T, 0);
		lua_rawset(L, -3);
		
		lua_pushstring(L, "__tostring");
		lua_pushcclosure(L, __tostring_T, 0);
		lua_rawset(L, -3);
		
		lua_pushstring(L, "__gc");
		lua_pushcclosure(L, __gc_T, 0);
		lua_rawset(L, -3);

		
		/**
		 *
		 */
		lua_newtable(L);
		lua_pushstring(L, "__call");
		lua_pushcclosure(L, __call_T, 0);
		lua_rawset(L, -3);
		lua_setmetatable(L, -2);
		
		lua_settable(L, LUA_GLOBALSINDEX);
	}
	
	static void bind_method(lua_State* L, const char* name, int (T::*method)(lua_State* L))
	{
		setmetatable(L);
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, name);
			lua_push_method_userdata(L, method);
			
			lua_pushcclosure(L, invoke_T, 1);
			lua_rawset(L, -3);
		}
		
		lua_pop(L, 1);
	}

	static void bind_method(lua_State* L, const char* name, int (*method)(lua_State* L))
	{
		setmetatable(L);
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, name);
			lua_pushcclosure(L, method, 0);
			lua_rawset(L, -3);
		}
		
		lua_pop(L, 1);
	}
	
	template <typename V>
	static void bind_member(lua_State* L, const char *name, V T::*member)
	{
		setmetatable(L);
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, name);
			
			new (lua_newuserdata(L, sizeof(lua_property_member<T, V>))) lua_property_member<T, V>(member);
			
			lua_rawset(L, -3);
		}
		
		lua_pop(L, 1);
	}
	
	template <typename V>
	static void bind_property(lua_State* L, const char *name, V (T::*getter)(), void (T::*setter)(V))
	{
		setmetatable(L);
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, name);
			
			new (lua_newuserdata(L, sizeof(lua_property<T, V>))) lua_property<T, V>(getter, setter);
			
			lua_rawset(L, -3);
		}
		
		lua_pop(L, 1);
	}
};


template < typename T >
const char* lua_metatable<T>::_name = "<undefined>";

#endif //__LUA_METATABLE_H__
