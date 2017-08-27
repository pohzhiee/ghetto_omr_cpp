//
// Created by poh on 8/23/17.
//

#include "selection_data.h"
#include <iostream>


selection_data::selection_data()
{
    layer_name = "Layer 0";
    border_color = Gdk::RGBA("000000");
    init_coord = coords();
    final_coord = coords();
    isnum = false;
    ismarker = false;
    ismcq = false;
}

void selection_data::print_params()
{
    std::cout << "BASE CLASS PRINT CALLED?!?!?" << std::endl;
    std::cout << "Layer name: " << layer_name << std::endl;
    std::cout << "Initial coords, X:" << init_coord.x << "\t Y: " << init_coord.y << std::endl;
    std::cout << "Final coords, X:" << final_coord.x << "\t Y: " << final_coord.y << std::endl;
}

std::unordered_map<std::string, Glib::ustring> selection_data::get_param_map()
{
    std::unordered_map<std::string, Glib::ustring> mymap;
    mymap.insert ( std::pair<std::string, Glib::ustring>("type","NOTHING") );


    return mymap;
}

numerical_data::numerical_data() {
    bubble_shape = "Unknown shape";
    orientation = "Some orientation";
    no_col = "0";
    no_row = "0";
    no_qn = "0";
    no_digit = "0";

}

void numerical_data::print_params()
{
    std::cout << "Layer name: " << layer_name << std::endl;
    std::cout << "Initial coords, X:" << init_coord.x << "\t Y: " << init_coord.y << std::endl;
    std::cout << "Final coords, X:" << final_coord.x << "\t Y: " << final_coord.y << std::endl;
    std::cout << "Bubble Shape: " << bubble_shape << std::endl;
    std::cout << "Orientation: " << orientation << std::endl;
    std::cout << "Number of columns: " << no_col << std::endl;
    std::cout << "Number of rows: " << no_row << std::endl;
    std::cout << "Number of questions: " << no_qn << std::endl;
    std::cout << "Number of digits: " << no_digit << std::endl;
}


mcq_data::mcq_data()
{
    bubble_shape = "Unknown shape";
    orientation = "Some orientation";
    no_col = "0";
    no_row = "0";
    no_qn = "0";
}

void mcq_data::print_params()
{
    std::cout << "MCQ PRINT PARAMS CALLED" << std::endl;
    std::cout << "Layer name: " << layer_name << std::endl;
    std::cout << "Initial coords, X:" << init_coord.x << "\t Y: " << init_coord.y << std::endl;
    std::cout << "Final coords, X:" << final_coord.x << "\t Y: " << final_coord.y << std::endl;
    std::cout << "Bubble Shape: " << bubble_shape << std::endl;
    std::cout << "Orientation: " << orientation << std::endl;
    std::cout << "Number of columns: " << no_col << std::endl;
    std::cout << "Number of rows: " << no_row << std::endl;
    std::cout << "Number of questions: " << no_qn << std::endl;
}
std::unordered_map<std::string, Glib::ustring> mcq_data::get_param_map()
{
    std::unordered_map<std::string, Glib::ustring> mymap;
    mymap.insert ( std::pair<std::string, Glib::ustring>("type","MCQ") );
    mymap.insert ( std::pair<std::string, Glib::ustring>("bubble_shape",bubble_shape) );
    mymap.insert ( std::pair<std::string, Glib::ustring>("orientation",orientation) );
    mymap.insert ( std::pair<std::string, Glib::ustring>("no_col",no_col) );
    mymap.insert ( std::pair<std::string, Glib::ustring>("no_row",no_row) );
    mymap.insert ( std::pair<std::string, Glib::ustring>("no_qn",no_qn) );


    return mymap;
}

marker_data::marker_data()
{
}