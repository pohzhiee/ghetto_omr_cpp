//
// Created by poh on 8/17/17.
//

#include "contents.h"
#include "content2/worktools.h"
#include "content2/img_area.h"
#include <iostream>

mainbox::content2::content2(mainbox *pMainBox){
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    worktools_box = new worktools(this);
    imgarea = new img_area(this);
//    img_box1 = Gtk::Box();
//    img_box1.pack_start(*imgarea,Gtk::PackOptions::PACK_SHRINK);
//    img_box1.set_name("img_box");
//    img_box1.set_vexpand(FALSE);
//    img_box1.set_valign(Gtk::ALIGN_CENTER);

//    img_box1a.pack_start(*imgarea,Gtk::PackOptions::PACK_SHRINK);
//    img_box1a.set_name("img_box");
//    img_box1a.set_vexpand(FALSE);
//    img_box1a.set_valign(Gtk::ALIGN_CENTER);
    img_box1a.set_child_widget(*imgarea);
    img_box1a.set_valign(Gtk::ALIGN_CENTER);


    img_box2 = Gtk::Box();
    img_box2.pack_start(img_box1a,Gtk::PackOptions::PACK_EXPAND_PADDING);
    img_box2.set_name("img_box2");

    pack_start(img_box2,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    pack_start(*worktools_box,Gtk::PackOptions::PACK_SHRINK);
};


