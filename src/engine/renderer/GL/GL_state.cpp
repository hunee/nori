/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "GL_state.h"


namespace GL {

/*
std::map<int, const std::string> status = {
        {200, "OK"},
        {404, "Not Found"}
    };
*/

#define __string_to_GLenum(v) { #v, v }

static std::map<const std::string, GLenum> __gl_state = {
///__GLRENDERSTATETYPE[] =
	__string_to_GLenum(GL_DEPTH_TEST),
	__string_to_GLenum(GL_SCISSOR_TEST),
	__string_to_GLenum(GL_STENCIL_TEST),

#if !defined (CGL_VERSION_1_3)
	
#if !defined (__TARGET_EGL__)
	__string_to_GLenum(GL_ALPHA_TEST),

///__SHADEMODE[] =
	__string_to_GLenum(GL_FLAT),
	__string_to_GLenum(GL_SMOOTH),

///__FILLMODE[] =
	__string_to_GLenum(GL_POINT),
	__string_to_GLenum(GL_LINE),
	__string_to_GLenum(GL_FILL),

	__string_to_GLenum(GL_CLAMP),
#endif //__TARGET_RGL__
#endif //CGL_VERSION_1_3
	
	__string_to_GLenum(GL_BLEND),

///__CULL[] =
	__string_to_GLenum(GL_CULL_FACE),
	__string_to_GLenum(GL_CW),
	__string_to_GLenum(GL_CCW),

///__BLEND[] =
	__string_to_GLenum(GL_ZERO),
	__string_to_GLenum(GL_ONE),
	__string_to_GLenum(GL_SRC_COLOR),
	__string_to_GLenum(GL_ONE_MINUS_SRC_COLOR),
	__string_to_GLenum(GL_SRC_ALPHA),
	__string_to_GLenum(GL_ONE_MINUS_SRC_ALPHA),
	__string_to_GLenum(GL_DST_ALPHA),
	__string_to_GLenum(GL_ONE_MINUS_DST_ALPHA),
	__string_to_GLenum(GL_DST_COLOR),
	__string_to_GLenum(GL_ONE_MINUS_DST_COLOR),
	__string_to_GLenum(GL_SRC_ALPHA_SATURATE),

///__CMPFUNC[] =
	__string_to_GLenum(GL_NEVER),
	__string_to_GLenum(GL_LESS),
	__string_to_GLenum(GL_EQUAL),
	__string_to_GLenum(GL_LEQUAL),
	__string_to_GLenum(GL_GREATER),
	__string_to_GLenum(GL_NOTEQUAL),
	__string_to_GLenum(GL_GEQUAL),
	__string_to_GLenum(GL_ALWAYS),

///__TEXTUREFILTERTYPE[] =
	__string_to_GLenum(GL_NEAREST),
	__string_to_GLenum(GL_LINEAR),
	__string_to_GLenum(GL_NEAREST_MIPMAP_NEAREST),
	__string_to_GLenum(GL_NEAREST_MIPMAP_LINEAR),
	__string_to_GLenum(GL_LINEAR_MIPMAP_NEAREST),
	__string_to_GLenum(GL_LINEAR_MIPMAP_LINEAR),

///__TEXTUREADDRESS[] =
	__string_to_GLenum(GL_REPEAT),
	__string_to_GLenum(GL_CLAMP_TO_EDGE),


	__string_to_GLenum(GL_ENABLE),
	__string_to_GLenum(GL_DISABLE),
	__string_to_GLenum(GL_BLEND_FUNC),

	__string_to_GLenum(NULL),
};

GLenum string_to_GLenum(const std::string& name)
{
	auto it = __gl_state.find(name);
	if (it != __gl_state.end())
		return it->second;

	return 0;
}

std::shared_ptr<state> GL_make_state(const std::string& name, const std::string& v1, const std::string& v2)
{
	//COUT << "GL_state_<" << name << ">(" << v1;
	//if (!v2.empty()) std::cout << ", " << v2;
	//std::cout << ")" << ENDL;
	
	GLenum v = string_to_GLenum(v1);

	if (!name.compare("GL_ENABLE"))
		//return std::move(std::make_unique<GLstate_<GL_ENABLE>>(v));
		return std::make_shared<GL_state_<GL_ENABLE>>(v);
	else if (!name.compare("GL_DISABLE"))
		return std::make_shared<GL_state_<GL_DISABLE>>(v);
	/*else if (!strcmp(name, "GL_FRONT_FACE"))
		return new GLstate<GL_FRONT_FACE>(GLvalue);
	else if (!strcmp(name, "GL_CULL_FACE"))
		return new GLstate<GL_CULL_FACE>(GLvalue);
	*/
	else if (!name.compare("GL_BLEND_FUNC"))
	{
		GLuint dfactor = string_to_GLenum(v2);
		return std::make_shared<GL_state_<GL_BLEND_FUNC>>(v, dfactor);
	}

#if 0	
#if !defined (CGL_VERSION_1_3)
	else if (!strcmp(name, "GL_SHADE_MODEL"))
		return new GLstate<GL_SHADE_MODEL>(GLvalue);
	else if (!strcmp(name, "GL_POLYGON_MODE"))
		return new GLstate<GL_POLYGON_MODE>(GLvalue);
	else if (!strcmp(name, "GL_ALPHA_TEST_REF"))
		return new GLstate<GL_ALPHA_TEST_REF>(GLvalue);
	else if (!strcmp(name, "GL_ALPHA_TEST_FUNC"))
		return new GLstate<GL_ALPHA_TEST_FUNC>(GLvalue);
#endif //CGL_VERSION_1_3

	else if (!strcmp(name, "GL_DEPTH_FUNC"))
		return new GLstate<GL_DEPTH_FUNC>(GLvalue);
	else if (!strcmp(name, "GL_TEXTURE_WRAP_S"))
		return new GLstate<GL_TEXTURE_WRAP_S>(GLvalue);
	else if (!strcmp(name, "GL_TEXTURE_WRAP_T"))
		return new GLstate<GL_TEXTURE_WRAP_T>(GLvalue);
	else if (!strcmp(name, "GL_TEXTURE_MAG_FILTER"))
		return new GLstate<GL_TEXTURE_MAG_FILTER>(GLvalue);
	else if (!strcmp(name, "GL_TEXTURE_MIN_FILTER"))
		return new GLstate<GL_TEXTURE_MIN_FILTER>(GLvalue);
#endif

#if 0
	else if (!strcmp(name, "GL_BLEND_DST"))
		return new GLstate<GL_BLEND_DST>(GLvalue);
	else if (!strcmp(name, "GL_BLEND_SRC"))
		return new GLstate<GL_BLEND_SRC>(GLvalue);
#endif

	return nullptr;
}
};//GL