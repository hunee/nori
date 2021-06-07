/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL {


/**
 * @brief 
 * 
 */
class component_
: public std::enable_shared_from_this<component_> {
public:
	std::shared_ptr<component_> get_shared_ptr() { return shared_from_this(); }

public:
	std::weak_ptr<component_> owner_;
	const std::shared_ptr<component_> owner() const 
	{
		return owner_.lock(); 
	}
	void set_owner(const std::shared_ptr<component_>& owner)
	{
		owner_ = owner;
	}

public:
	std::string name_;
	const std::string& name() const 
	{
		return name_; 
	}
	void set_name(const std::string& name) 
	{
		name_ = name; 
	}

public:
	component_() {}
	component_(const std::string& name) : name_(name) {}
	component_(const std::string& name, const std::shared_ptr<component_>& owner) : name_(name), owner_(owner)	{}

	virtual ~component_() {}

public:
	virtual void _began() {}
	virtual void _end() {}

public:
	virtual void _tick(double dt) {}	
};


/**
 * @brief 
 * 
 */
template <typename T>
class component : public component_, public T {
public:
	component(const std::string& name)
	: component_(name) {}

public:
	void _tick(double dt) override
	{
		T::_tick(dt);
	}
};

};//GL
