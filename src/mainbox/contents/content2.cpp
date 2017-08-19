//
// Created by poh on 8/17/17.
//

#include "contents.h"

mainbox::content2::content2(mainbox *pMainBox){
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    imgarea = Gtk::manage(new img_area());

    btm_bar = Gtk::manage(new bottombar(imgarea));
    worktools_box =  Gtk::manage(new worktools(imgarea,btm_bar));
    img_scroll =  Gtk::manage(new img_scrollable(imgarea));

    img_box = Gtk::manage(new Gtk::Box());
    img_box->set_orientation(Gtk::ORIENTATION_VERTICAL);
    img_box->pack_start(*img_scroll,Gtk::PACK_EXPAND_WIDGET);
    img_box->pack_start(*btm_bar,Gtk::PACK_SHRINK);

    pack_start(*img_box,Gtk::PACK_EXPAND_WIDGET);
    pack_start(*worktools_box,Gtk::PACK_SHRINK);
};


