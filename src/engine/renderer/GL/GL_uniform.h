/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/uniform.h"

namespace GL {

template<typename T>
class GL_uniform : public uniform_<T> {
public:
	GL_uniform(const std::string& name, GLuint handle)
	: uniform_<T>(name)
	{
		location_ = glGetUniformLocation(handle, name.c_str());		
	}
protected:
	GLuint location_;	
};


/**
 * @brief 
 * 
 * @tparam T 
 */
template<typename T = float>
class GL_uniform_ : public GL_uniform<T> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<T>(name, handle)
	{
	}

public:
	void bind() override
	{
		glUniform1f(GL_uniform<T>::location_, GL_uniform<T>::v_);
	}
};


/**
 * @brief 
 * 
 * @tparam  
 */
template<>
class GL_uniform_<int> : public GL_uniform<int> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<int>(name, handle)
	{
	}

public:
	void bind() override
	{
		glUniform1i(location_, v_);
	}
};


static std::map<const std::string, unsigned int> __tex_stage = {
	{"TEX0", 0},
	{"TEX1", 1},
	{"TEX2", 2},
	{"TEX3", 3}
};

/**
 * @brief 
 * 
 * @tparam  
 */
template<>
class GL_uniform_<unsigned int> : public GL_uniform<unsigned int> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<unsigned int>(name, handle)
	{
		if (location_ != GL_INVALID_HANDLE_VALUE)
		{
			auto it = __tex_stage.find(name);
			if (it != __tex_stage.end())
			{
				auto n = it->second;
				glUniform1i(location_, n);

				location_ = n;
			}
		}
	}

public:
	void bind() override
	{
		glActiveTexture(GL_TEXTURE0 + location_);
		glBindTexture(GL_TEXTURE_2D, v_);
	}
};


/**
 * @brief 
 * 
 * @tparam  
 */
template<>
class GL_uniform_<GL::float2> : public GL_uniform<GL::float2> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<GL::float2>(name, handle)
	{
	}

public:
	void bind() override
	{
		//__method__

		glUniform2f(location_, v_.x,v_.y);
	}
};


/**
 * @brief 
 * 
 * @tparam  
 */
template<>
class GL_uniform_<GL::float3> : public GL_uniform<GL::float3> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<GL::float3>(name, handle)
	{
	}

public:
	void bind() override
	{
		glUniform3f(location_, v_.x,v_.y,v_.z);
	}
};


/**
 * @brief 
 * 
 * @tparam  
 */
template<>
class GL_uniform_<GL::float4> : public GL_uniform<GL::float4> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<GL::float4>(name, handle)
	{
	}

public:
	void bind() override
	{
		glUniform4f(location_, v_.x,v_.y,v_.z,v_.w);
	}
};


/**
 * @brief 
 * 
 * @tparam  
 */
#if 0
template<>
class GL_uniform_<GL::float3x3> : public GL_uniform<GL::float3x3> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<GL::float3x3>(name, handle)
	{
	}

public:
	void bind() override
	{
		glUniformMatrix3fv(location_, 1, GL_FALSE, v_.m);
	}
};
#endif

/**
 * @brief 
 * 
 * @tparam  
 */
template<>
class GL_uniform_<GL::float4x4> : public GL_uniform<GL::float4x4> {
public:
	GL_uniform_(const std::string& name, GLuint handle)
	: GL_uniform<GL::float4x4>(name, handle)
	{
	}

public:
	void bind() override
	{
		glUniformMatrix4fv(location_, 1, GL_FALSE, &v_[0]);
	}
};

};//GL

