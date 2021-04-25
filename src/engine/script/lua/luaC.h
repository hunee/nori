//
//  luaC.h
//  luaC
//
//  Created by Jang Jeonghun on 11/23/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef luaC_luaC_h
#define luaC_luaC_h



/**
 * lua
cavnas=Canvas{
	blend = {BLEND.SRC_ALPHA, BLEND.ONE_MINUS_SRC_ALPHA},
	texture0 = {
		tex = resource.loadByType(typename( 'png'), 'app://particle_10.png' ),
		sprited = false;
	},
};
*/

/**
 * cpp
Canvas::Canvas( TypeLua const& lua){
	lua_State* L(lua.getL());
	lua.get(L);
	
	if( !lua_istable(L,-1) ){
		LOG("Expected a table. (Canvas)");
		lua_pop(L,1);
		return;
	}
	
	lua_pushnil(L);
	while( lua_next(L, -2 ) ){
		if( lua_type( L, -2 ) == LUA_TSTRING ){
			char const* key = lua_tostring(L, -2);
			
			if( strcmp( key, "depth") == 0 ){
				int value = (int)lua_tonumber(L,-1);
				if( value < 0 || value > CF_DISABLED )
					LOG("Depth setting not applicable.");
				else
					mDepth.compareFunc = (CompareFunction)value;
			}
			
			else if( strcmp( key, "blend") == 0 ){
				if( lua_isboolean(L,-1) && lua_toboolean(L,-1)){
					mBlend.blendSrc = BF_DISABLED;
				}else if( lua_istable(L,-1) ){
					lua_rawgeti(L, -1, 1);
					int value = (int)lua_tonumber(L,-1);
					if( value < 0 || value > BF_DISABLED )
						LOG("Blend setting not applicable.");
					else
						mBlend.blendSrc = (BlendFactor)value;
					
					lua_rawgeti(L, -2, 2);
					value = (int)lua_tonumber(L,-1);
					if( value < 0 || value > BF_DISABLED )
						LOG("Blend setting not applicable.");
					else
						mBlend.blendDest = (BlendFactor)value;
					
					lua_rawgeti(L, -3, 3);
					value = (int)lua_tonumber(L,-1);
					if( value < 0 || value > BE_REV_SUBTRACT )
						LOG("Blend setting not applicable.");
					else
						mBlend.blendEq = (BlendEquation)value;
					
					lua_pop(L,3);
				}
			}
			
			else if( strcmp( key, "texture0") == 0 ){
				setTexture(L, mTex[0] );
			}
			
			else if( strcmp( key, "texture1") == 0 ){
				setTexture(L, mTex[1] );
			}
			
			else 
				LOG("Not a supported canvas setting.");
			
		};
		
		lua_pop(L,1);
	};
};
*/

#endif
