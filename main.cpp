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
    //int num_data = 1e6; int node_size = 1e3;
    int num_data = 1e3; int node_size = 50;
    //int num_data = 20; int node_size = 10;
    
    if(argc > 1){
        int argv1ret = sscanf(argv[1], "%d", &num_data);
        int argv2ret = sscanf(argv[2], "%d", &node_size);
        if(argv1ret == EOF || argv2ret == EOF){
            std::cout << "argv error: " << '\n';
            std::cout << argv[0] << ',' 
                      << argv[1] << ',' 
                      << argv[2] << '\n';
        }
    }

    std::cout << "data.num: " << num_data << "\n";
    std::cout << "node.size: " << node_size << "\n";
    ULNode* ulist; init_list(&ulist, node_size); //unrolled
    ULNode* list;  init_list(&list, 1); // just linked list

    EXPR("ul.insert.front", "ulist insert front running time",
        for(int i = 0; i < num_data; i++){
            insert(&ulist, 0, i);
        }
    );
    //print_list(ulist, TRUE);
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
    //print_list(list, TRUE);
    EXPR("l.remove.front", "list remove front running time",
        for(int i = 0; i < num_data; i++){
            //std::cout << i << ", ";
            remove(&list, 0, NULL);
        }
    );


    EXPR("ul.insert.back", "ulist insert back running time",
        for(int i = 0; i < num_data; i++){
            insert(&ulist, -1, i);
        }
    );
    EXPR("ul.remove.back", "ulist remove back running time",
        for(int i = 0; i < num_data; i++){
            remove(&ulist, -1, NULL);
        }
    );

    EXPR("l.insert.back", "list insert back running time",
        for(int i = 0; i < num_data; i++){
            insert(&list, -1, i);
        }
    );
    EXPR("l.remove.back", "list remove back running time",
        for(int i = 0; i < num_data; i++){
            //std::cout << i << ", ";
            remove(&list, -1, NULL);
        }
    );
}
