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


#define N 10
static int a[N];
static int occupied[N];

int i;
for(i = 0;i < N;i++) occupied[i]=0;

void f(int n, int e[n][n], int t[n][n]){
    int i,j ;int max = n;
    
    for(i = 0; i < n;i++){
        for(j=1;j<n;j++){
            if(max > e[i][j] && !occupied[j]) max = e[i][j];occupied[j]=1;
        }
        a[i]=max;
    }
    //check a[j]
}



