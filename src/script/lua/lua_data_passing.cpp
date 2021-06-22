This example code illustrates how to pass data between a C++ and a lua script. Read the comments and text output (cout and print statements) in the following two pieces of code.
After Running the Program

This is the output after running the code listed below.
[C++] Passing 'arg' array to script
[C++] Running script
[lua] These args were passed into the script from C
1       45
2       99
[lua] Script returning data back to C
[C++] These values were returned from the script
script returned 1
script returned 9
script returned a table
The C++ code

extern "C"
{
   #include <lua.h>
   #include <lauxlib.h>
   #include <lualib.h>
}
#include <iostream>

// a list of libs to expose for use in scripts
static const luaL_reg lualibs[] = 
{
  {"base", luaopen_base},
  {"table", luaopen_table},
  {"io", luaopen_io},
  {"string", luaopen_string},
  {"math", luaopen_math},
  {"debug", luaopen_debug},
  {"loadlib", luaopen_loadlib}, 
  /* add your libraries here */
  {NULL, NULL}
};

// load the list of libs
static void openstdlibs( lua_State *l ) 
{
  const luaL_reg *lib = lualibs;
  for (; lib->func; lib++) 
  {
    lib->func(l);  /* open library */
    lua_settop(l, 0);  /* discard any results */
  }
}

int main()
{
   int status;
   lua_State* state = lua_open();

  
   openstdlibs( state );
   status = luaL_loadfile( state, "args.lua" );

   std::cout << "[C++] Passing 'arg' array to script" << std::endl;

   // start array structure
   lua_newtable( state );

   // set first element "1" to value 45
   lua_pushnumber( state, 1 );
   lua_pushnumber( state, 45 );
   lua_rawset( state, -3 );

   // set second element "2" to value 99
   lua_pushnumber( state, 2 );
   lua_pushnumber( state, 99 );
   lua_rawset( state, -3 );
  
   // set the number of elements (index to the last array element)
   lua_pushliteral( state, "n" );
   lua_pushnumber( state, 2 );
   lua_rawset( state, -3 );

   // set the name of the array that the script will access
   lua_setglobal( state, "arg" );


   std::cout << "[C++] Running script" << std::endl;
   
   int result = 0;
   if (status == 0)
      result = lua_pcall( state, 0, LUA_MULTRET, 0 );
   else
      std::cout << "bad" << std::endl;
   
   if (result != 0)
      std::cerr << "[C++] script failed" << std::endl;

   std::cout << "[C++] These values were returned from the script" << std::endl;
   while (lua_gettop( state ))
   {
      switch (lua_type( state, lua_gettop( state ) ))
      {
         case LUA_TNUMBER: std::cout << "script returned " << lua_tonumber( state, lua_gettop( state ) ) << std::endl; break;
         case LUA_TTABLE:  std::cout << "script returned a table" << std::endl; break;
         case LUA_TSTRING: std::cout << "script returned " << lua_tostring( state, lua_gettop( state ) ) << std::endl; break;
         case LUA_TBOOLEAN:std::cout << "script returned " << lua_toboolean( state, lua_gettop( state ) ) << std::endl; break;
         default: std::cout << "script returned unknown param" << std::endl; break;
      }
      lua_pop( state, 1 );
   }
   lua_close( state );
   return 0;
}
The Lua Script "args.lua"

io.write( "[lua] These args were passed into the script from C\n" );

for i=1,table.getn(arg) do
   print(i,arg[i])
end

io.write("[lua] Script returning data back to C\n")

local temp = {}
temp[1]=9
temp[2]=8
temp[3]=7
temp[4]=6
temp[5]=5

return temp,9,1