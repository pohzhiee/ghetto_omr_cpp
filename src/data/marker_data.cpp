//
// Created by poh on 9/6/17.
//

#include "marker_data.h"

int marker_data::marker_count = 0;

marker_data::marker_data()
{
    border_color.set_red(1);
    border_color.set_green(1);
    border_color.set_blue(0);
    border_color.set_alpha(1);
    std::string count_str = std::to_string(marker_count++);
    variables["layer_name"] = "Marker " + count_str;
}

marker_data::~marker_data()
{
    marker_count--;
}

//Getters
Glib::ustring marker_data::get_value_by_key(std::string key)
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

Gdk::RGBA marker_data::get_color() const {
    return border_color;
}

//Setters
void marker_data::set_value_by_key(std::pair<std::string, Glib::ustring> pair)
{
    variables[pair.first] = pair.second;
}

void marker_data::set_color(Gdk::RGBA color) {
    border_color = color;
}
