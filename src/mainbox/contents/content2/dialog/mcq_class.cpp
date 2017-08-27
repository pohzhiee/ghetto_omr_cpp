//
// Created by poh on 8/22/17.
//

#include "mcq_class.h"
#include <iostream>

mcq_class::mcq_class()
{
    //First parameter, layer name
    auto layer_label = Gtk::manage(new Gtk::Label("Layer Name: "));
    layer_entry = Gtk::manage(new Gtk::Entry());
    layer_entry->set_text("MCQ 0");

    add_field(layer_label,layer_entry);
    //Second parameter, shape
    //Checkable 1
    add_checkable_field("Bubble Shape: ", {"Circle", "Oval", "Rectangle", "Square"});

    //Third Parameter, orientation
    //icon_combobox_arr 1
    entries entry_temp = {"Vertical", "Horizontal"};
    entries icon_path_array = {"../icons/orientation_vertical.svg","../icons/orientation_horizontal.svg"};
    add_icon_combobox("Question Orientation: ", entry_temp, icon_path_array,50);

    //Fourth Parameter, Number of columns
    entries entr_temp;
    for (int i = 1; i<=50 ; i++)
    {
        entr_temp.push_back(std::to_string(i));
    }
    //Checkable 2
    add_checkable_field("Number of Columns: ", entr_temp);
    //Fifth Parameter, Number of rows
    //Checkable 3
    add_checkable_field("Number of Rows: ", entr_temp);

    //Sixth Parameter, Number of questions
    for (int i=51;i<=100;i++)
    {
        entr_temp.push_back(std::to_string(i)) ;
    }

    //Checkable 5
    add_checkable_field("Number of Questions: ", entr_temp);

    //Seventh Parameter, selection border color
    add_color_selector();
}



void mcq_class::save_values()
{
    std::shared_ptr<mcq_data> p_data;
    p_data = std::make_shared<mcq_data>();
    p_data->ismcq = true;
    p_data->init_coord = coords_init;
    p_data->final_coord = coords_final;
    p_data->border_color = m_Color;
    p_data->layer_name = layer_entry->get_text();
    p_data->bubble_shape = combobox_arr[0] ->get_active_text();
    p_data->no_col = combobox_arr[1] ->get_active_text();
    p_data->no_row = combobox_arr[2] ->get_active_text();
    p_data->no_qn = combobox_arr[3] ->get_active_text();

    //necessary long process to get
    auto treemodel_iter = icon_combobox_arr[0]->get_active();
    Gtk::TreeModel::Row row = *treemodel_iter;
    ModelColumns columns;
    p_data->orientation = row[columns.col_name];

    data::selections.push_back(p_data);

};