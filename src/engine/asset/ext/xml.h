/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace ext {

/**
 * @brief
 * 
 */
class ICLASS(xml_parser) {
public:
	virtual ~ICLASS(xml_parser)() {}

public:
	// pure virtual function providing interface framework.
	virtual std::shared_ptr<ICLASS(asset)> parser(const XMLElement*) =0;
};


/**
 * @brief 
 * 
 */
template <typename ext>
class xml_parser : public ICLASS(xml_parser), public ext {
public:
	std::shared_ptr<ICLASS(asset)> parser(const XMLElement* element) override
	{
    return ext::parser(element);
  }
};


/**
 * @brief 
 * 
 */
class xml 
: public std::map<const std::string, std::unique_ptr<ICLASS(xml_parser)>> {

public:
	
	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @param name 
	 * @return std::shared_ptr<T> 
	 */
	std::shared_ptr<ICLASS(asset)> parser(const std::string& name, const XMLElement *element)
	{
		//CLOGF();

		auto it = find(name);
		if (it != end())
		{
				auto second = it->second->parser(element);
				return second;
		}

		return nullptr;
	}

	/**
	 * @brief 
	 * 
	 * @param pathname 
	 * @return std::shared_ptr<ICLASS(asset)> 
	 */
	std::shared_ptr<ICLASS(asset)> import(const std::string& pathname)
{
  //CLOGF();

	XMLDocument doc;
	doc.LoadFile(pathname.c_str());

  if (doc.ErrorID() != XML_SUCCESS)
  {
    //throw ...
		char e[255];
		sprintf(e, "XML Parsing %s", doc.ErrorStr());

		throw std::runtime_error(e);
  }

  /// parser
	auto body_element = doc.FirstChildElement("body");
  for (auto node_element = body_element->FirstChildElement("node"); node_element; node_element = node_element->NextSiblingElement())
  {
    auto node_class = node_element->Attribute("class");
    //COUT << node_class << ENDL;

		if (!strcmp(node_class, "header"))
		{
			// Get the "header" element.
			// It is a child of the document, and can be selected by name.
			auto info_element = node_element->FirstChildElement("info");
			if (info_element)
			{
				auto info_name = info_element->Attribute("name");
				auto info_version = info_element->Attribute("version");

        //COUT << "info_name: " << info_name << ENDL;
        //COUT << "info_version: " << info_version << ENDL;
			}
    }
    else
    {
      /* code */
      auto p = parser(node_class, node_element);
      return p;
    }    
  }

  return nullptr;
}

	/**
	 * @brief 
	 * 
	 */
	void dump()
	{
		//CLOGF();

		for (auto&& kv : *this)
		{
      COUT << "parser ext: \"" << kv.first << "\", type: " << typeid_name(*kv.second) << ENDL;
		}
	}
};

};//ext