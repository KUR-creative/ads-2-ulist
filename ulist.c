#include <stdlib.h>
#include <stdio.h>
#include "ulist.h"

int init_list(ULNode** lst, int node_size)
{
    *lst = (ULNode*)malloc(
        sizeof(ULNode) + sizeof(Item) * node_size);
    ULNode* root = *lst;
    root->top = 0;
    root->max = node_size;
    root->next = NULL;
    return SUCCESS;
}

int is_empty(ULNode** lst)
{
    ULNode* root = *lst;
    return (root->next == NULL && root->top == 0);
}

int insert(ULNode** lst, int pos, Item item)
{
    ULNode* root = *lst;
    root->items[root->top++] = item;
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
