#include <stdlib.h>
#include <stdio.h>
#include "ulist.h"

int print_node(ULNode* node, int all)
{
    printf("%p: ", node);
    printf("front[%d] back[%d] max[%d] ", 
        node->front, node->back, node-> max);
    printf("arr[ ");
    int beg = (all ? 0 : node->front + 1);
    for(int i = beg; i < node->back; i++){
        if(all && i <= node->front){
            printf("x ");
        }else{
            printf("%d ", node->items[i]);
        }
    }
    printf("] next:%p \n", node->next);
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
    return (
        lst->next == NULL && 
        lst->back - 1 == lst->front 
    );
}

int insert(ULNode** lst, int pos, Item item)
{
    //print_node(*lst, TRUE);
    if(pos == 0){
        ULNode* tmp = *lst;
        new_node(lst, tmp->max, tmp);
        return add_front(*lst, item);
    }
    else if(pos == -1){
        ULNode* tail = *lst;
        while(tail->next){
            tail = tail->next;
        }

        if(tail->back == tail->max){
            ULNode* new_tail;
            new_node(&new_tail, tail->max, NULL);
            tail->next = new_tail;
            return add_back(new_tail, item);
        }else{
            return add_back(tail, item);
        }
    }

    // TODO: if pos is not 0 nor -1?
}

int remove(ULNode** lst, int pos, Item* removed)
{
    if(is_empty(*lst)){
        return FAILURE;
    }

    if(pos == 0){
        (*lst)->front += 1;
    }
    else if(pos == -1){
    }
    return SUCCESS;
}

int get(ULNode* lst, int pos, Item* accessed)
{
    // NOTE: pos is index, begin from 0!
    int idx = 0;
    ULNode* node = lst;
    while(pos != 0){
        int num_elem = node->back - node->front - 1;
        int chk = pos - num_elem;
        //printf("before pos[%d] num_elem[%d] node[%p] next[%p] chk[%d]\n", pos, num_elem, node, node->next, chk);
        if(chk >= 0){
            node = node->next;
            pos = chk; // = 0 then break
        }else{
            idx = pos;
            pos = 0;
        }
        //printf("after  pos[%d] num_elem[%d] node[%p] next[%p] chk[%d]\n", pos, num_elem, node, node->next, chk);
    }

    *accessed = node->items[idx + node->front + 1];
    return SUCCESS;
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
    if(-1 < node->front){
        node->items[node->front--] = item;
        return SUCCESS;
    }
    // check items overflow
    return FAILURE;
}
