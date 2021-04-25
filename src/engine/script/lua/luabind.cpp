// sqbind.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "luabind.h"

#include "lua_helper.h"
#include "lua_metatable.h"

#include "lua_delegate.h"
#include "lua_class_delegate.h"

#include "lua_class.h"

#include "property.h"

#include "lua_class_property.h"

class View;

template <> void lua_push(lua_State* L, View* val);
template <> View* lua_to(lua_State* L, int idx);


template <>
void lua_push(lua_State* L, View* val)
{
	lua_metatable<View>::pushuserdata(L, val);
}

template <>
View* lua_to(lua_State* L, int idx)
{
	return lua_metatable<View>::touserdata(L, idx);
}


class T;

#include "lua_userdata.h"

#define is_type_equal(T1, T2) typeid(T1) == typeid(T2)


template <typename T>
T get(property_ptr* p)
{
	property_impl<T>* ip = dynamic_cast<property_impl<T>*> (p);
	return ip->get();
}

template <typename T>
void set(property_ptr* p, T v)
{
	property_impl<T>* ip = dynamic_cast<property_impl<T>*> (p);
	return ip->set(v);
}


struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

struct _object_info {
public:
	virtual ~_object_info() {}
	
	virtual int id() =0;
	virtual const char* name() =0;
};

/**
 * object_type
 */
template<typename T>
struct _type {
	static int type;
	static const char* name;
};

template<typename T>
int _type<T>::type = 0;

template<typename T>
const char* _type<T>::name = "<undefined>";


/**
 *
 */
template <typename T>
struct _type_info : public _type<T>, public _object_info {
	int id() { return _type<T>::type; }
	const char* name() { return _type<T>::name; }
};


class object;
template<>
int _type<object>::type = 1;

template<>
const char* _type<object>::name = "<object>";


/**
 *
 */
template <typename T>
class _method;

template<>
int _type<_method<int>>::type = 2;

template<>
const char* _type<_method<int>>::name = "<method<int>>";


template<>
int _type<_method<const char*>>::type = 2;

template<>
const char* _type<_method<const char*>>::name = "<method<const char*>>";

/**
 *
 */
template <typename T>
class _member;

template<>
int _type<_member<int>>::type = 2;

template<>
const char* _type<_member<int>>::name = "<member<int>>";


/**
 *
 */
template <typename T>
class _property;

template<>
int _type<_property<int>>::type = 2;

template<>
const char* _type<_property<int>>::name = "<property<int>>";


template <typename T>
class _method : public _type_info<_method<T>> {
public:
};

template <typename T, typename Target>
class type_method : public _method<T> {
	typedef T (Target::*Selector) ();
public:
};


/**
 *
 */
template <typename T>
class _member : public _type_info<_member<T>> {
};

template <typename T, typename Target>
class type_member : public _member<T> {
	typedef T Target::*Member;
};

/**
 *
 */
template <typename T>
class _property : public _type_info<_property<T>> {
};

template <typename T, typename Target>
class type_property : public _property<T> {
	typedef T Target::*Member;
};

/**
 *
 */
class object : public _type_info<object> {
	hash_map<const char*, _object_info*, std::hash<const char*>, eqstr> _vtable;

public:
	object()
	{
		printf("->> size = %ld\n", sizeof(object));

		_vtable.insert(std::make_pair("id", new type_method<int, object>()));
		_vtable.insert(std::make_pair("name", new type_method<const char*, object>()));
		_vtable.insert(std::make_pair("i", new type_member<int, object>()));
		_vtable.insert(std::make_pair("j", new type_property<int, object>()));

		printf("->> id.name = %s\n", (_vtable["id"])->name());
		printf("->> name.name = %s\n", (_vtable["name"])->name());
		printf("->> i.name = %s\n", (_vtable["i"])->name());
		printf("->> j.name = %s\n", (_vtable["j"])->name());
	}
	
	int _i;
};

