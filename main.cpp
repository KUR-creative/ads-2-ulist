// map <F4> :wa<CR>:!rm main;g++ main.cpp ulist.c -o main;./main<CR>

#include <iostream>
#include <chrono>
#include <numeric>   // iota
#include <vector>

#include "ulist.h"

namespace crn = std::chrono;

#define EXPR(key, description, code) do{            \
    auto beg_clk = crn::steady_clock::now();        \
    code                                            \
    auto end_clk = crn::steady_clock::now();        \
    auto run_time = end_clk - beg_clk;              \
    std::cout <<                                    \
        key": " <<                                  \
        crn::duration<double,std::milli>(run_time)  \
        .count() << std::endl;                      \
}while(0)


int main(int argc, char* argv[]){
    int num_data = 1e3;
    int node_size = 64;

    std::cout << "data.num: " << num_data << "\n";
    ULNode* ulist; init_list(&ulist, node_size); //unrolled
    ULNode* list;  init_list(&list, 1); // just linked list

    EXPR("ul.insert.front", "ulist insert front running time",
        for(int i = 0; i < num_data; i++){
            insert(&ulist, 0, i);
        }
    );
    EXPR("ul.remove.front", "ulist remove front running time",
        for(int i = 0; i < num_data; i++){
            remove(&ulist, 0, NULL);
        }
    );

    EXPR("l.insert.front", "list insert front running time",
        for(int i = 0; i < num_data; i++){
            insert(&list, 0, i);
        }
    );
    EXPR("l.remove.front", "list remove front running time",
        for(int i = 0; i < num_data; i++){
            remove(&list, 0, NULL);
        }
    );
}
