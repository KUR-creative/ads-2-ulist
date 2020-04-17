#ifndef _ULIST_H_
#define _ULIST_H_

#define TRUE    (1==1)
#define FALSE   (!TRUE)

#define SUCCESS (0)
#define FAILURE (1)
#define NONE    (-1)

typedef int Item;
#define NONE_ITEM NONE

// singly linked list
typedef struct ULNode {
    int top; // 
    int max;
    struct ULNode* next;
    Item items[1]; 
} ULNode;

int init_list(ULNode** lst, int node_size);
int insert(ULNode** lst, int pos, Item item);
int remove(ULNode** lst, int pos, Item* removed);

int is_empty(ULNode* lst);
int get(ULNode* lst, int pos, Item* accessed);
int print_node(ULNode* node);
int print_list(ULNode* lst);

#endif //_ULIST_H_
