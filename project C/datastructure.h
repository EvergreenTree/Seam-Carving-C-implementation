//
//  datastructure.h
//  project C
//
//  Created by Fu Changqing on 04/10/2017.
//  Copyright © 2017 Fu Changqing. All rights reserved.
//

#ifndef datastructure_h
#define datastructure_h


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

// define a bitree
typdef struct TNode {
    Item item;
    struct TNode *left;
    struct TNode *right;
} TNode;

typdef struct BiTree{
    TNode *root;
} Bitree

//define a skiplist
typedef struct SNode{
    Item item;
    struct SNode *right;
    struct SNode *down;
}SNode;

typedef struct Skiplist{
    SNode *head;
}Skiplist;



#endif /* datastructure_h */
