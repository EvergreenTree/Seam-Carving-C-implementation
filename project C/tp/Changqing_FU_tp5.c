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


//TP 5
//ex1
int is_int(char *s){
    int a,i;
    int flag=1;
    size_t n=strlen(s);
    if(n==0) return 0;
    for(i=0;i<n;i++){
        a=(int)(s[i]-'0');
        if(!(a>=0&&a<=9)) flag=0;
    }
    return flag;
}

//ex2
int inputsum(int argc, const char * argv[]){
    int s=0;
    int i;
    for(i=1;i<argc;i++){
        s+=atoi(argv[i]);
    }
    return s;
}

//ex3
int countlines(FILE *f){
    int count=0;
    char a;
    do {
        a=fgetc(f);
        if(a=='\n') count++;
    } while (a!=EOF);
    return count;
}
int maxlinesize(FILE *f);
void readline(FILE *f, char *s);
void readlines(FILE *f, char *s, char **t);

//ex4
int compare(const void* a, const void* b) {
    const char *ia = (const char *)a;
    const char *ib = (const char *)b;
    return strcmp(ia, ib);
}

int main(int argc, const char * argv[]){
    const char ** argsort;
    argsort= argv+1;
    qsort(argsort, argc, sizeof(argv[0]), compare);
    FILE *f=fopen("/Users/EvergreenFu/Documents/Xcode/project C/project C/File.txt","r");
    printf("%d\n",countlines(f));
    return 0;
}



