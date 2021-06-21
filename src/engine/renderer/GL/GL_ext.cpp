/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "GL_ext.h"

///#ifdef __USING_GLFW__

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

///#endif //__USING_GLFW__

/* Shaders */
GLint MAX_VERTEX_ATTRIBS = 0;
GLint MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0;
GLint MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0;
GLint MAX_TEXTURE_IMAGE_UNITS = 0;
GLint MAX_TEXTURE_SIZE = 0;

static char GL_SHADING_LANGUAGE_VERSION_STR[] = "#version 123\n";

const char * glGetShaderLanguageVersion()
{
	return GL_SHADING_LANGUAGE_VERSION_STR;
}

/**
 * @brief 
 * 
 */
void check_GLextensions()
{
	//__function__

#ifdef USE_GLEW
  if (glewInit() != GLEW_OK)
    return;

#else
	if (!gladLoadGL(glfwGetProcAddress))
		return;
#endif

/*
	char* renderer = (char*) glGetString(GL_RENDERER);
	char* version = (char*) glGetString(GL_VERSION);
	char* slversion = (char*) glGetString(GL_SHADING_LANGUAGE_VERSION);
	char* vendor = (char*) glGetString(GL_VENDOR);
		
	COUT << "- GL_RENDERER: " << renderer << ENDL;
	COUT << "- GL_VERSION: " << version << ENDL;
	COUT << "- GL_SHADING_LANGUAGE_VERSION: " << slversion << ENDL;
	COUT << "- GL_VENDOR: " << vendor << ENDL;
*/

	// Determine if GLSL version 140 is supported by this context.
	//  We'll use this info to generate a GLSL shader source string  
	//  with the proper version preprocessor string prepended
	GLfloat _gl_shading_language_version;

#if defined (__TARGET_EGL__)
	sscanf((char *)glGetString(GL_SHADING_LANGUAGE_VERSION), "OpenGL ES GLSL ES %f", &_gl_shading_language_version);
#else
	sscanf((char *)glGetString(GL_SHADING_LANGUAGE_VERSION), "%f", &_gl_shading_language_version);	
#endif

	// GL_SHADING_LANGUAGE_VERSION returns the version standard version form 
	//  with decimals, but the GLSL version preprocessor directive simply
	//  uses integers (thus 1.10 should 110 and 1.40 should be 140, etc.)
	//  We multiply the floating point number by 100 to get a proper
	//  number for the GLSL preprocessor directive
	GLuint shading_language_version = (GLuint) (100.0f * _gl_shading_language_version);
	
	// Prepend our vertex shader source string with the supported GLSL version so
	//  the shader will work on ES, Legacy, and OpenGL 3.2 Core Profile contexts
	sprintf(GL_SHADING_LANGUAGE_VERSION_STR, "#version %d\n", shading_language_version);
	//COUT << "- GL_SHADING_LANGUAGE_VERSION_STR: " << GL_SHADING_LANGUAGE_VERSION_STR;

	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &MAX_VERTEX_ATTRIBS);
	//COUT << "- GL_MAX_VERTEX_ATTRIBS: " << MAX_VERTEX_ATTRIBS << ENDL;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &MAX_TEXTURE_SIZE);
	//COUT << "- GL_MAX_TEXTURE_SIZE: " << MAX_TEXTURE_SIZE << ENDL;

	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	//COUT << "- GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: " << MAX_COMBINED_TEXTURE_IMAGE_UNITS << ENDL;

	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	//COUT << "- GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: " << MAX_VERTEX_TEXTURE_IMAGE_UNITS << ENDL;

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_IMAGE_UNITS);
	//COUT << "- GL_MAX_TEXTURE_IMAGE_UNITS: " << MAX_TEXTURE_IMAGE_UNITS << ENDL;


#if 0
	// check for existance in the list of extension names, and if it's there
	// look up all of the functions and set the flag stating multitexturing
	// is availible.
  unsigned int num_exts = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts);
	COUT << "- GL_EXTENSIONS: " << num_exts << ENDL;

	for (int index = 0; index < num_exts; ++index) 
	{
		const char *extension = (const char*) glGetStringi(GL_EXTENSIONS, index);
		COUT << "-- " << extension << ENDL;
	}
#endif
	
	/*
  glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
*/
	//glFrontFace(GL_CCW);
  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);

	//glEnable(GL_DEPTH_TEST);
}

