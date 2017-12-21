//
//  seam_carving.c
//  Seam-Carving
//
//  Created by Fu Changqing on 21/11/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//
#include <math.h>

#include "imglib.h"
#include "seam_carving.h"

int max(int x, int y){return x > y ? x : y;}
int min(int x, int y){return x < y ? x : y;}

seam_bundle alloc_seam_bundle(unsigned int width, unsigned int height)
{
    seam_bundle s;
    s = malloc(sizeof(seam_bundle_t));
    s->buf = malloc(width*height*sizeof(seam));
    s->first_pixel = s->buf;//avoid memory leak
    s->last_pixel = s->buf+width*height-1; //for finding least energy
    s->width = width;
    s->height = height;
    s->width_actural = width;
    return s;
}

void free_seam_bundle(seam_bundle s){
    free(s->buf);
    free(s);
}

//to-be-optimized
grayimage enlarge(grayimage img, unsigned int edge){
    grayimage img_large = alloc_grayimg(img->width+2*edge,img->height+2*edge);
    int x,y;
    int targetx, targety;
    for(y=0;y<img->height+2*edge;y++){
        for (x=0; x<img->width+2*edge; x++) {
            targety=max(min(y-edge,img->height-1),0);
            targetx=max(min(x-edge,img->width-1),0);
            img_large->buf[y*img_large->width+x][0] = img->buf[targety*img->width+targetx][0];
        }
    }
    return img_large;
}

grayimage gradient(grayimage img){
    grayimage grad = alloc_grayimg(img->width,img->height);
    grayimage img_large = enlarge(img,1);
    
    int x,y;
    unsigned int X = img->width, Y = img->height;
    for(y=0;y<Y;y++){
        for (x=0; x<X; x++) {
            grad->buf[y*X+x][0] = abs(img_large->buf[(y+1)*(X+2)+x][0]-img_large->buf[(y+1)*(X+2)+x+2][0])
            +abs(img_large->buf[y*(X+2)+x+1][0]-img_large->buf[(y+2)*(X+2)+x+1][0]);
        }
    }
    free_grayimg(img_large);
    return grad;
}

grayimage gradient_filter(grayimage img, int wx[], int wy[]){//w is a 3*3 window
    grayimage grad = alloc_grayimg(img->width,img->height);
    grayimage img_large = enlarge(img,1);
    
    int x,y;
    unsigned int X = img->width+2, Y = img->height;
    for(y=0;y<Y;y++){
        for (x=0; x<X-2; x++) {
            grad->buf[y*(X-2)+x][0] = 
                                  abs(img_large->buf[y*X+x][0]*wx[0]     +img_large->buf[y*X+x+1][0]*wx[1]    +img_large->buf[y*X+x+2][0]*wx[2]
                                     +img_large->buf[(y+1)*X+x][0]*wx[3] +img_large->buf[(y+1)*X+x+1][0]*wx[4]+img_large->buf[(y+1)*X+x+2][0]*wx[5]
                                     +img_large->buf[(y+2)*X+x][0]*wx[6] +img_large->buf[(y+2)*X+x+1][0]*wx[7]+img_large->buf[(y+2)*X+x+2][0]*wx[8])
                                + abs(img_large->buf[y*X+x][0]*wy[0]     +img_large->buf[y*X+x+1][0]*wy[1]    +img_large->buf[y*X+x+2][0]*wy[2]
                                     +img_large->buf[(y+1)*X+x][0]*wy[3] +img_large->buf[(y+1)*X+x+1][0]*wy[4]+img_large->buf[(y+1)*X+x+2][0]*wy[5]
                                     +img_large->buf[(y+2)*X+x][0]*wy[6] +img_large->buf[(y+2)*X+x+1][0]*wy[7]+img_large->buf[(y+2)*X+x+2][0]*wy[8]);
        }
    }
    free_grayimg(img_large);
    return grad;
}

