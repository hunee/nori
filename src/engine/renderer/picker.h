/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "core/object.h"

#include "unique_ptr.h"

namespace GL {
class input;

class picker : public unique_ptr<picker> {
public:
	std::vector<std::shared_ptr<GL::object>> picked_;

	void flush();
};

};//GL