/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "component.h"

namespace GL {


/**
 * @brief Construct a new node object
 * 
 */
class node_ 
: public component_
, public std::map<const std::string, std::shared_ptr<node_>> {
public:	
	///std::shared_ptr<node_> get_shared_ptr() { return shared_from_this(); }

public:
	node_() {}
	node_(const std::string& name) : component_(name) {}
	node_(const std::string& name, const std::shared_ptr<component_>& owner) : component_(name, owner) {}

public:
	virtual ~node_() {}

public:
	virtual std::shared_ptr<node_> add()
	{
		auto p = std::dynamic_pointer_cast<node_>(owner());
		auto n = std::dynamic_pointer_cast<node_>(get_shared_ptr());
	
		auto ret = p->insert({name_, nullptr});
		if (ret.second == true)
		{
			ret.first->second = n;
		}

		return n;
	}

public:
	template <typename T=node_>
	void add(const std::string& name, std::shared_ptr<T> node)
	{
		//__method__

		auto ret = insert({name, nullptr});
		if (ret.second == true)
		{
			node->owner_ = shared_from_this();
			ret.first->second = node;
		}
	}

	template <typename T=node_>
	std::shared_ptr<T> get(const std::string& name)
	{
		auto it = find(name);
		if (it != end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}

		return nullptr;
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
		__method__

		COUT << "- name: \"" << name_ << "\", type: " << __typeid_name(*this) << ", use_count: " << shared_from_this().use_count() << ENDL;

		auto parent = owner_.lock();
		if (parent)
			COUT << "+ parent name: \"" << parent->name_ << "\", type: " << __typeid_name(*parent) << ", use_count: " << parent.use_count() << ENDL;

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
class node : public node_, public T {

public:
	~node()
	{
//		__FUNC_YEL__

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
	node(const std::string& name) : node_(name) {}
	node(const std::string& name, const std::shared_ptr<component_>& owner) : node_(name, owner) {}

public:
	std::shared_ptr<node_> add() override
	{
		return node_::add();
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

		node_::_tick(dt);
	}
	void _draw() override
	{
		T::_draw();

		node_::_draw();
	}

///using ttt::operator=;
};

//std::unique_ptr<GL::node_> root_;
//root_ = std::make_unique<GL::node<GL::dummy_node> >("dummy");
//root_->insert("dummy", std::make_unique<GL::node<GL::dummy_node2> >("dummy"));
class dummy {
public:
	virtual ~dummy() {}

public:
	void _began() {}
	void _end() {}

public:
	void _tick(double dt) {}
	void _draw() {}
};

using dummy_node = node<dummy>;

};//GL
