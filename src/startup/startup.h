//
// Created by poh on 8/16/17.
//

#ifndef GTK_MAIN_STARTUP_H
#define GTK_MAIN_STARTUP_H

#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/widget.h>
#include <gtkmm/messagedialog.h>
#include "../data.h"
#include "../gui_main.h"

class gui_main::startup: public Gtk::Box
{
public:
    startup(gui_main *pMain);
    virtual ~startup();

protected:
    Glib::ustring btn1_label, btn2_label;
    Gtk::Button btn1, btn2;
    void btn1_clicked(gui_main *pinp);
    void btn2_clicked(gui_main *pinp);

};


#endif //GTK_MAIN_STARTUP_H
