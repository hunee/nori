/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once


namespace GL {

/**
 * @brief 
 * 
 */
class buffer {
public:
	virtual ~buffer() {}

public:
	virtual void * map() =0;
	virtual void unmap() =0;

public:
	virtual void bind() =0;

public:
	virtual void draw() =0;
};

/**
 * @brief 
 * 
 */
class vertex_array {
public:
	virtual ~vertex_array() {}

public:
	virtual void bind() =0;
};

};//GL