/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/GL/GL_texture.h"

#define USE_TARGA

#ifdef USE_TARGA

#include "targa/targa.h"

namespace ext {
	
class targa {
public:
	std::shared_ptr<asset_> import(const std::string& pathname)
{
  //__method__

	tga_image tga;
	tga_result result = tga_read(&tga, pathname.c_str());
	if (result != TGA_NOERR)
	{
		tga_free_buffers(&tga);
		return nullptr;
	}

	//
	if (tga_is_top_to_bottom(&tga))
		tga_flip_vert(&tga);

	//
	if (tga_is_right_to_left(&tga))
		tga_flip_horiz(&tga);

	tga_swap_red_blue(&tga);


/////
  std::shared_ptr<asset_> texture = nullptr;

  try {
    switch (tga.pixel_depth)
    {
    case 24:
    {
      //COUT << "24" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGB>> ();
      p->texImage(0, tga.width, tga.height, tga.image_data);
      texture.reset(p);
    }
      break;

    case 32:
    {
      //COUT << "32" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGBA>> ();
      p->texImage(0, tga.width, tga.height, tga.image_data);
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
	tga_free_buffers(&tga);
    
  return texture;
}
};

}; //ext

#endif //USE_TARGA
