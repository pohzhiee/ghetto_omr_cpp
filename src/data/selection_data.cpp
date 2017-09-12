//
// Created by poh on 8/23/17.
//

#include "selection_data.h"
#include <iostream>

long selection_data::unique_index =0;

selection_data::selection_data() : isVisible(true)
{
    unique_index++;
}

void selection_data::set_coords(coords input_init_coord, coords input_final_coord) {
    init_coord = input_init_coord;
    final_coord = input_final_coord;
}

std::pair<coords, coords> selection_data::get_coords() {
    return std::make_pair(init_coord,final_coord);
}
