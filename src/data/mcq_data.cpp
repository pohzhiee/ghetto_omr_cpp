//
// Created by poh on 9/6/17.
//

#include "mcq_data.h"


int mcq_data::mcq_count =0;

mcq_data::mcq_data()
{
    border_color.set_red(1);
    border_color.set_green(0);
    border_color.set_blue(0);
    border_color.set_alpha(1);
    std::string count_str = std::to_string(mcq_count++);
    variables["layer_name"] = "MCQ " + count_str;
    variables["bubble_shape"] = "Oval";
    variables["orientation"] = "Vertical";
    variables["no_columns"] = "0";
    variables["no_rows"] = "0";
    variables["no_questions"] = "0";
}

mcq_data::~mcq_data()
{
    mcq_count--;
}

//Getters
Glib::ustring mcq_data::get_value_by_key(std::string key)
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

Gdk::RGBA mcq_data::get_color() const {
    return border_color;
}

//Setters
void mcq_data::set_value_by_key(std::pair<std::string, Glib::ustring> pair)
{
    variables[pair.first] = pair.second;
}

void mcq_data::set_color(Gdk::RGBA color) {
    border_color = color;
}
