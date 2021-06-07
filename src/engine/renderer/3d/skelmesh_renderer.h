
/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

class UIobject {

};

class GLtexture;
class GLbuffer;
class GLvertex_attrib;

class GLshader;


class GLsprite_renderer {
public:
	GLsprite_renderer(const std::string& name);
	~GLsprite_renderer();
	
	
public:
	///
	//abgr = 0x00BBGGRR
	void draw(const GLint2& pos, const GLtexture* texture, GLuint color = 0xffffffff, GLfloat alpha = 1.0f);
	void draw(const GLint2& pos, const GLtexture* texture, const GLint2& size, GLuint color = 0xffffffff, GLfloat alpha = 1.0f);
	
	void draw(const GLint2& pos, const GLtexture* texture, const GLint4& rect, GLuint color = 0xffffffff, GLfloat alpha = 1.0f);
	
private:
	GLbuffer* vb_;
	GLvertex_attrib* vertex_attrib_;

	GLshader* shader_;
};
