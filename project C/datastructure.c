
#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include <assert.h>

//operations
Array *array_init(void){
    //initialize an array
    Array *array=(Array *)malloc(sizeof(Array *));
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

Node *array_search(Array *array, Item x){
    Node *needle = array->head;
    while(needle!=NULL){
        if(needle->item==x)
            return needle;
    }
    return NULL;
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

//void skiplist_insert(Skiplist s,Item x){
//    SNode *new = malloc(sizeof(SNode));
//    new->Item = x;
//    SNode *p = s->
//}

Bitree *bitree_init(void){
    //initialize a bitree
    Bitree *t =malloc(sizeof(Bitree *));
    t->root = NULL;
    return t;
}//empty tree

bool bitree_insert(Bitree *t, Item x){
    TNode *tnode=malloc(sizeof(TNode *));
    assert(tnode!=NULL);
    tnode->left = NULL;//!!!!!!!!!!
    tnode->right = NULL;//!!!!!!!!!!
    tnode->item=x;
    TNode *needle = t->root;
    if(needle==NULL) t->root = tnode;
    while(1){
        if(needle->item > x){
            if(needle->left == NULL) {needle->left = tnode; break;}
            else needle = needle->left;
        }
        else {
            if(needle->right == NULL) {needle->right = tnode; break;}
            else needle = needle->right;
        }
    }
    return 0;
}

Bitree *array2tree(Array *array){
    Bitree *bitree = bitree_init();
    Node *needle;
    for(needle = array->head;needle->next!=NULL;needle = needle->next){
        bitree_insert(bitree, needle->item);
    }
}

void print_node(TNode *n){
    print_node(n->left);
    printf("%d ",n->item);
    print_node(n->right);
}

void bitree_print(Bitree *t){
    print_node(t->root);
}

TNode *bitree_search(Bitree *t, Item x){
    TNode *needle = t->root;
    if(needle==NULL)return NULL;
    while(1){
        if(needle->item==x) return needle;
        if(needle->item>x) needle = needle->left;
        else needle = needle->right;
    }
    return NULL;
}