template <typename T>
T _lua_get(lua_State* L, void* target, const char* member)
{
	/**
	 * metatable
	 */
	lua_pushlightuserdata(L, target);
	lua_gettable(L, LUA_REGISTRYINDEX);


	/**
	 * member
	 */
	lua_getfield(L, -1, member);

	T v = lua_to<T>(L, -1);

	lua_pop(L, 1);

	return v;
}

template <typename T>
void _lua_set(lua_State* L, void* target, const char* member, T v)
{
	/**
	 * metatable
	 */
	lua_pushlightuserdata(L, target);
	lua_gettable(L, LUA_REGISTRYINDEX);
	
	
	/**
	 * member
	 */
	lua_push(L, v);
	
	lua_setfield(L, -2, member);
	lua_pop(L, 1);
}


struct _lua_userdata {};
struct _lua_lightuserdata {};

struct _lua_table {};
struct _lua_function {};


template <typename T>
struct _lua_type_info : public _type_info<T> {

};

template <typename T>
struct _lua_type : public _lua_type_info<T> {
	T get(lua_State* L, void* target, const char* member)
	{
		return _lua_get<T>(L, target, member);
	}
	void set(lua_State* L, void* target, T v, const char* member)
	{
		_lua_set(L, target, member, v);
	}
};

template<>
struct _lua_type<_lua_userdata> : public _type_info<_lua_userdata> {
	
};



template<>
struct _lua_type<_lua_function> : public _type_info<_lua_function> {
	int _ref;
	
	_lua_type<_lua_function>()
	{
	}

	~_lua_type<_lua_function>()
	{
		//luaL_unref(L, LUA_REGISTRYINDEX, _ref);
	}
	
	inline int pcall(lua_State* L, int narg)
	{
		int base = lua_gettop(L) - narg;					// function index
		lua_pushcfunction(L, lua_traceback);			// push traceback function
		lua_insert(L, base);											// put it under chunk and args
		
		int status = lua_pcall(L, narg, 0, base);
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
	
	int is_function(lua_State* L, void* target, const char* method)
	{
		/**
		 * metatable
		 */
		lua_pushlightuserdata(L, target);
		lua_gettable(L, LUA_REGISTRYINDEX);
		
		
		/**
		 * method
		 */
		lua_pushstring(L, method);
		lua_gettable(L, -2);
		if (!lua_isfunction(L, -1))
			return FALSE;
		
		_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		
		// ??
		//lua_pop(_L, 1);
		
		return TRUE;
	}
	int operator() (lua_State* L, void* target)
	{
		/**
		 * set ref (fast???)
		 */
		lua_rawgeti(L, LUA_REGISTRYINDEX, _ref);
		
		// push userdata
		lua_pushlightuserdata(L, target);
		lua_gettable(L, LUA_REGISTRYINDEX);
		
		//lua_push(L, arg);
	
		return pcall(L, 1);
	}

	int operator() (lua_State* L, void* target) const
	{
		return (*this) (L, target);
	}
};


template<>
struct _lua_type<_lua_table> : public _type_info<_lua_table> {
	hash_map<std::string, _object_info*> _field;
	
