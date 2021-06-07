/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/buffer.h"

#include "GL_handle.h"

namespace GL {


/**
 *
 */

//GL_ELEMENT_ARRAY_BUFFER
//GL_ARRAY_BUFFER

#if !defined (GL_ALLOC_ARRAY_BUFFER)
#define GL_ALLOC_ARRAY_BUFFER	0x100
#endif

template <typename T, GLint target, GLenum mode = GL_TRIANGLE_STRIP, GLenum access = GL_WRITE_ONLY>
class GL_buffer : public GL_handle, public buffer {
private:
	std::unique_ptr<char[]> ptr_;
	GLsizeiptr size_;
	GLsizeiptr msize_;

public:
	GL_buffer(GLsizeiptr size)
	: size_(size)
	, msize_(sizeof(T) * size)
	{
		//__method__

		glGenBuffers(1, &handle_);
		glBindBuffer(target, handle_);	

		if (target == GL_ALLOC_ARRAY_BUFFER) {
			//ptr_ = std::make_unique<char>(size);
			ptr_.reset(new char[msize_]);
			return;
		}

		//allocate enough space in VRAM
		glBufferData(target, msize_, NULL, GL_STATIC_DRAW);
	}
	~GL_buffer()
	{
		if (is_validate())
			glDeleteBuffers(1, &handle_);
	}

public:
	void * map()
	{
		//__method__

		if (target == GL_ALLOC_ARRAY_BUFFER)
			return ptr_.get();
		
		//map the VBO into client memory and fill it
		glBindBuffer(target, handle_);
		return glMapBuffer(target, access);		
	}
	void unmap()
	{
		if (target == GL_ALLOC_ARRAY_BUFFER) {
			glBindBuffer(target, handle_);	
			glBufferData(target, msize_, ptr_.get(), GL_STATIC_DRAW);

			return;
		}

		glUnmapBuffer(target);
	}

	void bind()
	{
		glBindBuffer(target, handle_);
	}

	void draw()
	{
		if (target == GL_ARRAY_BUFFER)
			glDrawArrays(mode, 0, size_);
	}
};



/**
 * @brief 
 * 
 */
#define GL_vertex_attrib_array(index, size, type, normalized, stride, pointer) \
	glEnableVertexAttribArray(index); \
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);


/**
 * V2F_C4B_T2F
 */
struct V2F_C4B_T2F {
	float2 position;
	uint color;
	float2 tex0;
};

template <typename T = V2F_C4B_T2F>
class GL_vertex_attrib {
public:
	GL_vertex_attrib()
	{
		//__method__

		//GL_vertex_attrib_array(ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offsetof(T, position));
		//GL_vertex_attrib_array(ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(T), (void*) offsetof(T, color));
		//GL_vertex_attrib_array(ATTRIB_TEXCOORD0, 2, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offsetof(T, tex0));

		GL_vertex_attrib_array(0, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offsetof(T, position));
		GL_vertex_attrib_array(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(T), (void*) offsetof(T, color));
		GL_vertex_attrib_array(2, 2, GL_FLOAT, GL_FALSE, sizeof(T), (void*) offsetof(T, tex0));
	}
};


/**
 * V2F_C4B
 */
struct V2F_C4B {
	float2 position;
	uint color;
};

template<>
class GL_vertex_attrib<V2F_C4B> {
public:
	GL_vertex_attrib()
	{
		//__method__

		GL_vertex_attrib_array(0, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B), (void*) offsetof(V2F_C4B, position));
		GL_vertex_attrib_array(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B), (void*) offsetof(V2F_C4B, color));
	}
};

////vb_ = GL_buffer_<V2F_C4B_T2F, GL_ARRAY_BUFFER, GL_TRIANGLE_STRIP, GL_WRITE_ONLY>(4);
template <typename T=V2F_C4B_T2F, GLint target = GL_ARRAY_BUFFER, GLenum mode = GL_TRIANGLE_STRIP, GLenum access = GL_WRITE_ONLY>
class GL_buffer_ : public GL_buffer<T, target, mode, access>, public GL_vertex_attrib<T> {
public:
	GL_buffer_(GLsizeiptr size)
	: GL_buffer<T, target, mode, access>(size)
	, GL_vertex_attrib<T>()
	{
		//__method__
	}

	void bind()
	{
		//__method__

		//GL_buffer<target, access>::begin();			
	}
};


/**
 * @brief 
 * 
 */
class GL_vertex_array : 
	public vertex_array,
	public GL_handle {

public:
	GL_vertex_array()
	{
		//__method__
		
		glGenVertexArrays(1, &handle_);

		glBindVertexArray(handle_);
	}
	~GL_vertex_array()
	{
		if (is_validate())
			glDeleteVertexArrays(1, &handle_);
	}

public:
	void bind()
	{
		glBindVertexArray(handle_);
	}
};

};//GL