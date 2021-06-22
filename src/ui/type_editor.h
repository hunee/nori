/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

namespace GL::ui {

/**
 * @brief 
 * 
 */
class panel {
public:
	button();
	virtual ~button();

public:
	rect rect_;

	uint highlight_color_;
	uint dark_color_;
	uint background_color_;

public:
	//abgr = 0x00BBGGRR
	void draw_rect(const rect& rect, uint color = 0xffffffff);

	void draw_rect(const rect& rect, uint highlightColor, uint darkColor);
	void draw_rect(const rect& rect, uint highlightColor, uint darkColor, uint backgroundColor);

};

};//GL::ui

