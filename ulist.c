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
    *lst = (ULNode*)malloc(
        sizeof(ULNode) + sizeof(Item) * node_size);
    ULNode* root = *lst;
    root->front = -1;
    root->back = 0;
    root->max = node_size;
    root->next = NULL;
    return SUCCESS;
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
            *lst = (ULNode*)malloc(
                sizeof(ULNode) + sizeof(Item) * tmp->max);
            (*lst)->front = -1;
            (*lst)->back = 0;
            (*lst)->max = tmp->max;
            (*lst)->next = tmp;

            (*lst)->items[(*lst)->back++] = item; 
        }
    }
    else if(pos == -1){
        (*lst)->items[(*lst)->back++] = item;
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
