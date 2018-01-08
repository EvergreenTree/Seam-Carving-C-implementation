//
//  main.c
//  Seam-Carving
//
//  Created by Fu Changqing on 21/11/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#include <Python.h>

#include "imglib.c"
#include "seam_carving.c"

int main(int argc, const char **argv){

    char *open_name = "../pic/lena.ppm";
    
    // image t= read_image(open_name); // aribitrary format. this doesn't work because of a error by ImageMagick
    
    char *filter = "Sobel";//"Sobel", "Central", "Prewitt"; default = "Central"

    image t = get_ppm(fopen(open_name,"r"));

    // transpose(t);

    // image t1=seam_carving(t,50,filter);
    image t1=seam_carving_showseam(t,3,filter);

    // transpose(t1);

    char *save_name = "../pic/output.ppm";

    output_ppm(fopen(save_name,"w"),t1);


    return 0;
}

