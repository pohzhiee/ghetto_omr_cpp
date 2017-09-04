//
// Created by poh on 9/3/17.
//

#include <gtkmm/scrolledwindow.h>
#include <iostream>
#include "LayerBox.h"
#include "LayerTools.h"
#include "LayerListScrollable.h"

LayerBox::LayerBox(content2 *parent)
{
    p_content2 = parent;
    {
        //Initialise tools and list
        tools = std::make_shared<LayerTools>(this);
        list = std::make_shared<LayerListScrollable>(this);
    }

    {
        pack_start(*list,Gtk::PACK_EXPAND_WIDGET);
        pack_start(*tools,Gtk::PACK_SHRINK);
    }
    set_orientation(Gtk::ORIENTATION_VERTICAL);


    show_all_children();
}

LayerBox::~LayerBox()
{
}

/**
 * Calls the delete_active_row method in the TreeView (aka the list) such that active row is deleted
 * Serve as means to access siblings (such as the tools accessing the list)
 */
void LayerBox::parent_delete_active_row()
{
    list->delete_active_row();
}


void LayerBox::add_row(Glib::ustring &input)
{
    list->add_row(input);
}
