/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "component.h"

namespace GL {


/**
 * @brief Construct a new ICLASS object
 * 
 */
class ICLASS(node) 
: public ICLASS(component)
, public std::map<const std::string, std::shared_ptr<ICLASS(node)>> {
public:	
	///std::shared_ptr<ICLASS(node)> get_shared_ptr() { return shared_from_this(); }

public:
	ICLASS(node)() {}
	ICLASS(node)(const std::string& name) : ICLASS(component)(name) {}
	ICLASS(node)(const std::string& name, const std::shared_ptr<ICLASS(component)>& owner) : ICLASS(component)(name, owner)	{}

public:
	virtual ~ICLASS(node)() { /*YLOGF();*/ }

public:
	template <typename T=ICLASS(node)>
	void add(const std::string& name, std::shared_ptr<T> node)
	//void add(const std::string& name, std::shared_ptr<ICLASS(node)> node)
	{
		//CLOGF();

		auto ret = insert({name, nullptr});
		if (ret.second == true)
		{
			node->owner_ = shared_from_this();
			ret.first->second = node;
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
	virtual std::shared_ptr<ICLASS(node)> add()
	{
		auto p = std::dynamic_pointer_cast<ICLASS(node)>(owner());
		auto n = std::dynamic_pointer_cast<ICLASS(node)>(get_shared_ptr());
	
		auto ret = p->insert({name_, nullptr});
		if (ret.second == true)
			ret.first->second = n;

		return n;
	}

public:
	void _tick(double dt) override
	{
		for (auto&& kv : *this)
      kv.second->_tick(dt);
	}

public:	
	virtual void _draw()
	{
		for (auto&& kv : *this)
      kv.second->_draw();
	}

public:
	virtual void dump()
	{
		///CLOGF();

		COUT << "* name: \"" << name_ << "\", type: " << typeid_name(*this) << ENDL;

		auto parent = owner_.lock();
		if (parent)
			COUT << "- parent name: \"" << parent->name_ << "\", type: " << typeid_name(*parent) << ", use_count: " << parent.use_count() << ENDL;

		/////
		for (auto&& kv : *this)
			kv.second->dump();
	}
};


/**
 * @brief 
 * 
 */
template <typename T>
class node : public ICLASS(node), public T {

public:
	~node()
	{
//		YLOGF();

/*	COUT << "name: " << name_ << ENDL;
	
	auto owner = owner_.lock();
	if (owner)
	{
		COUT << "pname: " << owner->name_ << ", use_count: " << owner.use_count() << ENDL;
	}
*/	
		//if (parent_) {
			//parent_->erase(name_); 

			/*auto it = parent_->find(name_);
			if (it != parent_->end())
				//COUT << "p: " << it->second->name_ << ENDL;
				it->second = nullptr;*/


		/*
		auto it = parent_->begin();
		for (;it != parent_->end(); )
		{
  		if (it->first == name_)
			{
    		parent_->erase(it++);
  		}else{
    		++it;
  		}
		}*/

		//}

	//	parent_ = nullptr;
	}

public:	
	node() {}
	node(const std::string& name) : ICLASS(node)(name) {}
	node(const std::string& name, const std::shared_ptr<ICLASS(component)>& owner) : ICLASS(node)(name, owner) {}

public:
	std::shared_ptr<ICLASS(node)> add() override
	{
		return ICLASS(node)::add();
	}

public:
	void _began() override
	{
		T::_began();
	}
	void _end() override
	{
		T::_end();
	}

public:
	void _tick(double dt) override
	{
		T::_tick(dt);

		ICLASS(node)::_tick(dt);
	}
	void _draw() override
	{
		T::_draw();

		ICLASS(node)::_draw();
	}

///using ttt::operator=;
};

//std::unique_ptr<GL::ICLASS(node)> root_;
//root_ = std::make_unique<GL::node<GL::dummy_node> >("dummy");
//root_->insert("dummy", std::make_unique<GL::node<GL::dummy_node2> >("dummy"));
class dummy {
public:
	virtual ~dummy() { /*YLOGF();*/ }

public:
	void _began() {}
	void _end() {}

public:
	void _tick(double dt) {}
	void _draw() {}
};

using dummy_node = node<dummy>;

};//GL
