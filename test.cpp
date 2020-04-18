// map <F8> :wa<CR>:!clear;rm test;g++ -g test.cpp ulist.c -o test -lgtest;./test<CR>

#include <gtest/gtest.h>
#include "ulist.h"

/*
printf("%d %d %p \n", root->back, root->max, root->next);
printf("[%p]\n", root);
printf("[%p]\n", *lst);
*/

//-------------------------------------------------------
TEST(is_empty, top_is_minus1_and_no_next_then_empty) {
    int node_size = 10;
    ULNode* root; init_list(&root, node_size);
    ASSERT_TRUE(is_empty(root));

    Item item = 42;
    int ret = insert(&root, 0, item);
    //printf("ret: %d \n", ret);
    ASSERT_FALSE(is_empty(root));
    //print_node(root, FALSE);
}

TEST(is_empty, back_is_not_0_but_empty){
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    insert(&lst, -1, 0); 
    insert(&lst, -1, 1);
    ASSERT_FALSE(is_empty(lst));

    //print_list(lst, TRUE);
    remove(&lst, 0, NULL); 
    //print_list(lst, TRUE);
    remove(&lst, 0, NULL);
    //print_list(lst, TRUE);
    ASSERT_TRUE(is_empty(lst));
}

//-------------------------------------------------------
TEST(insert, to_all_removed_list){
    int node_size = 6;
    int num_items = 10;
    ULNode* lst; init_list(&lst, node_size);

    // insert
    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
    }
    // remove
    for(int i = 0; i < num_items; i++){ 
        remove(&lst, -1, NULL);
    }
    ASSERT_TRUE(is_empty(lst));
    // insert
    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
    }
}

TEST(insert, front_from_zero){
    int node_size = 6;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < 4; i++){ 
        insert(&lst, 0, i); 
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
        //printf("----a %d---- \n",i); 
        //print_list(lst, TRUE);
    }

    Item accessed; 
    for(int i = 0; i < num_items; i++){ 
        get(lst, i, &accessed); 
        ASSERT_EQ(accessed, num_items - 1 - i);
    }

    int num_nodes = get_tail(lst, NULL);
    //printf("[%d]", num_nodes);
    ASSERT_LT(num_nodes, num_items);
}

//-------------------------------------------------------
TEST(remove, fail_cases){
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    ASSERT_EQ(remove(&lst, 0, NULL), FAILURE);
}

TEST(remove, front){
    int node_size = 8;
    int num_items = 10;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
    }
    for(int i = 0; i < num_items; i++){ 
        Item removed;
        remove(&lst, 0, &removed);
                //printf("---%d---\n", i);
                //print_list(lst, TRUE);
        ASSERT_EQ(removed, num_items - 1 - i);
    }
    ASSERT_TRUE(is_empty(lst));
}

TEST(remove, back){
    int node_size = 8;
    int num_items = 10;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < num_items; i++){ 
        insert(&lst, -1, i);
    }
    for(int i = 0; i < num_items; i++){ 
        Item removed;
        remove(&lst, -1, &removed);
                //printf("---%d---\n", i);
                //print_list(lst, TRUE);
        ASSERT_EQ(removed, num_items - 1 - i);
    }
    ASSERT_TRUE(is_empty(lst));
}

//-------------------------------------------------------
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
    //print_list(lst, FALSE);

    Item accessed; 
    get(lst, 0, &accessed); ASSERT_EQ(accessed, 0);
    get(lst, 1, &accessed); ASSERT_EQ(accessed, 1);
    get(lst, 2, &accessed); ASSERT_EQ(accessed, 2);
    //puts("-0--0-");
    get(lst, 3, &accessed); ASSERT_EQ(accessed, 3);
    get(lst, 4, &accessed); ASSERT_EQ(accessed, 4);
}

