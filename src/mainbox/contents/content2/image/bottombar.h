//
// Created by poh on 8/19/17.
//

#ifndef GTK_MAIN_BOTTOMBAR_H
#define GTK_MAIN_BOTTOMBAR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include "img_area.h"
#include "../../../../data/data.h"

class bottombar : public Gtk::Box {
public:
    bottombar(img_area *pimgarea);

    void set_instruction(int tool_num);
protected:
    img_area *pimgarea;

    Glib::RefPtr< Gdk::Pixbuf > icon_pix, zoom_out_pix, zoom_in_pix;

    Gtk::Label guide_label;
    Gtk::Entry size_entry;
    Gtk::Button zoom_in_btn, zoom_out_btn;
    Gtk::Image zoom_in_img, zoom_out_img;

    Glib::ustring text, text_buffer;
    int inp_int;

    void set_text_proper();
    void zoom_in();
    void zoom_out();

    Glib::ustring percent_to_string(int &percent);
    Glib::ustring percent_to_string(double &percent);
};


#endif //GTK_MAIN_BOTTOMBAR_H
