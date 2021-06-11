/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "program.h"

namespace GL {

/**
 * @brief 
 * 
 */
class shader : 
	public std::map<const std::string, std::shared_ptr<program>> {	
public:
	virtual ~shader() { /*__method__*/ }

public:
	void bind()
	{
		//__method__
/*
		for (auto&& p : *this)
		{
      COUT << "p: \"" << p.first << "\", type: " << __typeid_name(*p.second) << ENDL;
		}*/
	}

	void dump()
	{
		//__method__
#if 0
		for (auto&& p : *this)
		{
      COUT << "program name: \"" << p.first << "\", type: " << __typeid_name(*p.second) << ENDL;
		}
#endif		
	}

};//shader

};//GL