seam_bundle bundlize(image img, int filter){
    unsigned int width = img->width, height = img->height;
    seam_bundle s = alloc_seam_bundle(width,height);
    unsigned int i,y;

    grayimage gimg = tograyscale(img);
    grayimage grad;

    switch (filter){
    //1 for sobel, 2 for central, default for sentral (simple implementation)
    case 1:{
    int wx[9] = {1,0,-1,2,0,-2,1,0,-1};

    int wy[9] = {1,2,1,0,0,0,-1,-2,-1};
    grad = gradient_filter(gimg,wx,wy);
    };break;

    case 2: {
    int wx[9] = {0,0,0,1,0,-1,0,0,0};

    int wy[9] = {0,1,0,0,0,0,0,-1,0};
    grad = gradient_filter(gimg,wx,wy);
    }break;

    default:{
    grad = gradient(gimg);
    };break;
    }

    //assign reft, right, values
    s->buf[0].right = s->buf+1;
    s->buf[0].left = NULL;
    s->buf[width*height-1].left = s->buf+width*height-2;
    s->buf[width*height-1].right = NULL;
    for(i=1;i<width*height-1;i++){
        s->buf[i].right = s->buf+i+1;
        s->buf[i].left = s->buf+i-1;
    }
    for(i=0;i<width*height;i++){
        s->buf[i].col[0] = img->buf[i][0];
        s->buf[i].col[1] = img->buf[i][1];
        s->buf[i].col[2] = img->buf[i][2];
        s->buf[i].lum[0] = gimg->buf[i][0];
        s->buf[i].gra = (unsigned int) grad->buf[i][0];
    }
    //assign vertical values
    for(i = 0; i < width; i++){
        (s->buf+i)->last = NULL;
        (s->buf+i)->down = s->buf+width+i;
        for(y = 1; y < height-1; y ++){
            (s->buf+y*width+i)->last = s->buf+(y-1)*width+i;
            (s->buf+y*width+i)->down = s->buf+(y+1)*width+i;
        }
        (s->buf+(height-1)*width+i)->down = NULL;
        (s->buf+(height-1)*width+i)->last = s->buf+(height-2)*width+i;
    }
    //assign first row of energy
    for(i=0;i<width;i++){
        (s->buf+i)->energy = (unsigned int) s->buf[i].gra;
        (s->buf+i)->lastseam = NULL;
    }
    free_grayimg(grad);
    return s;
}

image debundlize_color(seam_bundle s){
    image img = alloc_img(s->width_actural, s->height);
    unsigned int i=0;
    seam * p = s->first_pixel;
    while(p->right!=NULL){
        img->buf[i][0] = p->col[0];
        img->buf[i][1] = p->col[1];
        img->buf[i++][2] = p->col[2];
        p = p->right;
    }

    return img;
}
grayimage debundlize_gray(seam_bundle s){
    grayimage img = alloc_grayimg(s->width_actural, s->height);
    unsigned int i=0;
    seam * p = s->first_pixel;
    while(p->right!=NULL){
        img->buf[i++][0] = p->lum[0];
        p = p->right;
    }
    return img;
}
grayimage debundlize_gradient(seam_bundle s){
    grayimage img = alloc_grayimg(s->width_actural, s->height);
    unsigned int i=0;
    seam * p = s->first_pixel;
    while(p->right!=NULL){
        img->buf[i++][0] = (luminance)p->gra;
        p = p->right;
    }
    return img;
}
grayimage debundlize_gradient_full(seam_bundle s){
    grayimage img = alloc_grayimg(s->width, s->height);
    unsigned int i=0;
    while(i < s->width * s->height - 1){
        img->buf[i][0] = (luminance)(s->buf+i)->gra;
        i++;
    }
    return img;
}
grayimage debundlize_energy(seam_bundle s,double rate){
    grayimage img = alloc_grayimg(s->width_actural, s->height);
    unsigned int i=0;
    seam * p = s->first_pixel;
    while(p->right!=NULL){
        img->buf[i++][0] = (luminance) ((p->energy)/rate);
        p = p->right;
    }
    return img;
}

// short which_min(unsigned a,unsigned b,unsigned c){
//     if(a < b){
//         if(c < a) return 1;
//         else return -1;
//     }
//     else{
//         if(c < b) return 1;
//         else return 0;
//     }
// }

// short which_min_t(seam *a,seam *b,seam *c){
//     if(a->energy<b->energy){
//         if(c->energy<a->energy) return 1;
//         else return -1;
//     }
//     else{
//         if(c->energy<b->energy) return 1;
//         else return 0;
//     }
// }

seam *which_min_p(seam *a,seam *b,seam *c){
    if(a->energy<b->energy){
        if(c->energy<a->energy) return c;
        else return a;
    }
    else{
        if(c->energy<b->energy) return c;
        else return b;
    }
}
seam *which_min_b(seam *a,seam *b){
    if(a->energy<b->energy){
        return a;
    }
    else{
        return b;
    }
}

// seam *last_seam(seam *p){
//     if(p->seam_direction==-1)return p->last->left;
//     if(p->seam_direction==0)return p->last;
//     if(p->seam_direction==1)return p->last->right;
//     return NULL;
// }

seam *find_seam(seam_bundle s){
    unsigned int X = s->width_actural;
    seam *p = s->last_pixel, *ret = p;
    unsigned i;

    for(i = 0;i < X; i++){
        if(ret->energy > p->energy)
            ret = p;
        p = p->left;
    }
    return ret;
}

