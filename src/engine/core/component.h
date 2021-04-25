/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL {


/**
 * @brief 
 * 
 */
class ICLASS(component)
: public std::enable_shared_from_this<ICLASS(component)> {
public:
	std::shared_ptr<ICLASS(component)> get_shared_ptr() { return shared_from_this(); }

public:
	std::weak_ptr<ICLASS(component)> owner_;
	const std::shared_ptr<ICLASS(component)> owner() const 
	{
		return owner_.lock(); 
	}
	void set_owner(const std::shared_ptr<ICLASS(component)>& owner)
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
	ICLASS(component)() {}
	ICLASS(component)(const std::string& name) : name_(name) {}
	ICLASS(component)(const std::string& name, const std::shared_ptr<ICLASS(component)>& owner) : name_(name), owner_(owner)	{}

	virtual ~ICLASS(component)() {}

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
class component : public ICLASS(component), public T {
public:
	component(const std::string& name)
	: ICLASS(component)(name) {}

public:
	void _tick(double dt) override
	{
		T::_tick(dt);
	}
};

};//GL
