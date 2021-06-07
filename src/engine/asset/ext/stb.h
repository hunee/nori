/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/GL/GL_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace ext {
	
class stb {
public:
	std::shared_ptr<asset_> import(const std::string& pathname)
{
  //__method__

  stbi_set_flip_vertically_on_load(true); 

  int width, height, nrChannels;
  unsigned char *data = stbi_load(pathname.c_str(), &width, &height, &nrChannels, 0);
  
  ///COUT << "nrChannels: " << nrChannels << ENDL;

  std::shared_ptr<asset_> texture = nullptr;

  try {
    switch (nrChannels)
    {
      case 2:
    {
      ///COUT << "24" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_LUMINANCE>> ();
      p->texImage(0, width, height, data);
      texture.reset(p);
    }
      break;
    case 3:
    {
      ///COUT << "24" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGB>> ();
      p->texImage(0, width, height, data);
      texture.reset(p);
    }
      break;

    case 4:
    {
      ///COUT << "32" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGBA>> ();
      p->texImage(0, width, height, data);
      texture.reset(p);
    }
      break;
    }
  } 
  catch (std::exception& e) {
    COUT << e.what() << ENDL;
  }


  //auto p = std::make_shared<asset_ptr<GL::texture>>();
  //auto p = std::make_shared<asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGB>>>();
  ///p->reset(new GLtexture());
  stbi_image_free(data);
    
  return texture;
}
};

}; //ext