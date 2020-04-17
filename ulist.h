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
    int front;
    int back; // 
    int max;
    struct ULNode* next;
    Item items[1]; 
    // items [_ _ a b d e _ _ _]
    //          ^         ^     ^
    //        front      back  max
} ULNode;

int init_list(ULNode** lst, int node_size);
int insert(ULNode** lst, int pos, Item item);
int remove(ULNode** lst, int pos, Item* removed);

int is_empty(ULNode* lst);
int get(ULNode* lst, int pos, Item* accessed);
int print_node(ULNode* node, int all);
int print_list(ULNode* lst, int all);

static int new_node(ULNode** pnode, int max, ULNode* next);
static int add_back(ULNode* node, Item item);
static int add_front(ULNode* node, Item item);

#endif //_ULIST_H_
