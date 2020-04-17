#include <stdlib.h>
#include <stdio.h>
#include "ulist.h"

int print_node(ULNode* node)
{
    printf("front[%d] back[%d] max[%d] ", 
        node->front, node->back, node-> max);
    printf("arr[ ");
    for(int i = 0; i < node->back; i++){
        printf("%d ", node->items[i]);
    }
    printf("] next:%p \n", node->next);
}

int print_list(ULNode* lst)
{
    ULNode* cursor = lst;
    while(cursor){
        print_node(cursor);
        cursor = cursor->next;
    }
}

int init_list(ULNode** lst, int node_size)
{
    return new_node(lst, node_size, NULL);
}

int is_empty(ULNode* lst)
{
    return (lst->next == NULL && lst->back == 0);
}

int insert(ULNode** lst, int pos, Item item)
{
    //print_node(*lst);
    if(pos == 0){
        if((*lst)->front == -1){
            ULNode* tmp = *lst;
            new_node(lst, tmp->max, tmp);
            add_back(*lst, item);
        }
    }
    else if(pos == -1){
        add_back(*lst, item);
        return SUCCESS;
    }
}

int get(ULNode* lst, int pos, Item* accessed)
{
    int cursor = 0;
    int idx = 0;
    ULNode* node = lst;
    while(cursor != pos){
        int num_elem = node->back - node->front - 1;
        cursor += num_elem;
        node = node->next;
    }

    *accessed = node->items[idx];
    return SUCCESS;
}

int remove(ULNode** lst, int pos, Item* removed)
{
    return SUCCESS;
}

static int new_node(
    ULNode** pnode, int max, ULNode* next)
{
    *pnode = (ULNode*)malloc(
        sizeof(ULNode) + sizeof(Item) * max);
    (*pnode)->front = -1;
    (*pnode)->back = 0;
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


/* 
void print_item(const Item* item)
{
    //printf("%d,%d", item->x, item->y);
    printf("%d", *item);
}

int cbuf_init(CirBuf* cbuf, size_t buf_size)
{
    cbuf->cbuf = (Item*)malloc(buf_size * sizeof(Item));
    if(cbuf->cbuf == NULL){
        return FAILURE;
    }
    cbuf->buf_size = buf_size;
    cbuf->head = cbuf->tail = 0;
    return SUCCESS;
}

int cbuf_deinit(CirBuf* cbuf)
{
    free(cbuf->cbuf);
    return SUCCESS;
}

int cbuf_empty(CirBuf* cbuf)
{
    return cbuf->head == cbuf->tail;
}

int cbuf_full(CirBuf* cbuf)
{
    return cbuf->head == (cbuf->tail + 1) % cbuf->buf_size;
}

int cbuf_push(CirBuf* cbuf, Item item)
{
    if(cbuf_full(cbuf)){
        return FAILURE;
    }else{
        cbuf->cbuf[cbuf->tail] = item;
        cbuf->tail = (cbuf->tail + 1) % cbuf->buf_size;
        return SUCCESS;
    }
}

Item cbuf_pop(CirBuf* cbuf)
{
    if(cbuf_empty(cbuf)){
        return NONE_ITEM;
    }else{
        Item ret = cbuf->cbuf[cbuf->head];
        cbuf->head = (cbuf->head + 1) % cbuf->buf_size;
        return ret;
    }
}
*/
