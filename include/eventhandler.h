/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "function.h"

struct event;

class eventhandler {
public:
	eventhandler(int type, function<void>* f)
	: _type(type)
	, _f(f)
	{
	}
	~eventhandler()
	{
		if(_f)
		{
			delete _f;
			_f = nullptr;
		}
	}

public:
	/**
	 *
	 */
	template <typename T>
	void operator() (T* e)
	{
		(*_f) (e);
	}

	template <typename T>
	void operator() (T* e) const
	{
		(*_f) (e);
	}

	
	/**
	 *
	 */
	template <typename T, typename V>
	V r(T* e)
	{
		return (*_f).r<V> (e);
	}

	template <typename T, typename V>
	V r(T* e) const
	{
		return (*_f).r<V> (e);
	}
	
public:
	int _type;
	
private:
	function<void>* _f;
};

#endif //__EVENT_HANDLER_H__
