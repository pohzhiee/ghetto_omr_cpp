//
// Created by poh on 8/17/17.
//

#include "contents.h"
#include "content2/worktools.h"
#include "content2/imgbox.h"

mainbox::content2::content2(mainbox *pMainBox){
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    worktools_box = new worktools(this);
    img_box = new imgbox(this);
    pack_start(*img_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    pack_start(*worktools_box,Gtk::PackOptions::PACK_SHRINK);
};