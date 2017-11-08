//
//  sort.c
//  project C
//
//  Created by Fu Changqing on 04/10/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//qsort in stdlib
typedef struct {
    int idx;
    int data;
} Node;
int compar(const void *p1, const void *p2) {
    if (((Node *)p1)->data < ((Node *)p2)->data) return -1;
    else if (((Node *)p1)->data > ((Node *)p2)->data) return 1;
    else return 0;
}
int qsortdemo(void){
    Node x[4];
    x[0].data = 3;
    x[1].data = 1;
    x[2].data = 5;
    x[3].data = 4;
    qsort(x, 4, sizeof(Node), compar);
    printf("%d %d %d %d\n",x[0].data,x[1].data,x[2].data,x[3].data);
    return 0;
}

//merge sort
void fusion(int t[], int i, int j, int k){
    assert((i<=j)&&(j<k));
    int aux[k+1];
    int p;
    for(p=i;p<=k;p++){aux[p]=t[p];}
    p=i;
    int q=j+1;
    int r=i;
    while (r<=k){
        if ((p<=j) && (aux[p]<=aux[q])){t[r]=aux[p];p++;r++; continue;}
        if ((q<=k) && (aux[p]>aux[q])) {t[r]=aux[q];q++;r++; continue;}
        if (p>j){t[r]=aux[q];q++;r++; continue;}
        if (q>k){t[r]=aux[p];p++;r++; continue;}
    }
}
void trifusion(int t[], int i, int j){
    assert(i<=j);
    if (i<j){
        int m=(i+j)/2;
        trifusion(t,i,m);
        trifusion(t,m+1,j);
        fusion(t,i,m,j);
    }
}

