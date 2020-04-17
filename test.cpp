// map <F4> :wa<CR>:!clear;rm test;g++ -g test.cpp ulist.c -o test -lgtest;./test<CR>

#include <gtest/gtest.h>
#include "ulist.h"

/*
printf("%d %d %p \n", root->back, root->max, root->next);
printf("[%p]\n", root);
printf("[%p]\n", *lst);
*/

TEST(is_empty, top_is_minus1_and_no_next_then_empty) {
    int node_size = 10;
    ULNode* root; init_list(&root, node_size);
    ASSERT_TRUE(is_empty(root));

    Item item = 42;
    int ret = insert(&root, 0, item);
    printf("ret: %d \n", ret);
    ASSERT_FALSE(is_empty(root));
    print_node(root, FALSE);
}

TEST(remove, fail_cases){
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    ASSERT_EQ(remove(&lst, 0, NULL), FAILURE);
}

TEST(is_empty, back_is_not_0_but_empty){
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    insert(&lst, -1, 0); 
    insert(&lst, -1, 1);
    ASSERT_FALSE(is_empty(lst));

    remove(&lst, 0, NULL); 
    remove(&lst, 0, NULL);
    ASSERT_TRUE(is_empty(lst));
}

TEST(insert, front_from_zero){
    int node_size = 6;
    ULNode* lst; init_list(&lst, node_size);

    // insert front
                    //puts("--------"); print_list(lst, FALSE);
    for(int i = 0; i < 4; i++){ 
        insert(&lst, 0, i); 
                    //printf("----%d----\n", i); print_list(lst, FALSE);
    }
    Item accessed; 
    for(int i = 0; i < 4; i++){ 
        get(lst, i, &accessed); 
        ASSERT_EQ(accessed, 4 - 1 - i );
    }
}

TEST(insert, back_from_zero){
    int node_size = 8;
    ULNode* lst; init_list(&lst, node_size);

    // insert front
    for(int i = 0; i < 4; i++){ 
        insert(&lst, -1, i);
    }

    Item accessed; 
    for(int i = 0; i < 4; i++){ 
        get(lst, i, &accessed); ASSERT_EQ(accessed, i);
    }
}

TEST(insert, back_more_than_1node_max_capacity_when_next_is_nil){
    int node_size = 8;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < 10; i++){ 
        insert(&lst, -1, i);
    }

    Item accessed; 
    for(int i = 0; i < 10; i++){ 
        get(lst, i, &accessed); ASSERT_EQ(accessed, i);
    }
}

TEST(insert, front_more_than_1node_max_capacity){
    int node_size = 4;
    int num_items = 10;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
        printf("----a %d---- \n",i); 
        print_list(lst, TRUE);
    }

    Item accessed; 
    for(int i = 0; i < num_items; i++){ 
        get(lst, i, &accessed); 
        ASSERT_EQ(accessed, num_items - 1 - i);
    }

    ULNode* tmp = lst;
    int num_nodes = 0;
    while(tmp->next){
        tmp = tmp->next;
        num_nodes++;
    }
    ASSERT_LT(num_nodes, num_items);
}

TEST(get, 3_2_list){
    int node_size = 5;
    ULNode* lst; init_list(&lst, node_size);
    ULNode* lst2; init_list(&lst2, node_size);
    // 3
    insert(&lst, -1, 0);
    insert(&lst, -1, 1);
    insert(&lst, -1, 2);
    // 2
    insert(&lst2, -1, 3);
    insert(&lst2, -1, 4);
    // link
    lst->next = lst2;
    print_list(lst, FALSE);

    Item accessed; 
    get(lst, 0, &accessed); ASSERT_EQ(accessed, 0);
    get(lst, 1, &accessed); ASSERT_EQ(accessed, 1);
    get(lst, 2, &accessed); ASSERT_EQ(accessed, 2);
    //puts("-0--0-");
    get(lst, 3, &accessed); ASSERT_EQ(accessed, 3);
    get(lst, 4, &accessed); ASSERT_EQ(accessed, 4);
}

TEST(get, DISABLED_more_than_1_node_size) {
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < node_size + 2; i++){
        insert(&lst, -1, i);
    }
    for(int i = 0; i < node_size + 2; i++){
        Item accessed;
        get(lst, i, &accessed);
        ASSERT_EQ(accessed, i);
    }
}

TEST(get, DISABLED_incorrect_pos) {
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    Item accessed;
    ASSERT_EQ(get(lst, 0, &accessed), FAILURE);
}
/*
TEST(test, print_item) {
    Item xyb = 1;
    print_item(&xyb);
    puts("");
}

TEST(cbuf, push_and_pop) {
    size_t BUF_SIZE = 100;
    CirBuf cbuf; cbuf_init(&cbuf, BUF_SIZE);
    Item expected[3] = {1, 3, 5};
    for(int i = 0; i < 3; i++){
        cbuf_push(&cbuf, expected[i]);
    }
    for(int i = 0; i < 3; i++){
        Item actual = cbuf_pop(&cbuf);
        ASSERT_EQ(actual, expected[i]);
    }
}

TEST(cbuf, cannot_pop_from_empty_cbuf) {
    size_t BUF_SIZE = 100;
    CirBuf cbuf; cbuf_init(&cbuf, BUF_SIZE);
    ASSERT_TRUE(cbuf_empty(&cbuf));
    Item actual = cbuf_pop(&cbuf);
    ASSERT_EQ(actual, NONE_ITEM);
}

TEST(cbuf, cannot_push_to_full_cbuf) {
    size_t BUF_SIZE = 100;
    CirBuf cbuf; cbuf_init(&cbuf, BUF_SIZE);
    Item yx = 0;
    for(int i = 1; i <= BUF_SIZE - 1; i++){
        ASSERT_EQ(cbuf_push(&cbuf, yx), SUCCESS);
    }
    ASSERT_EQ(cbuf_push(&cbuf, yx), FAILURE);
}

TEST(cbuf, circular_push) {
    size_t BUF_SIZE = 100;
    CirBuf cbuf; cbuf_init(&cbuf, BUF_SIZE);
    Item expected[BUF_SIZE - 1] = {9, 0};

    for(int i = 0; i < BUF_SIZE - 1; i++){
        cbuf_push(&cbuf, expected[i]);
    }
    for(int i = 0; i < BUF_SIZE - 1; i++){
        Item actual = cbuf_pop(&cbuf);
        ASSERT_EQ(actual, expected[i]);
    }

    for(int i = 0; i < BUF_SIZE - 1; i++){
        ASSERT_EQ(cbuf_push(&cbuf, expected[i]), SUCCESS);
    }
    for(int i = 0; i < BUF_SIZE - 1; i++){
        Item actual = cbuf_pop(&cbuf);
        ASSERT_EQ(actual, expected[i]);
    }

    Item yx = 1;
    for(int i = 0; i < BUF_SIZE * 2; i++){
        cbuf_push(&cbuf, yx);
    }
    ASSERT_TRUE(cbuf_full(&cbuf));
    for(int i = 0; i < BUF_SIZE * 2; i++){
        cbuf_pop(&cbuf);
    }
    ASSERT_TRUE(cbuf_empty(&cbuf));
}
*/


//-------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