	void parser(lua_State* L)
	{
		lua_pushnil(L);
		
		while (lua_next(L, -2))
		{
			char ikey[8];
			
			int nkey = 0;
			const char* key = NULL;
			
			if (lua_type(L, -2) == LUA_TSTRING)
			{
				key = lua_to<const char*>(L, -2);
				
				//TRACEA("->> %s", key);
			}
			else
			{
				nkey = lua_to<int>(L, -2);

				_itoa(nkey, ikey, 10);
				key = ikey;
				
				//TRACEA("->> %d", nkey);
			}
			
			
			int type = lua_type(L, -1);
			
			//TRACELA(" (%s): ", lua_typename(type));
			switch (type)
			{
				case LUA_TNIL:
					break;
				case LUA_TBOOLEAN:
					//TRACELA("%s", lua_toboolean(L, -1) ? "TRUE" : "FALSE");
				{
					_field.insert(std::make_pair(key, new _lua_type<bool>()));
				}
					break;
				case LUA_TNUMBER:
					//TRACELA("%d", lua_tointeger(L, -1));
				{
					_field.insert(std::make_pair(key, new _lua_type<int>()));
				}
					break;
				case LUA_TSTRING:
					//TRACELA("%s", lua_tostring(L, -1));
				{
					_field.insert(std::make_pair(key, new _lua_type<const char*>()));
				}
					break;
				case LUA_TLIGHTUSERDATA:
					//TRACELA("%p", lua_touserdata(L, -1));
				{
					_field.insert(std::make_pair(key, new _lua_type<const void*>()));
				}
					break;
				case LUA_TTABLE:
				{
					_lua_type<_lua_table> *table = new _lua_type<_lua_table>();
					_field.insert(std::make_pair(key, table));
					
					//TRACELA("{\n");
					table->parser(L);
				//	TRACEA("}");
				}
					break;
				case LUA_TFUNCTION:
				{
					_field.insert(std::make_pair(key, new _lua_type<_lua_function>()));
				}
					break;
				case LUA_TUSERDATA:
				{
					lua_userdata<T>* udata = static_cast<lua_userdata<T>*>(lua_touserdata(L, -1));
					//TRACELA("%p", udata->_self);
					
					_field.insert(std::make_pair(key, new _lua_type<_lua_userdata>()));
				}
					break;
				case LUA_TTHREAD:
					break;
			}
			
			//TRACELA("\n");
			
			lua_pop(L, 1);
		};
	}
	
	void dump(lua_State* L, void* target)
	{
		//TRACEA("->> TABLE SIZE = %d\n", _field.size());
		
		for (hash_map<std::string, _object_info*>::iterator i = _field.begin(); i != _field.end(); i++)
		{
			//TRACEA("->> %s (%s): %p ", i->first.c_str(), ((_object_info*)(i->second))->name(), i->second);
			
			int type = ((_object_info*)(i->second))->id();
			switch (type)
			{
				case LUA_TBOOLEAN:
				{
					_lua_type<bool>* p = dynamic_cast<_lua_type<bool>*> (i->second);
					//TRACELA("= %d (%s)", p->get(L, target, i->first.c_str()), p->get(L, target, i->first.c_str()) ? "true" : "false");
				}
					break;
					
				case LUA_TNUMBER:
				{
					_lua_type<int>* p = dynamic_cast<_lua_type<int>*> (i->second);
					//TRACELA("= %d", p->get(L, target, i->first.c_str()));
				}
					break;
				case LUA_TSTRING:
				{
					_lua_type<const char*>* p = dynamic_cast<_lua_type<const char*>*> (i->second);
					//TRACELA("= '%s'", p->get(L, target, i->first.c_str()));
				}
					break;
				case LUA_TLIGHTUSERDATA:
				{
					_lua_type<const void*>* p = dynamic_cast<_lua_type<const void*>*> (i->second);
					//TRACELA("= %p", p->get(L, target, i->first.c_str()));
				}
					break;
				case LUA_TTABLE:
				{
					_lua_type<_lua_table>* p = dynamic_cast<_lua_type<_lua_table>*> (i->second);

					//TRACELA("{\n");
					p->dump(L, target);
					//TRACEA("}");
				}
					break;
				case LUA_TFUNCTION:
				{
					//TRACELA("\n");
					
					_lua_type<_lua_function>* p = dynamic_cast<_lua_type<_lua_function>*> (i->second);
					p->is_function(L, target, i->first.c_str());
					
					//(*p)(L, target);
				}
					break;
			}
			
			//if (type != LUA_TTABLE)
				//TRACELA("\n");
		}
	}
};


/**
 *
 */
template<>
int _type<bool>::type = LUA_TBOOLEAN;

template<>
const char* _type<bool>::name = "LUA_TBOOLEAN";


/**
 *
 */
template<>
int _type<int>::type = LUA_TNUMBER;

template<>
const char* _type<int>::name = "LUA_TNUMBER";



/**
 *
 */
template<>
int _type<const char*>::type = LUA_TSTRING;

template<>
const char* _type<const char*>::name = "LUA_TSTRING";

template<>
int _type<char*>::type = LUA_TSTRING;

template<>
const char* _type<char*>::name = "LUA_TSTRING";

/**
 *
 */
template<>
int _type<const void*>::type = LUA_TLIGHTUSERDATA;

template<>
const char* _type<const void*>::name = "LUA_TLIGHTUSERDATA";


template<>
int _type<void*>::type = LUA_TLIGHTUSERDATA;

template<>
const char* _type<void*>::name = "LUA_TLIGHTUSERDATA";

/**
 *
 */
template<>
int _type<_lua_userdata>::type = LUA_TUSERDATA;

template<>
const char* _type<_lua_userdata>::name = "LUA_TUSERDATA";


/**
 *
 */
template<>
int _type<_lua_table>::type = LUA_TTABLE;

template<>
const char* _type<_lua_table>::name = "LUA_TTABLE";


/**
 *
 */
template<>
int _type<_lua_function>::type = LUA_TFUNCTION;

template<>
const char* _type<_lua_function>::name = "LUA_TFUNCTION";



/**
 * Entity
 */
class Entity {
	lua_class* _target;
	
