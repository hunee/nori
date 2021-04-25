/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __HANDLER_H__
#define __HANDLER_H__


#include "function.h"

/**
 *
 */
class _handler {
protected:
	void* _function_ptr;
	
public:
	_handler()
	{
	}
	
	template <typename V, typename T, typename M>
	_handler(T* target, M method)
	{
		_function_ptr = new function<V>(target, method);
	}
	virtual ~_handler()
	{
		if (_function_ptr)
		{
			function<void>* f = static_cast<function<void>*> (_function_ptr);
			delete f;
			
			_function_ptr = nullptr;
		}
	}
	
	
	/**
	 *
	 */
	template <typename T>
	void operator () (T sender)
	{
		function<void>* f = static_cast<function<void>*> (_function_ptr);
		(*f)(sender);
	}
	
	template <typename T>
	void operator () (T sender) const
	{
		function<void>* f = static_cast<function<void>*> (_function_ptr);
		(*f)(sender);
	}
	
	/**
	 *
	 */
	template <typename V, typename T>
	V r(T sender)
	{
		function<V>* f = static_cast<function<V>*> (_function_ptr);
		return f->r(sender);
	}
	template <typename V, typename T>
	V r(T sender) const
	{
		function<V>* f = static_cast<function<V>*> (_function_ptr);
		return f->r(sender);
	}
};


/**
 *
 */
template <typename V>
class handler : public _handler {
public:
	handler()
	{
	}
	
	template <typename T, typename M>
	handler(T* target, M method)
	{
		_function_ptr = new function<V>(target, method);
	}
};


/**
 * ...
 */
#endif //__HANDLER_H__
