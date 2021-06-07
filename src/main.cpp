/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "GLFW.h"

class B {};

class A {

public:
A() 
{
__method__

CLOG_printf("A(--------------------)\n");

std::shared_ptr<B> b = std::make_shared<B>();

CLOG_ptr(b)
CLOG_shared_ptr(b)

COUT << COUT_method << ENDL;
//COUT << FUNC << ENDL;

//COUT << SHARED_PTR(b) << ENDL;
//COUT << PTR(this) << ENDL;
}
};


/**
 */
int main()
{
#if 0
  LOG_printf("main\n")

  LOG_cout << COUT_func << ENDL;

  std::shared_ptr<A> a = std::make_shared<A>();

LOG_ptr(a)
LOG_shared_ptr(a)

LOG_cout << COUT_func << " - " << COUT_ptr(a) << ENDL;
COUT << COUT_func << " - " << COUT_shared_ptr(a) << ENDL;


std::cout << "...thread calls flush()" << std::endl;
std::clog << "This output from main is not tie()'d to cout\n";
std::cerr << "This output is tie()'d to cout\n";
#endif

    ////
    #if defined(_WIN32)

    // Enable run-time memory check for debug builds.
    #if defined (_DEBUG)
    #if defined (_MSC_VER)
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif //_MSC_VER
    #endif //_DEBUG
    #endif //_WIN32

#if 0
try 
{
  //throw ...
  char e[255];
  sprintf(e, E_str());

  throw std::runtime_error(e);
} 
catch (std::exception& e) 
{
  COUT << e.what() << ENDL;
}
#endif


///    __function__

    auto glfw = GLFW::get();
    glfw->init();

    glfw->runLoop();
}