	hash_map<std::string, delegate_impl<int>*> _methods;
	hash_map<std::string, property_ptr*> _property;

	hash_map<const char*, _object_info*, std::hash<const char*>, eqstr> _vtable;
	
	_lua_type<_lua_table> _table;
	
public:
	Entity()
	: _fps(0)
	, _name(NULL)
	{
	}
	Entity(lua_State* L)
	: _fps(0)
	, _name(NULL)
	{
		TRACEC();

		object o;
		printf("->> o.name = %s\n", o.name());
	}
	~Entity()
	{
		TRACEC();
	}

	
	int init()
	{
		//TRACEF();
		
		(*_methods["init"])();
		
		return 0;
	}
	
	int drawFrame()
	{
		TRACEF();

		(*_methods["drawFrame"])();
	}
		 
	int init(lua_State* L)
	{
		//TRACEF();
		
		(*_methods["init"])();
		
		return 0;
	}
	
	int drawFrame(lua_State* L)
	{
		/*TRACEF();
		
		int a = get<int>("a");
		printf("->> a = %d\n", a);
		
		printf("->> a ++\n");
		a ++;
		
		set<int>("a", a);
		
		printf("->> a = %d\n", a);
		
		int b = get<int>("b");
		printf("->> b = %d\n", b);
		
		int c = get<int>("c");
		printf("->> c = %d\n", c);
		*/
		(*_methods["drawFrame"])();

		return 0;
	}

