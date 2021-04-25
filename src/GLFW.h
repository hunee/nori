/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "unique_ptr.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class GLFW : public unique_ptr<GLFW>, public _type_info<GLFW> {
public:
    ~GLFW();

public:    
    int init();

public:
    void began();

public:
    void runLoop();

private:
    GLFWwindow* window_;
};

