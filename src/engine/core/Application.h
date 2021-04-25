/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "unique_ptr.h"

#include "node.h"

//namespace GL {

/**
 *
 */
//struct event;
//class eventhandler;

class Application 
: public unique_ptr<Application>
, public _type_info<Application> {

public:
	std::shared_ptr<GL::ICLASS(node)> root_;

/**
 *
 */
public:
	Application() {}
	~Application() {};

public:
	int init();
	
private:
	int init_GL();
	int init_asset_manager();
	
	int init_lua();
	int init_python();

	int run_script();
	
public:
	int runLoop();

/**
 * @brief 
 * 
 */

};

extern Application* theApp;

//};//GL