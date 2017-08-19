//
// Created by poh on 8/19/17.
//

#ifndef GTK_MAIN_BOTTOMBAR_H
#define GTK_MAIN_BOTTOMBAR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include "img_area.h"
#include "../../../../data/data.h"

class bottombar : public Gtk::Box {
public:
    bottombar(img_area *pimgarea);

protected:
    img_area *pimgarea;

    Gtk::Label guide_label;
    Gtk::Entry size_entry;

    Glib::ustring text, text_buffer;
    int inp_int;

    void set_text_proper();
    Glib::ustring percent_to_string(int &percent);
};


#endif //GTK_MAIN_BOTTOMBAR_H
