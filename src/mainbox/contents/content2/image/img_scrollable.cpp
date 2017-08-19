//
// Created by poh on 8/19/17.
//

#include "img_scrollable.h"


img_scrollable::img_scrollable(img_area *imgarea)
{
    border_cont.set_child_widget(*imgarea);
    border_cont.set_valign(Gtk::ALIGN_CENTER);

    box = Gtk::Box();
    box.set_name("content2_img_padding");
    box.pack_start(border_cont,Gtk::PackOptions::PACK_EXPAND_PADDING);

    add(box);
    set_name("content2_img_scrollable");
};