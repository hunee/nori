/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL {

/**
 * @brief 
 * 
 */
class state {
public:
	virtual ~state() { }

public:
	virtual void bind() =0;
};

};//GL