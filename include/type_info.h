/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include <cxxabi.h>
#include <typeinfo>


/**
 * type
 */
template<typename T>
struct __type {
	static size_t hash_code_;
	static const char* name_;
};

template<typename T>
size_t __type<T>::hash_code_ = typeid(T).hash_code();

template<typename T>
const char* __type<T>::name_ = abi::__cxa_demangle(typeid(T).name(), 0, 0, 0);


/**
 * _object_info
 */
struct __object_info {
///public:
	///virtual ~__object_info() {}
	
	virtual size_t hash_code() const =0;
	virtual const char* name() const =0;
};


/**
 * type_info
 */
template <typename T>
struct __type_info : public __type<T>, public __object_info {
	size_t hash_code() const override 
	{
		return __type<T>::hash_code_;
	}
	
	const char* name() const override 
	{
		return __type<T>::name_;
	}
};

#define is_typeid_equal(T1, T2) typeid(T1) == typeid(T2)

#define is_type_equal(T) __type<T>::hash_code_ == this->hash_code_
#define is_type_equal2(T1, T2) __type<T1>::hash_code_ == __type<T2>::hash_code_


class object_type : public __type_info<object_type> {
public:
	object_type() {}
};


/**
 * @brief 
 * 
 * @tparam T 
 * @param object 
 * @return const char* 
 */
template <typename T>
const char* __typeid_name(T& t)
{
  return abi::__cxa_demangle(typeid(t).name(), 0, 0, 0);
}