	void _parserTable(lua_State* L, const char* pkey)
	{
		lua_pushnil(L);
		
		while (lua_next(L, -2))
		{
			char ikey[PATH_MAX];
			
			int nkey = 0;
			const char* key = NULL;

			if (lua_type(L, -2) == LUA_TSTRING)
			{
				key = lua_to<const char*>(L, -2);

				TRACEA("->> %s", key);
			}
			else
			{
				nkey = lua_to<int>(L, -2);
				sprintf(ikey, "%d", nkey);
				key = ikey;

				TRACEA("->> %d", nkey);
			}

			
			int type = lua_type(L, -1);

			TRACELA(" (%s): ", lua_typename(type));
			switch (type)
			{
				case LUA_TNIL:
					break;
				case LUA_TBOOLEAN:
					//TRACELA("%s", lua_toboolean(L, -1) ? "TRUE" : "FALSE");
				{
					_vtable.insert(std::make_pair(key, new _lua_type<bool>()));
				}
					break;
				case LUA_TNUMBER:
					//TRACELA("%d", lua_tointeger(L, -1));
				{
					if (key)
					_property.insert(std::make_pair(key, new LUA_CLASS_PROPERTY(L, int, NULL, key)));

					_vtable.insert(std::make_pair(key, new _lua_type<int>()));

				}
					break;
				case LUA_TSTRING:
					TRACELA("%s", lua_tostring(L, -1));
				{
					_vtable.insert(std::make_pair(key, new _lua_type<const char*>()));
					
					if (!strcmp(key, "name"))
					{
						_name = lua_to<const char*>(L, -1);
					}
				}
					break;
				case LUA_TLIGHTUSERDATA:
					TRACELA("%p", lua_touserdata(L, -1));
				{
					_vtable.insert(std::make_pair(key, new _lua_type<const void*>()));
					
					//if (pkey && !strcmp(pkey, "this") && !strcmp(key, "this"))
					if (pkey == 0 && !strcmp(key, "this"))
					{
						_target = lua_to<lua_class*>(L, -1);
					}
				}
					break;
				case LUA_TTABLE:
				{
					_vtable.insert(std::make_pair(key, new _lua_type<_lua_table>()));
					
					TRACELA("{\n");
					_parserTable(L, key);
					TRACEA("}");
				}
					break;
				case LUA_TFUNCTION:
				{
					_vtable.insert(std::make_pair(key, new _lua_type<_lua_function>()));
					
					_methods.insert(std::make_pair(key, new LUA_CLASS_DELEGATE(L, int, NULL, key)));
				}
					break;
				case LUA_TUSERDATA:
				{
					//lua_userdata<T>* udata = static_cast<lua_userdata<T>*>(lua_touserdata(L, -1));
					//TRACELA("%p", udata->_self);
					
					_vtable.insert(std::make_pair(key, new _lua_type<_lua_userdata>()));
				}
					break;
				case LUA_TTHREAD:
					break;
					
			}
			
			TRACELA("\n");
			
			lua_pop(L, 1);
		};
	}

	void _parserArg(lua_State* L)
	{
		/**
		 *
		 */
		while (lua_gettop(L))
		{
			int top = lua_gettop(L);
			
			int type = lua_type(L, top);
			//TRACEA("->> %s: ", lua_typename(type));
			switch (type)
			{
				case LUA_TNIL:
					break;
				case LUA_TBOOLEAN:
					//TRACELA("%s", lua_toboolean(L, top) ? "TRUE" : "FALSE");
					break;
				case LUA_TLIGHTUSERDATA:
					//TRACELA("%p", lua_touserdata(L, top));
					break;
				case LUA_TNUMBER:
					//TRACELA("%d", lua_tointeger(L, top));
					break;
				case LUA_TSTRING:
					TRACELA("%s", lua_tostring(L, top));
				{
					if (_name == NULL)
					{
						_name = lua_to<const char*>(L, top);
					}
				}
					break;
				case LUA_TTABLE:
				{
					TRACELA("{\n");
					_parserTable(L, NULL);
					TRACEA("}");

					//TRACELA("{\n");
					//_table.parser(L);
					//TRACEA("}");
				}
					break;
				case LUA_TFUNCTION:
					break;
				case LUA_TUSERDATA:
				{
					//lua_userdata<T>* udata = static_cast<lua_userdata<T>*>(lua_touserdata(L, top));
					//TRACELA("%p", udata->_self);
				}
					break;
				case LUA_TTHREAD:
					break;
					
			}
				TRACELA("\n");
			
			lua_pop(L, 1);
		}
	}

	int loadScript(lua_State* L)
	{
		//lua_checknarg(L);
		
		if (lua_gettop(L) != 1)
		{
			lua_push(L, FALSE);
			return 1;
		}
		
		/**
		 *
		 */
		const char* path = lua_to<const char*>(L, 1);
		
		lua_push(L, loadScript(L, path));
		
		return 1;
	}
	
