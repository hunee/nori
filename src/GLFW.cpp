/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "GLFW.h"

#include "core/Application.h"
#include "renderer/GL/GL_framebuffer.h"

#include "os/input.h"

static double cursor_x;
static double cursor_y;

static void GLFW_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    auto in = input::get();
    in->key_ = key;
    in->key_action_ = action;
}

static void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    /*printf("%0.3f: Cursor position: %f %f (%+f %+f)\n",
           glfwGetTime(),
           x, y, x - cursor_x, y - cursor_y);

    cursor_x = x;
    cursor_y = y;*/

    auto in = input::get();
    in->cursor_.x = x;
    in->cursor_.y = y;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    /*double x, y;
    if (button != GLFW_MOUSE_BUTTON_LEFT) return;
    glfwGetCursorPos(window, &x, &y);
    if (action == GLFW_PRESS)  {
        double dt = glfwGetTime() - glfw.last_button_click;
        if (dt > NK_GLFW_DOUBLE_CLICK_LO && dt < NK_GLFW_DOUBLE_CLICK_HI) {
            glfw.is_double_click_down = nk_true;
            glfw.double_click_pos = nk_vec2((float)x, (float)y);
        }
        glfw.last_button_click = glfwGetTime();
    } else glfw.is_double_click_down = nk_false;
*/
    auto in = input::get();
    in->button_ = button;
    in->button_action_ = action;

}



/**
 * @brief Destroy the GLFW::GLFW object
 * 
 */
GLFW::~GLFW()
{
    //CLOGF();

    glfwDestroyWindow(window_);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/**
 * @brief 
 * 
 * @return int 
 */
int GLFW::init()
{
    //CLOGF();

///std::cout << KRED << "->> type_info: name: " << typeid_name(*this) << _type_info<unique_ptr<GLFW>>::name() << " hash_code: " << _type_info<GLFW>::hash_code() << RST << std::endl;
	//
	COUT << "- GLFW version: " << 
        GLFW_VERSION_MAJOR << "." << 
        GLFW_VERSION_MINOR << "." << 
        GLFW_VERSION_REVISION << ENDL;

    glfwSetErrorCallback(GLFW_error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(1024, 768, "...", NULL, NULL);
    if (!window_)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);

    auto fb = GL::GL_framebuffer::get();
    fb->set_viewport(GL::rect(0,0, width,height));

    glfwSetMouseButtonCallback(window_, mouse_button_callback);
    glfwSetCursorPosCallback(window_, cursor_position_callback);
    glfwSetKeyCallback(window_, GLFW_key_callback);

    glfwMakeContextCurrent(window_);
    //glfwSwapInterval(1);
    glfwSwapInterval(1);

////
    theApp->init();

    return 1;
}


/**
 * @brief 
 * 
 */
void GLFW::began()
{
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    ///const float ratio = width / (float) height;

    auto fb = GL::GL_framebuffer::get();
    fb->set_viewport(GL::rect(0,0, width,height));

    ///glViewport(0, 0, width, height);
    
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
}


/**
 * @brief 
 * 
 */
void GLFW::runLoop()
{
    //CLOGF();
//std::cout << KRED << "->> type_info: name: " << this->name() << " id: " << this->id() << RST << std::endl;

    while (!glfwWindowShouldClose(window_))
    {
        began();

        theApp->runLoop();

        glfwSwapBuffers(window_);

        ///
        glfwPollEvents();
    }
}
