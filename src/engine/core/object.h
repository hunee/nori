/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "node.h"

namespace GL {

/**
 * @brief Construct a new object
 * 
 */
class object
: public std::map<const std::string, std::shared_ptr<component_>> {
public:
//std::shared_ptr<ICLASS(object)> get_shared_ptr() { return shared_from_this(); }

public:
	GL::transform transform_;
	const GL::transform& transform() { return transform_; }

public:
	//object() { __method__ }
	virtual ~object() {}

public:
	virtual void _began() {}
	virtual void _end() {}

public:	
	virtual void _tick(double dt)
	{
		//owner
		GL::point pos;
		auto owner = ptr()->owner(); //component, parent
		if (owner)
		{
			auto o = std::dynamic_pointer_cast<object>(owner);
			if (o) 
			{
				auto t = o->transform();

				pos.x = t.x2;
				pos.y = t.y2;
			}
		}

		transform_.x2 = transform_.x + pos.x;
		transform_.y2 = transform_.y + pos.y;

	////
		for (auto&& kv : *this)
			kv.second->_tick(dt);
	}
	
	virtual void _draw() {}

public:	
	void dump()
	{
		//__method__

		for (auto&& kv : *this)
      COUT << "ext: \"" << kv.first << "\", type: " << __typeid_name(*kv.second) << ", use_count: " << kv.second.use_count() << ENDL;
	}

public:
	template <typename T = component_>
	void add(const std::string& name, std::shared_ptr<T> component)
//	void add(const std::string& name, std::shared_ptr<component_> component)	
	{
		//__method__

		try {
			component->owner_ = ptr()->get_shared_ptr();

			auto ret = insert({name, nullptr});
			if (ret.second == true)
				ret.first->second = component;
		}
		catch (std::exception& e) {
			COUT << "Exception: " << e.what() << ENDL;
		}		
	}

	template <typename T>
	std::shared_ptr<T> get(const std::string& name)
	{
		auto it = find(name);
		if (it != end())
			return std::dynamic_pointer_cast<T>(it->second);

		return nullptr;
	}

public:
	template <typename T=node_>
	T * ptr()
	{
		//__method__

		auto p = dynamic_cast <T*>(this);
  	if (p == nullptr)
  	{
			//throw ...
			char e[255];
			sprintf(e, "%sthis->owner(): Reference to object under construction is not valid when calling another constructor.%s", KRED, RST);

			throw std::runtime_error(e);
		}

		return p;
	}

	template <typename T=node_>
	std::shared_ptr<T> owner()
	{
		__method__

		auto p = dynamic_cast<T*>(this);
		auto owner = p->owner();
		if (owner)
			return std::dynamic_pointer_cast<T>(owner);

		return nullptr;	
	}

public:
	virtual bool contains(int x, int y) { return false; }

};


/**
 * @brief 
 * 
 */
class owner_ptr {
public:
	virtual ~owner_ptr() {}

public:	
	template <typename T>
	std::shared_ptr<T> owner()
	{
		//__method__
		
		auto p = dynamic_cast<component_*>(this);
		if (p)
		{
			auto owner = p->owner();
			if (owner) 
				return std::dynamic_pointer_cast<T>(owner);
		}

		return nullptr;	
	}	

public:
	virtual void _tick(double dt)	{}
};


};//GL
