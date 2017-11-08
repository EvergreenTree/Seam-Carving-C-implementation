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


//TP 6
//ex1
int is_int(char *s){
    int a,i;
    int flag=1;
    size_t n=strlen(s);
    if(n==0) return 0;
    for(i=0;i<n;i++){
        a=(int)(s[0]-'0');
        if(!(a>=0&&a<=9)) flag=0;
    }
    return flag;
}


