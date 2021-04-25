/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "state.h"
#include "uniform.h"

namespace GL {

/**
 * @brief 
 * 
 */
class program 
: public std::map<const std::string, std::shared_ptr<uniform>> {
public:
	program() //noexcept
	{
		//CLOGF();

		//throw std::runtime_error("Exception from 3!\n");
	}

	virtual ~program()
	{
		//CLOGF();		
	}

	std::map<const std::string, std::shared_ptr<state>> states_;

public:
	virtual void use() {}

	virtual void bind()
	{
		//CLOGF();

//		for (auto&& kv : *this)
//      kv.second->bind();

		for (auto&& kv : states_)
      kv.second->bind();
	}

	template <typename V>
	void set(const std::string& name, V v)
	{
		auto it = find(name);
		if (it != end())
		{
			auto p = std::dynamic_pointer_cast<GL::uniform_<V>>(it->second);
			p->set(v);			
			p->bind();
		}
	}

	void dump()
	{
		CLOGF();

		for (auto&& kv : *this)
		{
      COUT << "ext: \"" << kv.first << "\", type: " << typeid_name(*kv.second) << ", use_count: " << kv.second.use_count() << ENDL;
		}
	}
};

}; //GL
