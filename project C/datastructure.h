//
//  datastructure.h
//  project C
//
//  Created by Fu Changqing on 04/10/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#ifndef datastructure_h
#define datastructure_h

#endif /* datastructure_h */

// define bool
#if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)
typedef int bool;
#define true 1
#define false 0
#define __bool_true_false_are_defined
#endif

// item type (int here)
typedef int Item;

// define a node
typedef struct Node {
    Item item;				/** The data of this node. **/
    struct Node *next;		/** The next node (the one below the top). **/
} Node;

typedef struct Array{
    size_t count;//num of items (type size_t is very large, say 64 bit?)
    Node *head;//head of the array
} Array;

Array *array_init(void){
//initialize an array
    Array *array=(Array *)malloc(sizeof *array);
    if(array==NULL)
        return NULL;//failed to initialize..
    array->count = 0;
    array->head = NULL;//!!!!!!!!!!
    return array;
}

bool array_push(Array *array, Item item){
//push an item to the top
    Node *node = (Node *) malloc((sizeof *node));
    if(node == NULL) return false;
    
    node->item = item;
    node->next = array->head;
    
    array->head=node;
    array->count ++;
    return true;
}

Node *array_find(Array *array, size_t position){
//find the position of a certain node
    int i;
    Node *needle = array->head;
    for(i=0;i<position;i++){
        needle=needle->next;
    }
    return needle;
}

Item array_delete(Array *array,size_t n){
//delete the nth element (for head node, n=0)
    if(array->head==NULL){ //or array->count == 0
        printf("error: nothing to pop.\n");
        return -999;//question: how to return a better error message?
    }
    
    Item result;
    if(n>0){
    Node *needle = array_find(array, n-1);
    Node *newnext = needle->next->next;
    result = needle->next->item;
    
    free(needle->next);
    needle->next = newnext;
    }
    else{
        result = array->head->item;
        free(array->head);
        array->head = NULL;
    }
    array->count --;
    return result;
}

Item array_pop(Array *array){
    //pop the last node
    return array_delete(array, array->count-1);
}

bool array_isempty(Array *array){
    return array->head == NULL ? true : false;
}

void array_clean(Array *array){
    while(!array_isempty(array)){
        array_pop(array);
    }
}

void array_distroy(Array *array){
    array_clean(array);
    free(array);
}
//useful functions



//used in: void qsort(num_nodes, n, sizeof(Node), compar)