	int loadScript(lua_State* L, const char* filename)
	{
		TRACEF();
				
		char fullpath[PATH_MAX];
		makeResourcePath(fullpath, filename);
		
		if (lua_loadfile(L, fullpath) == FALSE)
			return FALSE;
		
		if (lua_pcall(L, 0) == FALSE)
			return FALSE;


		//_name = "baseActor";
		strcpy(fullpath, filename);
		char* p = strchr(fullpath, '.');
		*p = 0;
		
		//_name = fullpath;

/*
		char script[PATH_MAX];
		sprintf(script, "return %s(true)", _name);
		
		luaL_loadbuffer(L, script, strlen(script), "");
		
		if (lua_pcall(L, 0) == FALSE)
			return FALSE;
*/

		lua_setmethod(L, "main");
		lua_pcall(L, 0);
		
		
		/**
		 * return
		 */
		TRACELA("->> DUMP ARG\n");
		_parserArg(L);
		//_parserTable(L, NULL);
		//_table.parser(L);
		

		/**
		 * metatable
		 */
		TRACELA("->> DUMP METATABLE\n");

		
		lua_pushstring(L, _name);
		lua_gettable(L, LUA_GLOBALSINDEX);
		
		_parserTable(L, NULL);
		
		_table.parser(L);
		
		
		/**
		 * method
		 */
		//lua_pushstring(L, _name);
		//lua_gettable(L, LUA_GLOBALSINDEX);

		//lua_setmetatable(L, -2);

	
/*
		lua_pushlightuserdata(L, _target);
		lua_gettable(L, LUA_REGISTRYINDEX);

		const char* _method = "init";
		lua_pushstring(L, _method);
		lua_gettable(L, -2);
		
		if (lua_isfunction(L, -1))
		{
			//TODO: ???
			lua_pushvalue(L, -2);

			int narg = 1;
			
			//inline int pcall(int narg)
			{
				int base = lua_gettop(L) - narg;					// function index
				lua_pushcfunction(L, lua_traceback);			// push traceback function
				lua_insert(L, base);											// put it under chunk and args
				
				int status = lua_pcall(L, narg, 0, base);
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
		};
*/	
		
		
		/**
		 * rebinding method hash_map
		 */
		for (hash_map<std::string, delegate_impl<int>*>::iterator i = _methods.begin(); i != _methods.end(); i++)
		{
			//std::cout << "key(string): " << i->first << ", value(int): " << i->second << std::endl;

			lua_class_delegate<int, lua_class>* ptr = dynamic_cast<lua_class_delegate<int, lua_class>*> (i->second);
			if (ptr)
				ptr->setTarget(_target);
		}

		/**
		 * re binding property
		 */
		for (hash_map<std::string, property_ptr*>::iterator i = _property.begin(); i != _property.end(); i++)
		{
			//std::cout << "key(string): " << i->first << ", value(int): " << i->second << std::endl;

			lua_class_property_member<int, lua_class>* ptr = dynamic_cast<lua_class_property_member<int, lua_class>*> (i->second);
			if (ptr)
				ptr->setTarget(_target);
		}
		

		
		/**
		 * _vtable
		 */
		/*
		TRACEA("->> _VTABLE\n");
		
		for (hash_map<const char*, _object_info*>::iterator i = _vtable.begin(); i != _vtable.end(); i++)
		{
			TRACEA("->> %s (%s): %p ", i->first, ((_object_info*)(i->second))->name(), i->second);
			
			int type = ((_object_info*)(i->second))->id();
			switch (type)
			{
				case LUA_TBOOLEAN:
				{
					_lua_type<bool>* p = dynamic_cast<_lua_type<bool>*> (i->second);
					TRACELA("= %d (%s)", p->get(L, _target, i->first), p->get(L, _target, i->first) ? "true" : "false");
				}
					break;
					
				case LUA_TNUMBER:
				{
					_lua_type<int>* p = dynamic_cast<_lua_type<int>*> (i->second);
					TRACELA("= %d", p->get(L, _target, i->first));
				}
					break;
				case LUA_TSTRING:
				{
					_lua_type<const char*>* p = dynamic_cast<_lua_type<const char*>*> (i->second);
					TRACELA("= %s", p->get(L, _target, i->first));
				}
				case LUA_TLIGHTUSERDATA:
				{
					_lua_type<const void*>* p = dynamic_cast<_lua_type<const void*>*> (i->second);
					TRACELA("= %p", p->get(L, _target, i->first));
				}
					break;
				case LUA_TFUNCTION:
				{
					TRACELA("\n");
					
					_lua_type<_lua_function>* p = dynamic_cast<_lua_type<_lua_function>*> (i->second);
					p->is_function(L, _target, i->first);
					
					(*p)(L, _target);
				}
					break;
			}
			
			TRACELA("\n");
		}*/

		TRACELA("->> DUMP TABLE\n");
		//_table.dump(L, _target);
		
		TRACEA("->> name = %s\n", _name);
		
		return 1;
	}
	
