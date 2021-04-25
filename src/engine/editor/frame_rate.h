/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "asset/asset_manager.h"
#include "core/object.h"

#include "renderer/font/font_renderer.h"
#include "renderer/font/bitmap_font.h"
#include "renderer/font/freetype_font.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GL {

class frame_rate
: public object {
	std::shared_ptr<GL::_2d::font> bmfont_;
	std::shared_ptr<component<GL::_2d::font_renderer>> bmfrc_;
	
	std::shared_ptr<GL::_2d::font> ftfont_;
	std::shared_ptr<component<GL::_2d::font_renderer>> ftfrc_;
	std::shared_ptr<component<GL::_2d::font_renderer>> ftfrc2_;


private:
	unsigned long frame_count_ = 0;
	double frame_rate_ = 0;

public:
	frame_rate()
	{
	}

void _began() override
{
bmfont_ = asset_manager::get()->import<GL::_2d::font>(asset_path("sys.bmf"));

bmfrc_ = std::make_shared<component<GL::_2d::font_renderer>>("bmfrc");
bmfrc_->set_font(bmfont_);

ftfont_ = asset_manager::get()->import<GL::_2d::font>(asset_path("AsiaKHANM-SONY_p20.TTF"));
{
	auto p = std::dynamic_pointer_cast<GL::_2d::freetype_font> (ftfont_);
	p->new_face(asset_path("AsiaKHANM-SONY.TTF"), 20);
}

ftfrc_ = std::make_shared<component<GL::_2d::font_renderer>>("ftfrc");
ftfrc_->set_font(ftfont_);

ftfrc2_ = std::make_shared<component<GL::_2d::font_renderer>>("ftfrc2");
ftfrc2_->set_font(ftfont_);


}

void _tick(double dt) override
{
	object::_tick(dt);

	/**
	 * fps
	 */
    
	double time;//, dt;
	static double last_frametime;//, last_animtime;
	
	static bool first_call = true;
	if (first_call)
	{
		last_frametime = /*last_animtime =*/ glfwGetTime();
		first_call = false;
	}
	
	time = glfwGetTime();
	if (time > (last_frametime + 1.0))
	{
		frame_rate_ = frame_count_;
		frame_count_ = 0;
		
		last_frametime = time;
	}
	
	//dt = time - last_animtime;
	//if (dt > 0.1f) dt = 0.1f;

	//last_animtime = time;

  frame_count_ ++;
}

	void _draw() override
	{
    /////////////////////////////////////////////////////
    auto fb = GL::GL_framebuffer::get();

    //COUT << "fps: " << frame_rate_ << " dt: " << dt << ENDL;
    char fps[PATH_MAX];
    std::sprintf(fps, "FPS: %.2f width: %zu height: %zu", frame_rate_, fb->width(), fb->height());

    GL::point pos(5,5);
    bmfrc_->textout(pos, fps, 0xffffffff);

    std::string text = R"(참고로, wide character 라고 하여 반드시 "wide" 할 필요는 없습니다.
wide/mb character 에 대한 지원 의지 (혹은 필요성) 가 전혀 없는
implementation 의 경우, 간단히 wide character 를 single-byte character
로 둘 수도 있습니다.

한가지 재미있는 사실은, 만약 wchar_t 가 char 형인 환경이라면 (C++ 와는
달리) C 에서 (non-wide) character constant 가 int 형이기에

sizeof(L'a') == 1 && sizeof(L'a') <= sizeof('a')

가 참이 되어야 한다는 사실입니다. 따라서, wchar_t 를 char 형으로 두면
서 wide character 지원을 하지 않기에 간단히 character constant 앞의
L 을 무시하는 C 컴파일러는 주의하지 않으면 자신도 모르게 non-
conforming implementation 이 되어 버립니다.

이러한 이유로 wide character 를 사실상 지원하지 않는 implementation 도
wchar_t 를 최소한 short int 이상으로 정의하고, L 을 인식하여 처리하고
있습니다.)";

    std::string text2 = R"(간략하게 말하면 1999 ISO C 표준(C99)은 size_t는 객체의 크기를 나타내기 위해서 쓰이는 16비트 이상의 unsigned int타입이라고 정의합니다. (제일 밑에 원문을 첨부해뒀습니다.)

for 루프를 도는 경우, i가 항상 양수일 경우는 int/size_t 중 어느 걸 써도 무방한데요 다만 int를 쓰는 경우는 오버플로우가 날 수 있으니 i의 값이 너무 커진다 싶을 때는 size_t를 써야 합니다.

그리고 size_t는 항상 양수이므로 i가 음수가 될 수 있는 경우는 당연히 int를 써야 합니다.)";


    wchar_t wtext[PATH_MAX];
    wchar_t wtext2[PATH_MAX];

if (ftfrc_->is_renew_)
    M2W(wtext, text.c_str());

if (ftfrc2_->is_renew_)
    M2W(wtext2, text2.c_str());

    GL::point pos2(5,50);
    ftfrc_->textout(pos2, wtext, 0xffffffff);

    GL::point pos3(50,150);
    ftfrc2_->textout(pos3, wtext2, 0xffffff00);

ftfrc_->is_renew_ = false;
ftfrc2_->is_renew_ = false;


	}
};

};//GL
