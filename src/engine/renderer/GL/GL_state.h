/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/state.h"

#include "GL_ext.h"


namespace GL {

enum {
	GL_ENABLE = 1,
	GL_DISABLE,

	GL_BLEND_FUNC,
	
#if defined (__TARGET_EGL__)
	GL_BLEND_DST,
	GL_BLEND_SRC,

	GL_SHADE_MODEL,
	GL_POLYGON_MODE,

	GL_ALPHA_TEST_REF,
	GL_ALPHA_TEST_FUNC,

#endif
//	GL_FRONT_FACE,
//	GL_CULL_FACE,
//	GL_DEPTH_FUNC,

//	GL_TEXTURE_WRAP_S,
//	GL_TEXTURE_WRAP_T,
//	GL_TEXTURE_MAG_FILTER,
//	GL_TEXTURE_MIN_FILTER,
};

/*
const GLuint __GL {
	///__GLRENDERSTATETYPE[] =
	GL_DEPTH_TEST,
	GL_STENCIL_TEST,
	GL_ALPHA_TEST,
	GL_BLEND,

	///__CULL[] =
	GL_CULL_FACE,
	GL_CW,
	GL_CCW,

	///__BLEND[] =
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA_SATURATE,

	///__SHADEMODE[] =
	GL_FLAT,
	GL_SMOOTH,
	GL_SMOOTH,

	///__FILLMODE[] =
	GL_POINT,
	GL_LINE,
	GL_FILL,

	///__CMPFUNC[] =
	GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS,

	///__TEXTUREFILTERTYPE[] =
	GL_NEAREST,
	GL_LINEAR,
	GL_NEAREST_MIPMAP_NEAREST,
	GL_NEAREST_MIPMAP_LINEAR,
	GL_LINEAR_MIPMAP_NEAREST,
	GL_LINEAR_MIPMAP_LINEAR,

	///__TEXTUREADDRESS[] =
	GL_REPEAT,
	GL_CLAMP,
};
*/


extern GLenum string_to_GLenum(const std::string& name);
extern std::shared_ptr<state> GL_make_state(const std::string& name, const std::string& v1, const std::string& v2);


/**
 * @brief 
 * 
 * @tparam type 
 */
template<GLint type = GL_ENABLE>
class GL_state_ : public state {
private:
	GLenum v_;

public:
	GL_state_(GLenum v) : v_(v)	{} 

public:	
	void bind() override
	{
		glEnable(v_);
	}
};

template<>
class GL_state_<GL_DISABLE> : public state {
private:
	GLenum v_;

public:
	GL_state_(GLenum v) : v_(v) {}

public:
	void bind()
	{
		glDisable(v_);
	}
};

#if 0
template<>
class GLstate<GL_FRONT_FACE> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glFrontFace(_value);
	}
};

template<>
class GLstate<GL_CULL_FACE> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glCullFace(_value);
	}
};
#endif


template<>
class GL_state_<GL_BLEND_FUNC> : public state {
private:
	GLenum v1_, v2_;

public:
	GL_state_(GLenum v1, GLenum v2) : v1_(v1), v2_(v2) {}

public:
	void bind() override
	{
		glBlendFunc(v1_, v2_);
	}
	
};


#if 0
template<>
class GLstate<GL_BLEND_DST> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		GLint blend;
		glGetIntegerv(GL_BLEND_DST, &blend);
		glBlendFunc(blend, _value);
	}
};

template<>
class GLstate<GL_BLEND_SRC> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		GLint blend;
		glGetIntegerv(GL_BLEND_SRC, &blend);
		glBlendFunc(blend, _value);
	}
};


#if !defined (CGL_VERSION_1_3)

template<>
class GLstate<GL_SHADE_MODEL> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
#if !defined (__TARGET_EGL__)
		glShadeModel(_value);
#endif
	}
};
 
template<>
class GLstate<GL_POLYGON_MODE> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
#if !defined (__TARGET_EGL__)
		glPolygonMode(GL_FRONT, _value);
#endif
	}
};
#endif

template<>
class GLstate<GL_DEPTH_FUNC> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glDepthFunc(_value);
	}
};

///
template<>
class GLstate<GL_TEXTURE_WRAP_S> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _value);
	}
};
template<>
class GLstate<GL_TEXTURE_WRAP_T> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _value);
	}
};

template<>
class GLstate<GL_TEXTURE_MAG_FILTER> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _value);
	}
};
template<>
class GLstate<GL_TEXTURE_MIN_FILTER> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _value);
	}
};
#endif

#if 0
template<>
class GLstate<GL_ALPHA_TEST_REF> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
#if !defined (__TARGET_EGL__)
		GLfloat ref;
		glGetFloatv(GL_ALPHA_TEST_REF, &ref);

		glAlphaFunc(_value, ref);
#endif
	}
};
template<>
class GLstate<GL_ALPHA_TEST_FUNC> : public GLIstate {
public:
	GLstate(GLuint value)
		: GLIstate(value)
	{
	}
	void bind()
	{
#if !defined (__TARGET_EGL__)
		GLint func;
		glGetIntegerv(GL_ALPHA_TEST_FUNC, &func);

		glAlphaFunc(func, (GLfloat) _value / 255.0f);
#endif
	}
};
#endif


};//GL