	template <typename T>
	T get(const char* name)
	{
		property_impl<T>* property = dynamic_cast<property_impl<T>*> (_property[name]);
		return property->get();
	}
	
	template <typename T>
	void set(const char* name, T v)
	{
		property_impl<T>* property = dynamic_cast<property_impl<T>*> (_property[name]);
		property->set(v);
	}

	property_ptr* get(const char* name)
	{
		return _property[name];
	}
	
	const char* _name;
	int _fps;
};


/**
 * View
 */
class View {
public:
	View(lua_State* L)
	{
		TRACEC();
	}
	~View()
	{
		TRACEC();
	}
	int drawFrame(lua_State* L)
	{
		TRACEF();
		
		//int fps = _fps;
		//fps ++;
		
		lua_metatable<View>::pushuserdata(L, this);
		
		lua_getfield(L, -1, "fps");
		int fps = lua_to<int>(L, -1);
		lua_pop(L, 1);
		
		fps ++;
		
		lua_push(L, fps);
		
		lua_setfield(L, -2, "fps");
		lua_pop(L, 1);
		
		return 0;
	}
	
	void dumpTable(lua_State* L)
	{
		if (lua_istable(L, -1) == 0)
			return;
		
		lua_pushnil(L);
		
		while (lua_next(L, -2))
		{
			/*
			// `key' is at index -2 and `value' at index -1
			if (lua_type(L, -2) == LUA_TSTRING)
			{
				const char* s = lua_tostring(L, -2);
				printf("->> key = %s\n", s);
			}
			else
			{
				int n = (int)lua_tonumber(L, -2); // key index.
				printf("->> key = %d\n", n);
			}*/
			
			// key
			TRACEA("->> %s: %s = ", lua_typename(lua_type(L, -1)), lua_typetostring(L, -2));
			TRACELA("%s\n", lua_typetostring(L, -1));
			
			lua_pop(L, 1);
		};
	}
	
	int addNode(lua_State* L)
	{
		TRACEF();
		
		//lua_checknarg(L);
		
		if (lua_gettop(L) != 1)
		{
			lua_push(L, FALSE);
			return 1;
		}
		
	
		delegate_impl<int>* _delegate;
		
		lua_class* target = lua_to<lua_class*>(L, 1);
		const char* method = "drawFrame";
		
		_delegate = new LUA_CLASS_DELEGATE(L, int, target, method);
		(*_delegate)();

		
		/**
		 *
		 */
		//printf("->> dump class 'View'\n");

		//lua_metatable<View>::setmetatable(L);

		//dumpTable(L);

		
		/**
		 *
		 */
		printf("->> dump class 'Node'\n");
		
		lua_pushlightuserdata(L, target);
		lua_gettable(L, LUA_REGISTRYINDEX);
	
//		dumpTable(L);

		lua_getfield(L, -1, "fps");
		int fps = lua_to<int>(L, -1);
		lua_pop(L, 1);
		
		fps ++;
		
		lua_push(L, fps);
		
		lua_setfield(L, -2, "fps");
		lua_pop(L, 1);
	
		
		/**
		 *
		 */
		lua_push(L, TRUE);
		
		return 1;
	}
	
