//
// Created by poh on 8/22/17.
//

#include "numerical_class.h"
#include <iostream>

numerical_class::numerical_class(std::shared_ptr<selection_data> data_pointer)
{
    data_pointer == nullptr ? p_data = std::make_shared<numerical_data>() : p_data = data_pointer;

    //First parameter, layer name

    {
        Glib::ustring layer_name;
        try{
            layer_name=p_data->get_value_by_key("layer_name");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }
        layer_entry=add_field("Layer Name: ", layer_name);
    }

    //Second parameter, shape
    {
        Glib::ustring bubble_shape;
        try{
            bubble_shape=p_data->get_value_by_key("bubble_shape");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }
        entries entry_temp = {"Circle", "Oval", "Rectangle", "Square"};
        entries icon_path_array = {"../icons/circle.svg",
                                   "../icons/oval.svg",
                                   "../icons/rectangle.svg",
                                   "../icons/square.svg"};
        shape_combobox=add_icon_combobox("Bubble Shape: ", entry_temp, icon_path_array,30,bubble_shape);
    }

    //Third Parameter, orientation
    {
        Glib::ustring orientation;
        try{
            orientation=p_data->get_value_by_key("orientation");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }
        entries entry_temp = {"Vertical", "Horizontal"};
        entries icon_path_array = {"../icons/orientation_vertical.svg","../icons/orientation_horizontal.svg"};
        orientation_combobox=add_icon_combobox("Question Orientation: ", entry_temp, icon_path_array,50,orientation);
    }

    //Fourth Parameter, Number of columns
    {
        Glib::ustring no_columns;
        try{
            no_columns=p_data->get_value_by_key("no_columns");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }

        col_entry = add_int_field("Number of Columns", no_columns);
    }

    //Fifth Parameter, Number of rows
    {
        Glib::ustring no_rows;
        try{
            no_rows=p_data->get_value_by_key("no_rows");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }

        row_entry = add_int_field("Number of Rows", no_rows);
    }

    //Sixth Parameter, Number of questions
    {
        Glib::ustring no_questions;
        try{
            no_questions=p_data->get_value_by_key("no_questions");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }

        qn_entry = add_int_field("Number of Questions", no_questions);
    }
    //Seventh Parameter, number of digits
    {
        Glib::ustring no_digits;
        try{
            no_digits=p_data->get_value_by_key("no_digits");
        }
        catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
        }

        digit_entry = add_int_field("Number of Digits", no_digits);
    }

    //Eighth Parameter, selection border color
    {
        Gdk::RGBA color = p_data->get_color();
        add_color_selector(color);
    }
}



std::shared_ptr<selection_data> numerical_class::save_values()
{
    p_data->set_coords(coords_init, coords_final);
    p_data->set_color(m_Color);
    p_data->set_value_by_key(std::make_pair("layer_name",layer_entry->get_text()));
    p_data->set_value_by_key(std::make_pair("no_columns",col_entry->get_text()));
    p_data->set_value_by_key(std::make_pair("no_rows",row_entry->get_text()));
    p_data->set_value_by_key(std::make_pair("no_questions",qn_entry->get_text()));
    p_data->set_value_by_key(std::make_pair("no_digits",digit_entry->get_text()));

    //Get the proper value out of shape_combobox
    {
        ModelColumns columns;
        auto treemodel_iter = shape_combobox->get_active();
        Gtk::TreeModel::Row row = *treemodel_iter;
        p_data->set_value_by_key(std::make_pair("bubble_shape",row[columns.col_name]));
    }
    //Get the proper value out of orientation_combobox
    {
        ModelColumns columns;
        auto treemodel_iter = orientation_combobox->get_active();
        Gtk::TreeModel::Row row = *treemodel_iter;
        p_data->set_value_by_key(std::make_pair("orientation",row[columns.col_name]));
    }

    return p_data;

};
