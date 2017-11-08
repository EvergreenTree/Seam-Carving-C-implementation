//
//  main.c
//  project C
//
//  Created by Fu Changqing on 27/09/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#include <stdio.h>
#include <assert.h>

ppn

//TP4 1
int max(int a, int b){
    return (a < b ? b : a);
}
int kadane(int t[],int n){//maximal continious sum
    int max_ending_here = t[0],max_so_far = t[0];
    int i;
    for (i = 1; i < n; i++){
        max_ending_here = max(t[i],max_ending_here + t[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

//TP4 2
int evalue(int x, int a[],int deg){
    //int deg = sizeof(a) / sizeof(a[0]);//this is WRONG!!! when "a" is a variable of the function, sizeof(a) returns size of adress (which is 8 here)
    //printf("%d\n",deg);
    int i;
    int ret = a[deg];
    for(i = deg; i>=0; i --){
        ret = x * ret + a[i];
    }
    return ret;
}
/*
 usage:
 int a[3] = {1,2,3}; //3*x^2+2*x+1
 int n = sizeof(a)/sizeof(a[0])-1;
 printf("%d\n",evalue(2,a,n));
*/
void derive(int p[],int deg, int retour[]){//size of p - size of retour = 1
    int i = 0;
    for (i=0;i<deg-1;i++){
        retour[i]=p[i+1]*i;
    }
}
/*
 usage:
 int a[3]={1,2,3};
 int da[2];
 derive(a,3,da);
*/
void switchtable(void *p, void *q){
    r = p; p = q; q = r;
}
void somme(int p[], int degrep, int q[], int degreq, int retour[]){
    int i;
    if(degrep < degreq) {
        switchtable(p,q); t=degrep;degrep=degreq;degreq=t;
    }
    for(i=0;i<degrep;i++){
        retour[i] = p[i]+q[i];
    }
    for(i=degrep;i<degreq;i++){
        retour[i]=p[i];
    }
}

//TP 4 3(Merge Sort)
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
        if (q>k){t[r]=aux[p];p++;r++; continue;}}}
void trifusion(int t[], int i, int j){
    assert(i<=j);
    if (i<j){
        int m=(i+j)/2;
        trifusion(t,i,m);
        trifusion(t,m+1,j);
        fusion(t,i,m,j);}}


//int main(int argc, const char * argv[]){
//    int a[3] = {1,1,1};
//    int n = sizeof(a)/sizeof(a[0])-1;
//    printf("%d\n",evalue(2,a,n));
//    //assert(a[1]-1);
//    return 0;
//    
//}
//
//

