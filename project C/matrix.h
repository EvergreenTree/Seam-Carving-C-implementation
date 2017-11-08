//
//  matrix.h
//  project C
//
//  Created by Fu Changqing on 04/10/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#ifndef matrix_h
#define matrix_h
#endif /* matrix_h */
#ifndef N
#define N 3 //mat dimension
#endif

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

void predict(int a[N][N][N],int i,int j){
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
