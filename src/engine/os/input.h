/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "unique_ptr.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class input : public unique_ptr<input> {
public:
~input() {}

int key_ =0;
int key_action_ =0;

int button_ =0;
int button_action_ =0;

GL::float2 cursor_;
};
