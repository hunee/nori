/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

//std::map<const std::string, std::unique_ptr<node_>> map_;
template <typename V>
class map {
public:
	virtual ~map() {}

protected:
	std::map<const std::string, V> map_;

public:
	V& operator[] (const char* name)
	{
		//__method__

		return map_[name];
	}

	V& operator[] (const std::string& name)
	{
		return this->operator[] (name.c_str());
	}

  void insert(const std::string& name, V v)
	{
		auto ret = map_.insert(std::make_pair(name, nullptr));

		//
		if (ret.second == true)
			ret.first->second = std::move(v);	
  }

  void insert(const std::string& name, V& v)
	{
		auto ret = map_.insert(std::make_pair(name, nullptr));

		//
		if (ret.second == true)
			ret.first->second = std::move(v);	
  }

	const V& find(const char* name) const
	{
		//__method__

		auto it = map_.find(name);
		if (it == map_.end())
		{
			//throw ...
			char e[255];
			sprintf(e, E());

			throw std::runtime_error(e);
		}

		///COUT << KYEL << "typeid().name: " << (it->second ? __typeid_name(*it->second) : "nullptr") << ENDL;
		return it->second;
	}

	const V& find(const std::string& name) const
	{
		return this->find(name.c_str());
	}
};


