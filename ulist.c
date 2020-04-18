#include <stdlib.h>
#include <stdio.h>
#include "ulist.h"

int print_node(ULNode* node, int all)
{
    printf("%p: ", node);
    if(node){
        printf("front[%d] back[%d] max[%d] ", 
            node->front, node->back, node->max);
        printf("arr[ ");
        int beg = (all ? 0 : node->front + 1);
        int end = (all ? node->max : node->back);
        for(int i = beg; i < end; i++){
            if(all && (i <= node->front || node->back <= i)){
                printf("_ ");
            }else{
                printf("%d ", node->items[i]);
            }
        }
        printf("] next:%p \n", node->next);
    }
    return SUCCESS;
}

int print_list(ULNode* lst, int all)
{
    ULNode* cursor = lst;
    while(cursor){
        print_node(cursor, all);
        cursor = cursor->next;
    }
}

int init_list(ULNode** lst, int node_size)
{
    return new_node(lst, node_size, NULL);
}

int is_empty(ULNode* lst)
{
    return (lst == NULL) || (
        lst->next == NULL && 
        lst->back - 1 == lst->front 
    );
}

static int has_space(ULNode* prev, ULNode* node, int idx)
{
}

int insert(ULNode** lst, int pos, Item item)
{
    if(pos == 0){
        if(full_front(*lst)){
            ULNode* old_head = *lst;
            new_node(lst, old_head->max, old_head);
            return add_front(*lst, item);
        }else{
            return add_front(*lst, item);
        }
    }
    else if(pos == -1){
        ULNode* tail = *lst;
        while(tail->next){ tail = tail->next; }

        if(tail->back == tail->max){
            ULNode* new_tail;
            new_node(&new_tail, tail->max, NULL);
            tail->next = new_tail;
            return add_back(new_tail, item);
        }else{
            return add_back(tail, item);
        }
    }
    else if(pos > 0){
        // if empty slot
        ULNode* prev; ULNode* node; int idx;
        decode_pos((*lst), pos, &prev, &node, &idx);
        print_node(prev, TRUE);print_node(node, TRUE);
        // else
    }
    else{
        puts("Doesn't support negative pos (except -1)");
        return FAILURE;
    }

    // TODO: if pos is not 0 nor -1?
}

int remove(ULNode** lst, int pos, Item* removed)
{
    if(is_empty(*lst)){
        return FAILURE;
    }

    if(pos == 0){
        if(removed){
            *removed = (*lst)->items[(*lst)->front + 1];
        }

        int num_elem = num_items(*lst);
        if(num_elem > 1){
            (*lst)->front += 1;
        }else if(num_elem == 1){
            ULNode* next_node = (*lst)->next;
            free(*lst);
            *lst = next_node;
        }else{
            print_list(*lst, TRUE);
            printf("We can't remove from empty node. FATAL ERROR");
            exit(EXIT_FAILURE);
        }
    }
    else if(pos == -1){
        ULNode* prev = NULL;
        ULNode* tail = *lst;
        while(tail->next){ 
            prev = tail;
            tail = tail->next; 
        }

        if(removed){
            *removed = tail->items[tail->back - 1];
        }

        int num_elem = num_items(tail);
        if(num_elem > 1){
            tail->back -= 1;
        }else if(num_elem == 1){
            free(tail);
            if(prev){ 
                prev->next = NULL; 
            }else{
                *lst = NULL; // empty list
            }
        }else{
            print_list(*lst, TRUE);
            printf("We can't remove from empty node. FATAL ERROR");
            exit(EXIT_FAILURE);
        }
    }
    else if(pos > 0){
    }
    else{
        puts("Doesn't support negative pos (except -1)");
        return FAILURE;
    }

    return SUCCESS;
}

int decode_pos(ULNode* lst, int pos, 
    ULNode** ret_prev, ULNode** ret_node, int* ret_idx)
{
    // NOTE: pos is index, begin from 0!
    if(pos < 0){
        return FAILURE;
    }

    int idx = 0;
    ULNode* prev = NULL;
    ULNode* node = lst;
    while(pos != 0 && node != NULL){
        int num_elem = num_items(node);
        int chk = pos - num_elem;
        if(chk >= 0){
            prev = node;
            node = node->next;
            pos = chk; // = 0 then break
        }else{
            idx = pos;
            pos = 0;
        }
    }

    if(ret_prev){ *ret_prev = prev; }
    if(ret_node){ *ret_node = node; }
    if(ret_idx) { *ret_idx = idx;   }
    return (node && num_items(node)) ? SUCCESS : FAILURE;
}

int get(ULNode* lst, int pos, Item* accessed)
{

    ULNode* node = NULL; int idx; 
    int chk = decode_pos(lst, pos, NULL, &node, &idx);
    if(chk == FAILURE){
        return FAILURE;
    }

    *accessed = node->items[idx + node->front + 1];
    return SUCCESS;
}

// return value is number of nodes
int get_tail(ULNode* lst, ULNode* tail)
{
    int num_nodes = 0;
    if(lst){
        tail = lst;
        while(tail->next){
            tail = tail->next;
            num_nodes++;
        }
    }
    return num_nodes;
}

static int new_node(ULNode** pnode, int max, ULNode* next)
{
    *pnode = (ULNode*)malloc(
        sizeof(ULNode) + sizeof(Item) * max);
    int mid = max / 2;
    (*pnode)->front = mid - 1;
    (*pnode)->back = mid;
    (*pnode)->max = max;
    (*pnode)->next = next;
    return SUCCESS;
}

static int add_back(ULNode* node, Item item)
{
    if(node->back < node->max){
        node->items[node->back++] = item;
        return SUCCESS;
    }
    // check items overflow
    return FAILURE;
}

static int add_front(ULNode* node, Item item)
{
    if(node->max == 1){
        // If node size = 1, can't insert to front.
        // Because front is always -1 when node size = 1.
        return add_back(node, item);
    }

    if(-1 < node->front){
        node->items[node->front--] = item;
        return SUCCESS;
    }
    // check items overflow
    return FAILURE;
}

static int num_items(ULNode* node)
{
    return node->back - node->front - 1;
}

static int full_front(ULNode* node)
{
    return node->max == 1 ? 
        num_items(node) == 1 : 
        node->front == -1;
}
