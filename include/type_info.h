/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include <cxxabi.h>
#include <typeinfo>


/**
 * type
 */
template<typename T>
struct _type {
	static size_t _hash_code;
	static const char* _name;
};

template<typename T>
size_t _type<T>::_hash_code = typeid(T).hash_code();

template<typename T>
const char* _type<T>::_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, 0);


/**
 * _object_info
 */
struct _object_info {
///public:
	///virtual ~_object_info() {}
	
	virtual size_t hash_code() const =0;
	virtual const char* name() const =0;
};


/**
 * type_info
 */
template <typename T>
struct _type_info : public _type<T>, public _object_info {
	size_t hash_code() const override 
	{
		return _type<T>::_hash_code;
	}
	
	const char* name() const override 
	{
		return _type<T>::_name;
	}
};

#define is_typeid_equal(T1, T2) typeid(T1) == typeid(T2)

///#define is_type_equal(T) std::strcmp(_type<T>::_name, this->name()) == 0
///#define is_type_equal2(T1, T2) std::strcmp(_type<T1>::_name, _type<T2>::_name) == 0

#define is_type_equal(T) _type<T>::_hash_code == this->_hash_code
#define is_type_equal2(T1, T2) _type<T1>::_hash_code == _type<T2>::_hash_code

/**
 * ...
 */
struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return std::strcmp(s1, s2) == 0;
  }
};

class object_type : public _type_info<object_type> {
//	hash_map<const char*, _object_info*, std::hash<const char*>, eqstr> _vtable;
	
public:
	object_type()
	{
	}
};


/**
 * @brief 
 * 
 * @tparam T 
 * @param object 
 * @return const char* 
 */
template <typename T>
const char* typeid_name(T& object)
{
  return abi::__cxa_demangle(typeid(object).name(), 0, 0, 0);
}


///
#define ICLASS(c) interface_class_##c
#define AC(name) abstract_class_##name
