//
//  file.c
//  project C
//
//  Created by Fu Changqing on 18/10/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <stdio.h>

int file(void){
    FILE* f = fopen("in", "r");//in Xcode, build path is at "/Build/Products/Debug"
    FILE* g = fopen("out", "w");
    int x;
    fscanf(f,"%d",&x);
    printf("%d",x);
    fprintf(g,"%d",x);
    //fprintf(g,"%s",x);
    fclose(f);fclose(g);
    //assert(a[1]-1);
    return 0;
}
