/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "GLFW.h"

/**
 */
int main()
{
    ///CLOG_(KCLR);

    ////
    #if defined(_WIN32)

    // Enable run-time memory check for debug builds.
    #if defined (_DEBUG)
    #if defined (_MSC_VER)
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif //_MSC_VER
    #endif //_DEBUG
    #endif //_WIN32


///    LOGF();

    auto glfw = GLFW::get();
    glfw->init();

    glfw->runLoop();
}
