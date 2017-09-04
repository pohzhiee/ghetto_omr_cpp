//
// Created by poh on 9/3/17.
//

#include <iostream>
#include "LayerTools.h"

LayerTools::LayerTools(LayerBox *layerbox) : tool_button_size(25)
{
    parent = layerbox;
    {
        set_orientation(Gtk::ORIENTATION_HORIZONTAL);
        set_hexpand(false);
        set_halign(Gtk::ALIGN_START);
    }

    /*
     * Create first button
     */
    {
        const auto icon = Gdk::Pixbuf::create_from_file("../icons/alienarena.svg",tool_button_size,tool_button_size);
        auto btn = std::make_shared<Gtk::Button>();
        tool_image_list.push_back(std::make_unique<Gtk::Image>(icon));
        btn->set_image(*tool_image_list[0]);
        btn->signal_clicked().connect(sigc::mem_fun(*this,&LayerTools::on_button1_clicked));
        tool_button_list.push_back(btn);
    }
    /*
     * Create second button
     */
    {
        const auto icon = Gdk::Pixbuf::create_from_file("../icons/browser.svg",tool_button_size,tool_button_size);
        auto btn = std::make_shared<Gtk::Button>();
        tool_image_list.push_back(std::make_unique<Gtk::Image>(icon));
        btn->set_image(*tool_image_list[1]);
        btn->signal_clicked().connect(sigc::mem_fun(*this,&LayerTools::on_button2_clicked));
        tool_button_list.push_back(btn);
    }
    /*
     * Pack the buttons into the box
     */
    {
        for(auto btn_ptr : tool_button_list)
        {
            pack_start(*btn_ptr,Gtk::PACK_SHRINK);
        }
    }
}

LayerTools::~LayerTools() {

}

void LayerTools::on_button1_clicked() {
    parent->parent_delete_active_row();
}

void LayerTools::on_button2_clicked() {
    Glib::ustring temp = "ASDF 123";
    parent->add_row(temp);
}
