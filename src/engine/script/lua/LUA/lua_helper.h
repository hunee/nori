/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef LUA_HELPER_H
#define LUA_HELPER_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}



/**
 * traceback (from lua.c)
 */
int lua_traceback(lua_State* L);


/**
 * pcall
 */
int lua_setmethod(lua_State* L, const char* method);
int lua_pcall(lua_State* L, int narg);

int lua_loadfile(lua_State* L, const char* path);

const char* lua_typename(int type);
const char* lua_typetostring(lua_State* L, int idx);

int lua_checknarg(lua_State* L);



/**
 * lua helper
 */

//lua_push...
template<typename T>
void lua_push(lua_State* L, T val) {}

template <> void lua_push(lua_State* L, bool val);
template <> void lua_push(lua_State* L, int val);
template <> void lua_push(lua_State* L, unsigned int val);
template <> void lua_push(lua_State* L, float val);
template <> void lua_push(lua_State* L, double val);
template <> void lua_push(lua_State* L, char* val);
template <> void lua_push(lua_State* L, const char* val);
template <> void lua_push(lua_State* L, void* val);
template <> void lua_push(lua_State* L, const void* val);

//lua_to...
template<typename T>
T lua_to(lua_State* L, int idx) { return 0; }

template <> bool lua_to(lua_State* L, int idx);
template <> int lua_to(lua_State* L, int idx);
template <> unsigned int lua_to(lua_State* L, int idx);
template <> float lua_to(lua_State* L, int idx);
template <> double lua_to(lua_State* L, int idx);
template <> char* lua_to(lua_State* L, int idx);
template <> const char* lua_to(lua_State* L, int idx);
template <> void* lua_to(lua_State* L, int idx);
template <> const void* lua_to(lua_State* L, int idx);

#endif //LUA_HELPER_H
