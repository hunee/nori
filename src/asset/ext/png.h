/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 2; tab-width: 2 -*- */

#pragma once

#include "renderer/GL/GL_texture.h"

#ifndef USE_STB

#include <png.h>

namespace ext {

class png {
public:
  unsigned char *  png_load(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha) 
  {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
    
    if ((fp = fopen(name, "rb")) == NULL)
        return nullptr;
    
    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
    
    if (png_ptr == NULL) {
        fclose(fp);
        return nullptr;
    }
    
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return nullptr;
    }
    
    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return nullptr;
    }
    
    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
    
    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
    
    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
    
    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);

    outWidth = width;
    outHeight = height;

    switch (png_get_color_type(png_ptr, info_ptr)) {
      case PNG_COLOR_TYPE_RGBA:
          outHasAlpha = 1;
          break;
      case PNG_COLOR_TYPE_RGB:
          outHasAlpha = 0;
          break;
      default:
          printf("Color type %d not supported!\n", 
              png_get_color_type(png_ptr, info_ptr));
          png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
          return nullptr;
    }


    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    unsigned char * image_data = (unsigned char*) malloc(row_bytes * outHeight);
    
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    
    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(image_data+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }

    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    /* Close the file */
    fclose(fp);
    
    /* That's it */
    return image_data;
}

	std::shared_ptr<asset_> import(const std::string& pathname)
{
  //__method__

  int width, height;
  bool has_alpha;

  unsigned char *image_data = png_load(pathname.c_str(), width, height, has_alpha);

  int nrChannels = 3 + has_alpha;
  COUT << width << " " << height << " "  << has_alpha << ENDL;

/////
  std::shared_ptr<asset_> texture = nullptr;

  try {
    switch (nrChannels)
    {
    case 3:
    {
      //COUT << "24" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGB>> ();
      p->texImage(0, width, height, image_data);
      texture.reset(p);
    }
      break;

    case 4:
    {
      //COUT << "32" <<ENDL;

      auto p = new asset<GL::GL_texture_<GL_TEXTURE_2D, GL_RGBA>> ();
      p->texImage(0, width, height, image_data);
      texture.reset(p);
    }
      break;
    }
  } 
  catch (std::exception& e) {
    COUT << e.what() << ENDL;
  }

  free(image_data);
    
  return texture;
}

};

}; //ext

#endif //USE_STB