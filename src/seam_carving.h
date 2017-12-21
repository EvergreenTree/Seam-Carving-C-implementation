//
//  seam_carving.h
//  Seam-Carving
//
//  Created by Fu Changqing on 21/11/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#ifndef seam_carving_h
#define seam_carving_h

#include "imglib.h"
#include <stdio.h>
#include <limits.h>

#define NO_LAST 10

grayimage gradient(grayimage);

typedef struct seam{
	struct seam *left;
	struct seam *right;
	struct seam *last; 
	struct seam *down;
	//short seam_direction;//previously used long int, (could be smaller, e.g. int, but since width uses long...
	struct seam *lastseam; 

	pixel1 lum;
	pixel col;
	unsigned int gra;
	unsigned int energy;
} seam;////a little question: duplicate name works
typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int width_actural;
	seam *buf;//points to a pointer seam
	seam *first_pixel;
	seam *last_pixel;
} seam_bundle_t;
typedef seam_bundle_t * seam_bundle;



#endif /* seam_carving_h */
