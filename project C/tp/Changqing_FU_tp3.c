//  paper sissors stone
//
//  main.c
//  project C
//
//  Created by Fu Changqing on 27/09/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "datastructure.h"
//#include "matrix.h"

#ifndef N
#define N 3 //mat dimension
#endif
#define MAX 100


void initmat3(int a[3][3][3]){
    int i,j,k;
    for(k=0;k<N;k++){
        for(j=0;j<N;j++){
            for(i=0;i<N;i++){
                a[i][j][k]=0;
            }
        }
    }
}

void printmat3(int a[N][N][N]){
    int i,j,k;
    for(k=0;k<N;k++){
        for(j=0;j<N;j++){
            for(i=0;i<N;i++){
                printf("a(%d,%d,%d)=%d\n",k,j,i,a[k][j][i]);
            }
        }
    }
}

void printmax3(int a[N][N][N],int i,int j){//print the maximal(s) of a[i][j][*]
    int k = 0;
    int max = 0;
    for(;k<N;k++){
        if(max<a[i][j][k]) max=a[i][j][k];
    }
    for(k=0;k<N;k++){
        if(max==a[i][j][k]) printf("next step, I guess you may play %d\n",k);
    }
}
//
//void printmat2(int a[N][N]){
//    int i,j;
//    for(j=0;j<N;j++){
//        for(i=0;i<N;i++){
//            printf("%d ",a[j][i]);
//        }
//        printf("\n");
//    }
//
//}

int predict_3(){
    int t[N][N][N];
    initmat3(t);
    printf("Please input string:(must be 0, 1, 2 without spaces, up to %d digits)\n",MAX);
    //printmat3(t);
    
    char string[MAX];
    scanf("%s",string);
    
    printf("Your input: %s\n",string);
    //int x = getchar();
    size_t n = strlen(string);
    if(n<3) return 1;//input too short
    int i,a,b,c;
    
    a=(int)string[0]-'0';b=(int)string[1]-'0';
    for(i=2;i<n;++i){
        c = string[i]-'0';
        if((c*(c-1)*(c-2))) return 2;//invalid input
        //printf("%d %d %d\n",a,b,c);
        ++t[a][b][c];
        a=b;b=c;
    }
    //printmat3(t);
    printmax3(t,a,b);
    return 0;
}

int predict_k(void){
    int result[3]={0,0,0};
    int i,j,k;
    printf("Please input prediction steps k:(small number recommended)\n");
    scanf("%d",&k);
    k--;//key length
    printf("Please input string:(must be 0, 1, 2 without spaces, up to %d digits)\n",MAX);
    char string[MAX];
    scanf("%s",string);
    size_t n=strlen(string);
    if(n<k+1) return 1;//input too short
    for(i=0;i<n;i++){
        if((string[i]-'0')*(string[i]-'1')*(string[i]-'2')) return 2;//invalid input
    }
    
    char *key=&string[n-k];
    
    //the following may be optimized by KMP Algorithm, building a match table for the key
    for(i=0;i<n-k-1;i++){
        j=0;
        while(string[i+j]==key[j]){
            if(j==k-1){//found key
                //printf("found position%d\n",i);
                int prediction = string[i+j+1]-'0';
                result[prediction]++;
            }
            j++;
        }
    }
    int max=0;
    for(i=0;i<3;i++){
        max<result[i]?max=result[i]:0;
    }
    for(i=0;i<3;i++){
        max==result[i]?printf("next step, I guess you may play %d\n",i):0;
    }
    return 0;
}


int main(int argc, const char * argv[]){
    int output=0;
    int mode=0;
    
    printf("Please specify the mode: \n1 = 3-step prediction (implemented with an array of dimension 3), \n2 = arbitrary-step prediction (KMP Algorithm).\n");
    scanf("%d",&mode);
    
    switch(mode){
        case 1: output = predict_3();break;
        case 2: output = predict_k();break;
        default: output = 3;//wrong mode
    }
    return output;
}

//return values: 0 = success, 1 = input too short, 2 = input invalid, 3 = mode invalid

