//
//  main.c
//  project C
//
//  Created by Fu Changqing on 27/09/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pixmap_io.h"
//#include "pixmap_io.c"//in Xcode ,I don't need to include this, strangely...

//Project

//unsigned char *load_pixmap(char *filename, int *width, int *height);
//void store_pixmap(char *filename, unsigned char *data, int width, int height);
//static unsigned char *alloc_pixmap(long size);

unsigned char * gradient_forward(unsigned char *data,int width,int height){
    int i,j;
    unsigned char *result = alloc_pixmap((long)width*(long)height);
    for(i = 0;i < height-1; i++)
        for(j = 0; j < width-1;j++)
            *(data+i*width+j) = (*(data+i*width+j)-*(data+i*width+j+1)) * (*(data+i*width+j)-*(data+i*width+j+1))+*(data+i*width+j)-*(data+i*width+j+1) * *(data+i*width+j)-*(data+i*width+j+1);
    return result;
}

int seam_carving(unsigned char *data,int width,int height,int newheight){
    
    return 0;
}



int main(int argc, const char * argv[]){
    unsigned char *data;
    int width, height;
    
    if( (argc > 1) && ((data = load_pixmap((char *)argv[1], &width, &height)) != NULL) ){
        printf("%c\n", *(data+100*width+100));
        printf("succeed");
        store_pixmap("/Users/EvergreenFu/Documents/Xcode/project C/project C/clone.pgm", data, width, height);
    }

    return 0;
}




