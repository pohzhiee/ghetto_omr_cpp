//
// Created by poh on 8/16/17.
//

#ifndef GTK_MAIN_STARTUP_H
#define GTK_MAIN_STARTUP_H

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/widget.h>
#include <gtkmm/cssprovider.h>
#include "../gui_window.h"
#include <iostream>

class gui_window::startup: public Gtk::Box
{
public:
    startup(gui_window *pMain);
    virtual ~startup();

protected:
    Glib::ustring btn1_label, btn2_label;
    Gtk::Button btn1, btn2;


    void btn1_clicked(gui_window *pinp);
    void btn2_clicked(gui_window *pinp);

};


#endif //GTK_MAIN_STARTUP_H
