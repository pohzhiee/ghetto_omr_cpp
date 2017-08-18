//
// Created by poh on 8/17/17.
//

#include "contents.h"
#include "content2/worktools.h"
#include "content2/img_area.h"

mainbox::content2::content2(mainbox *pMainBox){
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    worktools_box = new worktools(this);
    img_box = new img_area(this);

    window = (*pMainBox).get_window();
    window->set_events(Gdk::EventMask::ENTER_NOTIFY_MASK);
    pack_start(*img_box);
    pack_start(*worktools_box,Gtk::PackOptions::PACK_SHRINK);
};