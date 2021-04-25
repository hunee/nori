/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL {

class uniform {
public:
	uniform(const std::string& name)
	: name_(name)
	{
	}
	virtual ~uniform() {}

public:
	virtual void bind() {};//= 0;
	
public:
	const std::string& name() const
	{
		return name_;
	}
	
private:
	std::string name_;
};


/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T>
class uniform_ : public uniform {
public:	
	uniform_(const std::string& name)
	: uniform(name)
	{}

public:
	void set(const T v)
	{
		v_ = v;
	}
	T& get() { return v_; }

	////
	void operator = (T v)
	{
		v_ = v;
	}
	void operator = (T& v)
	{
		v_ = v;
	}
	void operator = (const T& v)
	{
		v_ = v;
	}
	
protected:
	T v_;
};


};//GL

