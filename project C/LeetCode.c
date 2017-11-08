#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Brute Force */
//int* twoSum(int* nums, int numsSize, int target) {
//    int i,j;
//    int *result = (int*)malloc(2*sizeof(*result));
//    result[1] = 0;result[2]=0;
//    for(i=0;i<numsSize;i++){
//        for(j=i+1;j<numsSize;j++){
//            if(nums[i]+nums[j]==target){
//                result[0]=i;result[1]=j;
//            }
//        }
//    }
//    return result;
//}

int compare(const void *a,const void *b){
    int x = *(int*)a-*(int*)b;
    if(x>0) return 1;
    else if(x<0) return -1;
    else return 0;
}

/* qsort */
typedef struct {
    int idx;
    int data;
} Node;

int compar(const void *p1, const void *p2) {
    if (((Node *)p1)->data < ((Node *)p2)->data) return -1;
    else if (((Node *)p1)->data > ((Node *)p2)->data) return 1;
    else return 0;
}

int *twoSum_qsort(int numbers[], int n, int target) {
    int i, j;
    static int ret[2] = { 0, 0 };
    Node *num_nodes = (Node *)calloc(n, sizeof(Node));
    
    
    for (i = 0; i < n; i++) {
        num_nodes[i].idx = i + 1;
        num_nodes[i].data = numbers[i];
    }
    
    qsort(num_nodes, n, sizeof(Node), compar);
    
    i = 0, j = n - 1;
    while (i < n && j >= 0) {
        if (num_nodes[i].data + num_nodes[j].data == target) {
            ret[0] = num_nodes[i].idx;
            ret[1] = num_nodes[j].idx;
            if (ret[0] > ret[1]) {
                int t = ret[1];
                ret[1] = ret[0];
                ret[0] = t;
            }
            return ret;
        }
        else if (num_nodes[i].data + num_nodes[j].data < target){
            i++;
        }
        else {
            j--;
        }
    }
    
    return ret;
}

/* hash table */
typedef struct HashNode {
    int val;
    int key;
    struct HashNode * next;
} HashNode;

static inline int hash (int val, int n) {
    int index = val % n;
    return (index > 0) ? (index) : (-index);
}

int *twoSum(int numbers[], int n, int target) {
    static int ret[2] = { 0, 0 };
    int i;
    
    HashNode **hashtable = (HashNode **)calloc(n, sizeof(HashNode *));
    
    int idx;
    HashNode *p, *tail;
    for (i = 0; i < n; i++) {
        idx = hash(numbers[i], n);
        //get tail
        p = hashtable[idx];
        tail = NULL;
        while (p != NULL) {
            tail = p;
            p = p->next;
        }
        HashNode *new_node = (HashNode *)calloc(1, sizeof(HashNode));
        new_node->val = numbers[i];
        new_node->key = i;
        new_node->next = NULL;
        
        if (tail) {
            tail->next = new_node;
        }
        else {
            hashtable[idx] = new_node;
        }
    }
    
    for (i = 0; i < n; i++) {
        int diff = target - numbers[i];
        idx = hash(diff, n);
        p = hashtable[idx];
        while (p != NULL) {
            if (p->val == diff && p->key != i) {
                ret[0] = p->key + 1;
                ret[1] = i + 1;
                // swap value
                if (ret[0] > ret[1]) {
                    ret[0] = ret[0] ^ ret[1];
                    ret[1] = ret[0] ^ ret[1];
                    ret[0] = ret[0] ^ ret[1];
                }
                return ret;
            }
            p = p->next;
        }
    }
    
    return ret;
}

//int main() {
//    int numbers[] = {2,4,1,5};
//    
//    
//    int target = 9;
//    
//    int *index = twoSum(numbers, sizeof(numbers) / sizeof(numbers[0]), target);
//    
//    qsort(numbers,4,sizeof(int),compare);
//    
//    printf("%d %d %d %d\n",numbers[0],numbers[1],numbers[2],numbers[3]);
//    
//    int i;
//    for (i = 0; i < 2; i++){
//        printf("index%d = %d ", i + 1, index[i]);
//    }
//    printf("\n");
//    
//    return 0;
//}

