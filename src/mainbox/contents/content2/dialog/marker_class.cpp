//
// Created by poh on 8/23/17.
//

#include <iostream>
#include "marker_class.h"
#include "../../../../data/marker_data.h"

marker_class::marker_class(std::shared_ptr<selection_data> data_pointer)
{
    data_pointer == nullptr ? p_data = std::make_shared<marker_data>() : p_data = data_pointer;

    Glib::ustring text;
    try {
        text = p_data->get_value_by_key("layer_name");
    }
    catch (std::invalid_argument &e)    {
        std::cerr << e.what() << std::endl;
    }

    Gdk::RGBA color = p_data->get_color();

    layer_entry = add_field("Layer Name: ",text);
    add_color_selector(color);
}

std::shared_ptr<selection_data> marker_class::save_values()
{
    p_data->set_coords(coords_init,coords_final);
    p_data->set_color(m_Color);
    p_data->set_value_by_key(std::make_pair("layer_name",layer_entry->get_text()));


    return p_data;

}