	int _fps;
};


/**
 * Application
 */
class Application {
public:
	Application(lua_State* L)
	: _mainView(NULL)
	{
		TRACEC();
	
		_fps = 100;
		_width = 10;
		
		_pi = new property_member<int, Application>(this, &Application::_fps);

		_pi->set(200);
		int i = _pi->get();
		
		printf("_mi = %d\n", i);
	}
	int dispatchEvent(lua_State* L)
	{
		//TRACEF();
		
		return 0;
	}
	
	View* _mainView;
	
	int _fps;
	property_impl<int> *_pi;
	
	int _width;
	
	int getWidth() { return _width; }
	void setWidth(int width) { _width = width; }
	
	
	Application()
	: _mainView(NULL)
	{
		_self = this;
		
		_fps = 1000;
		_width = 200;
		
	}
	
	static void _dealloc()
	{
		TRACEF();
		
		SAFE_DELETE(_self);
	}
	
	static Application* sharedApplication()
	{
		if (_self == NULL)
		{
			_self = new Application();
			
			///
			atexit(_dealloc);
		}
		
		return _self;
	}
	
	static int sharedApplication(lua_State* L)
	{
		sharedApplication();
		
		lua_metatable<Application>::pushuserdata(L, _self);
		
		return 1;
	}
	
	static Application* _self;
};

/**
 * shared
 */
Application* Application::_self = 0;


#include "lua_vm.h"

/**
 * View
 */
class vec3 {
public:
	vec3(lua_State* L)
	{
		TRACEC();
	}
	float _x, _y, _z;
};

int initialize_bind()
{
	__init();
	
	
	lua_vm::sharedVM()->setpath(resourcePath());

	
	lua_State* _L = lua_vm::sharedVM()->get();
	

	/**
	 * vec3
	 */
	lua_metatable<vec3>::newtable(_L, "vec3");
	//lua_metatable<Entity>::bind_method(_L, "loadScript", &Entity::loadScript);
	lua_metatable<vec3>::bind_member(_L, "x", &vec3::_x);
	lua_metatable<vec3>::bind_member(_L, "y", &vec3::_y);
	lua_metatable<vec3>::bind_member(_L, "z", &vec3::_z);
	
	/**
	 *
	 */
	lua_metatable<Entity>::newtable(_L, "Entity");
	lua_metatable<Entity>::bind_method(_L, "init", &Entity::init);
	lua_metatable<Entity>::bind_method(_L, "drawFrame", &Entity::drawFrame);
	lua_metatable<Entity>::bind_method(_L, "loadScript", &Entity::loadScript);
	lua_metatable<Entity>::bind_member(_L, "fps", &Entity::_fps);

	
	/**
	 *
	 */
	lua_metatable<View>::newtable(_L, "View");
	lua_metatable<View>::bind_method(_L, "drawFrame", &View::drawFrame);
	lua_metatable<View>::bind_method(_L, "addNode", &View::addNode);
	lua_metatable<View>::bind_member(_L, "fps", &View::_fps);

	
	/**
	 *
	 */
	lua_metatable<Application>::newtable(_L, "Application");
	lua_metatable<Application>::bind_method(_L, "dispatchEvent", &Application::dispatchEvent);
	
	lua_metatable<Application>::bind_member(_L, "fps", &Application::_fps);
	lua_metatable<Application>::bind_member(_L, "mainView", &Application::_mainView);

	lua_metatable<Application>::bind_property(_L, "width", &Application::getWidth, &Application::setWidth);


	lua_metatable<Application>::bind_method(_L, "sharedApplication", &Application::sharedApplication);
	
	
	/**
	 *
	 */
	lua_register(_L, "sharedApplication", Application::sharedApplication);
	
	
	/**
	 *
	 */
	lua_register(_L, "bind_class", lua_class::bind);
	lua_register(_L, "bind_shared_class", lua_shared_class::bind);
	
	
	
	char bootstrap[PATH_MAX];
	makeResourcePath(bootstrap, "bootstrap.lua");

	lua_vm::sharedVM()->bootstrap(bootstrap);

	
	Entity e;
	e.loadScript(_L, "baseActor.lua");
	e.init();
	e.drawFrame();
	
	return 0;
}
										 
										 
