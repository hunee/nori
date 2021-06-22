/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#include "stdafx.h"

#include "asset_manager.h"

#include "GL/GL_texture.h"

#include "targa.h"

#include <regex>

namespace ext {

std::shared_ptr<asset_> targa::import(const std::string& pathname)
{
  //__method__


  std::string code = R"(
# Initialization file..
# This file supports line comments, and does not support trailing comments.
# Text here is not case sensitive.
# White spaces are ignored in file processing. 
# Values are comma "," separated.

Shader "Custom/colorShader"
Properties
  _MyColor ("Green Color", Color) = (0, 1, 0, 1)
SubShader
  Pass
    Material
      Diffuse[_MyColor]
      Lighting On
FallBack "Diffuse"
)";

//std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
//std::regex shader_re(R"r(- ([\w /-]*) "([\w /-]*)"|"([\w /-]*)")r");
//std::regex shader_re(R"r(- ([\w /-]*) ([\w /-]*))r");

/*

regex reg("\\s*\\s|([,.!\"]+)\\s*");
sregex_token_iterator iter(str.begin(), str.end(), reg, {-1,1}), end;
vector<string> vec;
copy_if(iter, end, back_inserter(vec), [](const string& x) { return x.size(); });


regex reg(R"(\d+|[^\W\d]+|[^\w\s])");
sregex_token_iterator iter(str.begin(), str.end(), reg), end;
vector<string> vec(iter, end);

\d+ - 1 or more digits
| - or
[^\W\d]+ - 1 or more ASCII letters or _
| - or
[^\w\s] - 1 char other than an ASCII letter/digit,_ and whitespace.
*/

//std::regex pattern{"#.*[\r\n]*"};
//std::string modified_code = std::regex_replace (code, pattern, "");

//std::regex repl(R"((["|,|(|)|=])|(#.*[\r\n]*))");
std::regex repl(R"(([,|=])|(#.*[\r\n]*))");
std::string modified_code = std::regex_replace(code, repl, "");

auto const re = std::regex{R"(\s+)"};
auto const tokens = std::vector<std::string>(
    std::sregex_token_iterator{begin(modified_code), end(modified_code), re, -1},
    std::sregex_token_iterator{}
);

//for (const auto& t : tokens) {
//        std::cout << t << "." << std::endl;
//    }

    auto token = tokens.begin();
    while (token != tokens.end())
    {
      std::cout << *token << "." << std::endl;

      token++;
    }

      //auto p = std::make_shared<asset_ptr<GL::texture>>();
      auto p = std::make_shared<asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGB>>>();
      ///p->reset(new GLtexture());

      return p;
}

};//ext