TEST(get, more_than_1_node_size) {
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

TEST(get, FAIL_when_get_node_from_empty_list) {
    int node_size = 4;
    ULNode* lst; init_list(&lst, node_size);

    Item accessed;
    EXPECT_EQ(get(lst, 0, &accessed), FAILURE);
}

//-------------------------------------------------------------------------------------
TEST(decode_pos, fail_cases){
    int node_size = 7;
    int num_items = 7;
    ULNode* lst; init_list(&lst, node_size);

    // insert
    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
    }
    print_list(lst,TRUE);

    // decode_pos: fail cases
    //  negative pos
    ULNode* node = NULL; int idx;
    ASSERT_EQ(decode_pos(lst, -1, NULL, &node, &idx), FAILURE); 
    ASSERT_EQ(decode_pos(lst, -2432, NULL, &node, &idx), FAILURE); 
    //  too big pos
    ASSERT_EQ(decode_pos(lst, num_items - 1, NULL, &node, &idx), SUCCESS); 
    ASSERT_EQ(decode_pos(lst, num_items, NULL, &node, &idx), FAILURE); 
    ASSERT_EQ(decode_pos(lst, num_items + 1, NULL, &node, &idx), FAILURE); 
    ASSERT_EQ(decode_pos(lst, num_items * 10, NULL, &node, &idx), FAILURE); 
}

TEST(positive_pos, DISABLED_insert){
    int node_size = 7;
    int num_items = 7;
    ULNode* lst; init_list(&lst, node_size);

    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
    }
    print_list(lst,TRUE);

    // insert to empty slot
    int expected = 99;
    int pos = 1;
    insert(&lst, pos, expected);
    Item accessed; get(lst, pos, &accessed);
    ASSERT_EQ(accessed, expected);
}

//-------------------------------------------------------------------------------------
TEST(big, DISABLED_insert_front_remove_back){
    int node_size = 100;
    int num_items = 100000;
    ULNode* lst; init_list(&lst, node_size);

    // insert
    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
    }
    Item accessed; 
    for(int i = 0; i < num_items; i++){ 
        get(lst, i, &accessed); 
        ASSERT_EQ(accessed, num_items - 1 - i);
    }
    int num_nodes = get_tail(lst, NULL);
    ASSERT_LT(num_nodes, num_items);

    // remove
    for(int i = 0; i < num_items; i++){ 
        Item removed;
        remove(&lst, -1, &removed);
        ASSERT_EQ(removed, i);
    }
    ASSERT_TRUE(is_empty(lst));
}

TEST(big, DISABLED_insert_back_remove_front){
    int node_size = 100;
    int num_items = 100000;
    ULNode* lst; init_list(&lst, node_size);

    // insert
    for(int i = 0; i < num_items; i++){ 
        insert(&lst, -1, i);
    }
    Item accessed; 
    for(int i = 0; i < num_items; i++){ 
        get(lst, i, &accessed); 
        ASSERT_EQ(accessed, i);
    }

    // remove
    for(int i = 0; i < num_items; i++){ 
        Item removed;
        remove(&lst, 0, &removed);
        ASSERT_EQ(removed, i);
    }
    ASSERT_TRUE(is_empty(lst));
}

//-------------------------------------------------------------------------------------
TEST(node_size1, insert_remove_from_front){
    int node_size = 1;
    //int node_size = 2;
    int num_items = 10;
    ULNode* lst; init_list(&lst, node_size);

    //printf("empty:\n"); print_list(lst, TRUE);
    // insert
    for(int i = 0; i < num_items; i++){ 
        insert(&lst, 0, i);
        //printf("insert %d:\n", i); print_list(lst, TRUE);
    }
    Item accessed; 
    // get pos=0 
    ASSERT_EQ(get(lst, 0, &accessed), SUCCESS); 
    ASSERT_EQ(accessed, 9);

    for(int i = 0; i < num_items; i++){ 
        get(lst, i, &accessed); 
        ASSERT_EQ(accessed, num_items - 1 - i);
    }
    ASSERT_FALSE(is_empty(lst));

    // remove
    for(int i = 0; i < num_items; i++){ 
        Item removed;
        remove(&lst, 0, &removed);
        ASSERT_EQ(removed, num_items - 1 - i);
    }
    ASSERT_TRUE(is_empty(lst));
}

//-------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
