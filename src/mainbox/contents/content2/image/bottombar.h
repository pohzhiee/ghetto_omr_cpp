//
//    borderbox = Gtk::manage(new img_border_box(*imgarea));

//    scrolledwin = Gtk::ScrolledWindow();
//    box1 = Gtk::Box();
//    auto paren = asd.get_parent();
//    borderbox->set_child_widget(asd);
//    auto box = Gtk::Box();

//    box1.set_name("content2_img_padding");
//    box1.pack_start(*borderbox,Gtk::PACK_EXPAND_PADDING);
//    scrolledwin.add(box1);
//    scrolledwin.set_name("content2_img_scrollable");
//
// Created by poh on 8/19/17.
//

#ifndef GTK_MAIN_BOTTOMBAR_H
#define GTK_MAIN_BOTTOMBAR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include "../../content2.h"

class bottombar : public Gtk::Box {
public:
    bottombar(content2 *p_inp);

    void set_instruction(int tool_num);
protected:
    content2 *p_content2;

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
