//
// Created by poh on 8/23/17.
//

#include "marker_class.h"

marker_class::marker_class()
{
    auto layer_label = Gtk::manage(new Gtk::Label("Layer Name: "));
    layer_entry = Gtk::manage(new Gtk::Entry());
    layer_entry->set_text("Marker 0");

    add_field(layer_label,layer_entry);
    add_color_selector();
    m_Color.set_red(1.0);
    m_Color.set_green(1.0);
    m_Color.set_blue(1.0);
    m_Color.set_alpha(1.0); //opaque
}

void marker_class::save_values()
{
    std::shared_ptr<marker_data> p_data;
    p_data = std::make_shared<marker_data>();
    p_data->ismarker = true;
    p_data->init_coord = coords_init;
    p_data->final_coord = coords_final;
    p_data->border_color = m_Color;
    p_data->layer_name = layer_entry->get_text();


    data::selections.push_back(p_data);

}