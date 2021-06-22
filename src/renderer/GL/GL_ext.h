/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

////
#ifdef USE_GLEW
  #include <GL/glew.h>

#else
	#include <glad/gl.h>
#endif

#include "math/math.h"

/**
 *
 */
enum {
	FMT_UNKNOWN = 0,

	FMT_R8G8B8,
	FMT_A8R8G8B8,

	FMT_R5G6B5,
	FMT_A1R5G5B5,
	FMT_A4R4G4B4,

	FMT_A8,
	FMT_L8,
	FMT_A8L8,

	FMT_DXT1,
	FMT_DXT3,
	FMT_DXT5,

	FMT_INDEX16 = 0,				// 16-bit index buffer bit depth.
	FMT_INDEX32,					// 32-bit index buffer bit depth.
	FMT_FORCE_DWORD = 0x7fffffff,	// force 32-bit size enum
};


/**
 * Vertex attributes
 */
enum {
	ATTRIB_POSITION=0,
	ATTRIB_NORMAL,
	ATTRIB_COLOR,
	ATTRIB_TANGENT,
	ATTRIB_BINORMAL,
	ATTRIB_TEXCOORD0,
	ATTRIB_TEXCOORD1,
	ATTRIB_BONEWEIGHT,
	ATTRIB_BONEINDEX,
};


#if !defined (GL_INVALID_HANDLE_VALUE)
#define GL_INVALID_HANDLE_VALUE 0xffffffff
#endif //GL_INVALID_HANDLE_VALUE

#if !defined (GL_CLAMP_TO_EDGE)
#define GL_CLAMP_TO_EDGE GL_CLAMP
#endif


/* Shaders */
extern GLint MAX_VERTEX_ATTRIBS;
extern GLint MAX_COMBINED_TEXTURE_IMAGE_UNITS;
extern GLint MAX_VERTEX_TEXTURE_IMAGE_UNITS;
extern GLint MAX_TEXTURE_IMAGE_UNITS;
extern GLint MAX_TEXTURE_SIZE;


extern void check_GLextensions();

extern const char * glGetShaderLanguageVersion();

static inline const char * glGetError_string(GLenum error)
{
	const char *str;
	switch (error)
	{
		case GL_NO_ERROR:
			str = "GL_NO_ERROR";
			break;
		case GL_INVALID_ENUM:
			str = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			str = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			str = "GL_INVALID_OPERATION";
			break;
#if defined __gl_h_ || defined __gl3_h_
		case GL_OUT_OF_MEMORY:
			str = "GL_OUT_OF_MEMORY";
			break;

#if defined (__APPLE__)
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			str = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
#endif
#endif
#if defined __gl_h_
		case GL_STACK_OVERFLOW:
			str = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			str = "GL_STACK_UNDERFLOW";
			break;

#if 0//defined (__APPLE__)
		case GL_TABLE_TOO_LARGE:
			str = "GL_TABLE_TOO_LARGE";
			break;
#endif
#endif
		default:
			str = "(ERROR: Unknown Error Enum)";
			break;
	}
	return str;
}

#define glCheckError() \
{	\
GLenum err = glGetError(); \
while (err != GL_NO_ERROR) { \
std::cout << KRED << "GLerror: " << glGetError_string(err) << RST << std::endl; \
err = glGetError();	\
}	\
}

