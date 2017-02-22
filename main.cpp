#include <iostream>
#include "Pizza.h"

int main(int argc, char ** argv) {

    if(argc >= 2)
    {
        Pizza pizza(argv[1]);
        //pizza.print_cells();
        pizza.run_algorithm();
        int score = pizza.get_score();
        return 0;
    }

    return 1;
}