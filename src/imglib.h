//
//  imglib.h
//  Seam-Carving
//
//  Created by Fu Changqing on 21/11/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//


#ifndef _imglib_h
#define _imglib_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <sys/queue.h>

//type
typedef unsigned char color_component;
typedef color_component pixel[3];
typedef struct {
    unsigned int width;
    unsigned int height;
    pixel * buf;
} image_t;
typedef image_t * image;

//type-gray
typedef unsigned char luminance;
typedef luminance pixel1[1];
typedef struct {
    unsigned int width;
    unsigned int height;
    pixel1 *buf;
} grayimage_t;
typedef grayimage_t * grayimage;

//function
image alloc_img(unsigned int width, unsigned int height);
void free_img(image);
void fill_img(image img,
              color_component r,
              color_component g,
              color_component b );
void put_pixel_unsafe(
                      image img,
                      unsigned int x,
                      unsigned int y,
                      color_component r,
                      color_component g,
                      color_component b );
void put_pixel_clip(
                    image img,
                    unsigned int x,
                    unsigned int y,
                    color_component r,
                    color_component g,
                    color_component b );
image read_image(const char *name);
image get_ppm(FILE *pf);
void output_ppm(FILE *fd, image img);

//function-gray
grayimage alloc_grayimg(unsigned int, unsigned int);
grayimage tograyscale(image);

void free_grayimg(grayimage);

image tocolor(grayimage);

#define GET_PIXEL(IMG, X, Y) (IMG->buf[ ((Y) * IMG->width + (X)) ])

#endif
