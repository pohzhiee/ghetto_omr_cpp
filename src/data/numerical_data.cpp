//
// Created by poh on 9/6/17.
//


#include "numerical_data.h"
#include <iostream>

int numerical_data::num_count =0;

numerical_data::numerical_data() : index(selection_data::unique_index)
{
    border_color.set_red(0);
    border_color.set_green(0);
    border_color.set_blue(0);
    border_color.set_alpha(1);
    std::string count_str = std::to_string(num_count++);
    variables["layer_name"] = "Numerical " + count_str;
    variables["bubble_shape"] = "Oval";
    variables["orientation"] = "Vertical";
    variables["no_columns"] = "0";
    variables["no_rows"] = "0";
    variables["no_questions"] = "0";
    variables["no_digits"] = "0";
    variables["type"] = "numerical";
}

numerical_data::~numerical_data()
{
    num_count--;
}

//Getters
Glib::ustring numerical_data::get_value_by_key(std::string key)
{
    std::unordered_map<std::string,Glib::ustring>::const_iterator got = variables.find(key);

    if ( got == variables.end() )
    {
        throw std::invalid_argument("No such key");
    }
    else
    {
        return got->second;
    }
}

Gdk::RGBA numerical_data::get_color() const {
    return border_color;
}

long numerical_data::get_index() const {
    return index;
}
//Setters
void numerical_data::set_value_by_key(std::pair<std::string, Glib::ustring> pair)
{
    variables[pair.first] = pair.second;
}

void numerical_data::set_color(Gdk::RGBA color) {
    border_color = color;
}

