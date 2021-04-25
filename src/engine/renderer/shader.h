/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

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
	virtual ~shader() { /*CLOGF();*/ }

public:
	void bind()
	{
		//CLOGF();
/*
		for (auto&& p : *this)
		{
      COUT << "p: \"" << p.first << "\", type: " << typeid_name(*p.second) << ENDL;
		}*/
	}

	void dump()
	{
		//CLOGF();

		for (auto&& p : *this)
		{
      COUT << "program name: \"" << p.first << "\", type: " << typeid_name(*p.second) << ENDL;
		}
	}

};//shader

};//GL