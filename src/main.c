//
//  main.c
//  Seam-Carving
//
//  Created by Fu Changqing on 21/11/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "/Users/EvergreenFu/GitHub/Seam-Carving/Seam-Carving/imglib.c"
#include "/Users/EvergreenFu/GitHub/Seam-Carving/Seam-Carving/seam_carving.c"



int main(int argc, const char **argv){

    char *open_name = "/Users/EvergreenFu/GitHub/Seam-Carving/Seam-Carving/pic/fu.ppm";

    // image t= read_image(open_name);
    
    image t = get_ppm(fopen(open_name,"r"));
    image t1 = t;


    t1=seam_carving(t1,10);

    char *save_name = "/Users/EvergreenFu/GitHub/Seam-Carving/Seam-Carving/pic/testbundle.ppm";

    output_ppm(fopen(save_name,"w"),t1);

    // unsigned i,j;
    // unsigned int X = t->width, Y = t->height;
    // for(i=1;i<Y;i++){
    //     for(j=1;j<X-1;j++){
    //         printf("%d ",t2->buf[j*X+i][1]);
    //     }
    //     printf("\n\n");
    // }

    return 0;
}

