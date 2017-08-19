//
// Created by poh on 8/19/17.
//

#ifndef GTK_MAIN_IMG_SCROLLABLE_H
#define GTK_MAIN_IMG_SCROLLABLE_H


#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include "img_border_box.h"
#include "img_area.h"

class img_scrollable : public Gtk::ScrolledWindow
{
public:
    img_scrollable(img_area *imgarea);
protected:
    img_border_box border_cont;
    Gtk::Box box;
};


#endif //GTK_MAIN_IMG_SCROLLABLE_H