void compute_energy(seam_bundle s){
    unsigned int x,y;
    unsigned int X = s->width_actural, Y = s->height;
    seam *p = s->first_pixel,*q = s->first_pixel;
    for(y=1;y<Y;y++){
        q = q->down;
        p = q;
        //left margin
        p->lastseam = which_min_b(p->last,p->last->right);
        p->energy=p->lastseam->energy+p->gra;
        // printf("left margin position:(%ld,%ld)\n",(p - s->buf) % s->width ,(long)((p - s->buf)/s->width));
        // printf("last seam position:(%ld,%ld)\n",(p->lastseam - s->buf) % s->width ,(long)((p->lastseam - s->buf)/s->width));
        p=p->right;

        for(x=1;x<X-1;x++){
            p->lastseam = which_min_p(p->last->left,p->last,p->last->right);
            p->energy=p->lastseam->energy+p->gra;
            p=p->right;
        }
        //right margin
        p->lastseam = which_min_b(p->last,p->last->left);
        p->energy=p->lastseam->energy+p->gra;
        p=p->right;
    }
}



///
void show_seam(seam_bundle s){
    seam *p = find_seam(s);
    while(1){
        p->gra = (luminance) 255;
        // printf("marking: (%ld,%ld)\n",(p - s->buf) % s->width ,(long)((p - s->buf)/s->width));
        if(p->lastseam==NULL) break;
        p=p->lastseam;
    }
}

void delete_seam(seam_bundle s){
    // unsigned int X = s->width;
    s->width_actural --;

    // int i=0;
    seam *p = find_seam(s);
    // printf(">>found seam at position: %ld\n",(p - s->buf) % X);

    while(1){
        //avoid margins
        // if((p - s->buf) % X == 0)p = p->right;
        // if((p - s->buf) % X == X-1)p = p->left;
        // printf("deleting: (%ld,%ld)\n",(p - s->buf) % X ,(long)((p - s->buf)/X));
        if(p->left!=NULL){
            p->left->right = p->right;
        }
        else{
            // printf("moving first pixel to the right");
            s->first_pixel = s->first_pixel->right;//the very first pixel of the image (avoid leaking)
        }
        if(p->right!=NULL){
            p->right->left = p->left;
        }
        else{
            s->last_pixel = s->last_pixel->left;//the very last pixel of the image
        }
        if(p->last==NULL) {
            // printf("first pixel: %ld, last pixel: %ld)\n",(s->first_pixel - s->buf) % X ,(long)((s->last_pixel - s->buf) % X));
            break;
        }

        if(p->lastseam == p->last->right) {p->right->last = p->last; p->last->down = p->right;}
        if(p->lastseam == p->last->left) {p->left->last = p->last; p->last->down = p->left;}
        // // printf("seam direction: %d\n",p->seam_direction);
        // if(p->seam_direction == 0){//case mid
        //     // printf("left: %d right: %d\n",p->left->seam_direction,p->right->seam_direction);
        //     p->left->seam_direction = which_min_t(p->left->last->left,p->left->last,p->last->right);
        //     p->right->seam_direction = which_min_t(p->last->left,p->right->last,p->right->last->right);
        //     // printf("new left: %d new right: %d\n",p->left->seam_direction,p->right->seam_direction);
        // }
        // if(p->seam_direction == -1){//case left
        //     // printf("left: %d right: %d\n",p->left->seam_direction,p->right->seam_direction);
        //     p->left->last = p->last;
        //     p->left->seam_direction = which_min_t(p->left->last->left,p->last,p->last->right);
        //     // printf("new left: %d new right: %d\n",p->left->seam_direction,p->right->seam_direction);
        // }
        // if(p->seam_direction == 1){//case right
        //     // printf("left: %d right: %d\n",p->left->seam_direction,p->right->seam_direction);
        //     p->right->last = p->last;
        //     p->right->seam_direction = which_min_t(p->last->left,p->last,p->right->last->right);
        //     // printf("new left: %d new right: %d\n",p->left->seam_direction,p->right->seam_direction);
        // }
        p = p->lastseam;
    }
}


image seam_carving(image img, unsigned int target_width){
    printf("building structure\n");

    int filter = 0;//1 = "sobel", 2 = "center"

    seam_bundle s = bundlize(img,filter);

    unsigned k;

    for(k=0;k < target_width;k++){
        printf("========\nOperating Seam %u\n",k+1);
        printf("compute energy\n");
        compute_energy(s);
        show_seam(s);

        printf("deleting seam\n");
            delete_seam(s);
    }
    // printf("========\nOperating Seam %u\n",k+1);
    // printf("compute energy\n");
    // compute_energy(s);

    // free(rank);

    //show seam
    // printf("seam position %ld\n",find_seam(s)-s->last_pixel+s->width-1);
    // show_seam(s);
    // image newimg = tocolor(debundlize_gradient(s));

    // show energy
    // image newimg = tocolor(debundlize_energy(s,13));

    // show gradient
    // image newimg = tocolor(debundlize_gradient(s));
    image newimg = tocolor(debundlize_gradient_full(s));

    //show image
    // image newimg = debundlize_color(s);
    // printf("new width: %u\n",newimg->width);

    // enlarge
    // image newimg = tocolor(enlarge(tograyscale(img),(unsigned)1));



    free_seam_bundle(s);

    //printf("new img:%u\n",newimg->buf[1000][2]);

    return newimg;
}




