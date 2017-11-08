//  Rabin-miller
//
//  main.c
//  project C
//
//  Created by Fu Changqing on 27/09/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//
#include <stdio.h>
//#include <math.h>
#include <limits.h>

#define LEN_A 5

typedef unsigned long long intL;

int isPair(intL n){
    if(n&1) return 0;
    return 1;
}

intL puissance(intL x,intL a){
    intL i;
    intL s=x;
    for(i=1;i<a;i++) s=s*x;
    return s;
}
intL puissance_rapide(intL x,intL a){
    if(a==0) return 1;
    if(a==1) return x;
    if(a&1)
        return x*puissance_rapide(x,a-1);
    else
        return puissance(puissance_rapide(x,a/2),2);
}

intL puissance_rapide_mod(intL a, intL b, intL n){
    //fast power mod by formula a^b mod n = (a mod n)^b mod n
    intL ans = 1;
    a = a % n;
    while(b>0) {
        if(b&1){
            ans = (ans * a) % n;
        }
        b>>=1;
        a = (a * a) % n;
    }
    return ans;
}

int rabinmiller(intL n){
    if(isPair(n)) return 0;
    //decompose n=2^s*d
    intL d=n-1;
    int s = 0;
    do{
        d=d/2;
        s++;
    }
    while(isPair(d));
    //printf("s = %d d = %llu\n",s,d);
    
    //loop s time: compute x for some a values
    intL res=0;
    intL a[LEN_A]={(intL)2,(intL)3,(intL)5,(intL)7,(intL)11};
    int i,r,flag;
    for(i=0;i<LEN_A;i++){
        //printf("a = %llu\n",a[i]);
        flag=0;
        for(r=0;r<s;r++){
            //printf("r = %d d = %llu\n",r,d);
            res=puissance_rapide_mod(a[i],puissance(2,r)*d,n);
            //printf("res = %llu \n", res);
            if(res==1||res==n-1) {flag=1;break;}
        }
        //printf("flag = %d\n",flag);
        if(flag==0) return 0;
    }
    return 1;
}


//main.c:
//#include <stdio.h>
//#include "Changqing_FU_tp2.h"
//
//int main(int argc, const char * argv[]) {
//    printf("/*warning: max value (unsigned long long) in the computing process is: %llu; the biggest tested prime number is 999999937 (actual bound not computed, but all 9-digit numbers passed)*/\n\n", ULLONG_MAX);
//    
//    printf("please enter a odd number greater than 10:\n");
//    intL x;
//    scanf("%llu",&x);
//    printf("(%llu is prime) = %d\n",x,rabinmiller(x));
//    //    for (i=999990001;i<=999999999;i+=2){
//    //        if(isPrime(i))
//    //            printf("%llu\n",i);
//    //    }
//    return 0;
//}
