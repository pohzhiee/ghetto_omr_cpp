//
// Created by poh on 8/23/17.
//

#include "marker_class.h"

marker_class::marker_class()
{
    auto layer_label = Gtk::manage(new Gtk::Label("Layer Name: "));
    auto layer_entry = Gtk::manage(new Gtk::Entry());
    layer_entry->set_text("Marker 0");

    add_field(layer_label,layer_entry);
    add_color_selector();
}

void marker_class::save_values()
{
}