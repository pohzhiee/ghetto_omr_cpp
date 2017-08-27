//
// Created by poh on 8/22/17.
//

#include "numerical_class.h"
#include <iostream>

numerical_class::numerical_class()
{

    //First parameter, layer name
    auto layer_label = Gtk::manage(new Gtk::Label("Layer Name: "));
    auto layer_entry = Gtk::manage(new Gtk::Entry());
    layer_entry->set_text("Numerical 0");

    add_field(layer_label,layer_entry);
    //Second parameter, shape
    add_checkable_field("Bubble Shape: ", {"Circle", "Oval", "Rectangle", "Square"});

    //Third Parameter, orientation
    entries entry_temp = {"Vertical", "Horizontal"};
    entries icon_path_array = {"../icons/orientation_vertical.svg","../icons/orientation_horizontal.svg"};
    add_icon_combobox("Question Orientation: ", entry_temp, icon_path_array,50);

    //Fourth Parameter, Number of columns
    entries entr_temp;
    for (int i = 1; i<=50 ; i++)
    {
        entr_temp.push_back(std::to_string(i));
    }
    add_checkable_field("Number of Columns: ", entr_temp);
    //Fifth Parameter, Number of rows
    add_checkable_field("Number of Rows: ", entr_temp);

    //Sixth Parameter, Number of questions
    for (int i=51;i<=100;i++)
    {
        entr_temp.push_back(std::to_string(i)) ;
    }
    add_checkable_field("Number of Questions: ", entr_temp);

    //Seventh Parameter, number of digits
    entries::const_iterator first = entr_temp.begin();
    entries::const_iterator dig_last = entr_temp.begin() + 6;
    add_checkable_field("Number of digits: ", entries(first,dig_last));

    //Eighth Parameter, selection border color
    add_color_selector();
}


void numerical_class::save_values()
{
    std::cout << "NUMERICAL VALUE SAVED" << std::endl;
}