/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "asset/asset_manager.h"

#include "renderer/texture.h"
#include "renderer/shader.h"

#include "lua.h"

extern "C" {
  #include "lua-5.4.1/src/lua.h"
  #include "lua-5.4.1/src/lauxlib.h"
  #include "lua-5.4.1/src/lualib.h"
}

namespace ext {

std::shared_ptr<ICLASS(asset)> lua_shader::import(const std::string& pathname)
{
  //CLOGF();

  //auto p = std::make_shared<asset_ptr<GLtexture>>(pathname);
  auto p = std::make_shared<asset<GL::shader>>();
      

  //throw std::runtime_error("Exception PNG 3!\n");

  lua_State* L = luaL_newstate();
  if (nullptr == L)
  {
    std::cout << "Lua state(environment) assign failed" << std::endl;
    return nullptr;
  }
    
  luaL_openlibs(L);

  if (luaL_loadfile(L, pathname.c_str()))
  {
    std::cout << "Lua loadfile failed" << std::endl;
    return nullptr;
  }

  if (lua_pcall(L, 0, LUA_MULTRET, 0))
  {
    std::cerr << "[C++] script failed" << std::endl;
    return nullptr;
  }

/*
    //return
   //while (lua_gettop( L ))
   {
      switch (lua_type( L, lua_gettop( L ) ))
      {
         case LUA_TNUMBER: std::cout << "script returned " << lua_tonumber( L, lua_gettop( L ) ) << std::endl; break;
         case LUA_TTABLE:  std::cout << "script returned a table" << std::endl; break;
         case LUA_TSTRING: std::cout << "script returned " << lua_tostring( L, lua_gettop( L ) ) << std::endl; break;
         case LUA_TBOOLEAN:std::cout << "script returned " << lua_toboolean( L, lua_gettop( L ) ) << std::endl; break;
         default: std::cout << "script returned unknown param" << std::endl; break;
      }
      //lua_pop( L, 1 );
   }
*/

  lua_getglobal(L, "shader");

  if (!lua_istable(L, -1))
  {
    std::cout << "Expected a table. (Shader)" << std::endl;
    lua_pop(L, 1);

    return nullptr;
  }

COUT << "AAAAAAA" << ENDL;

  lua_pushnil(L);
  while (lua_next(L, -2) != 0) 
  {
    if (lua_type(L, -2) == LUA_TSTRING)
    {
      auto key = lua_tostring(L, -2);
      std::cout << "-2: " << key << std::endl;

      //DEPTH
      if (strcmp( key, "SubShader") == 0)
      {
        if (lua_istable(L, -1))
        {
          COUT << "subshader" << ENDL;

          lua_pushnil(L);
          while (lua_next(L, -2) != 0) 
          {
            if (lua_type(L, -2) == LUA_TSTRING)
            {
              auto key = lua_tostring(L, -2);
              std::cout << "-2: " << key << std::endl;        
            }

            lua_pop(L, 1); 
          }
        }        
      }

      //DEPTH
      else if (strcmp( key, "depth") == 0)
      {
        COUT << "DEPTH" << ENDL;

        int value = (int)lua_tonumber(L,-1);
        //if( value < 0 || value > CF_DISABLED )
          //LOG("Depth setting not applicable.");
        //else
          //mDepth.compareFunc = (CompareFunction)value;
      }

      //BLEND
      else if (strcmp(key, "blend") == 0)
      {
        COUT << "BLEND" << ENDL;

        if (lua_isboolean(L, -1) && lua_toboolean(L, -1))
        {
          //mBlend.blendSrc = BF_DISABLED;
          //glEnable(GL_BLEND);
        }
        else if (lua_istable(L, -1))
        {
          lua_rawgeti(L, -1, 1);
          int value = (int)lua_tonumber(L, -1);
          std::cout << value << std::endl;
          //if( value < 0 || value > BF_DISABLED )
        //		LOG("Blend setting not applicable.");
          //else
          //	mBlend.blendSrc = (BlendFactor)value;
          
          lua_rawgeti(L, -2, 2);
          value = (int)lua_tonumber(L, -1);
          std::cout << value << std::endl;

          //if( value < 0 || value > BF_DISABLED )
          //	LOG("Blend setting not applicable.");
          //else
          //	mBlend.blendDest = (BlendFactor)value;
          //glBlendFunc

          lua_rawgeti(L, -3, 3);
          value = (int)lua_tonumber(L, -1);
          std::cout << value << std::endl;
          //if( value < 0 || value > BE_REV_SUBTRACT )
          //	LOG("Blend setting not applicable.");
          //else
          //	mBlend.blendEq = (BlendEquation)value;
          // glBlendEquation

          lua_pop(L, 3);
        }
      }
    }

    lua_pop(L, 1); 
  }

  lua_close(L);

  return p;
}

}; //ext