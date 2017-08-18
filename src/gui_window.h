//
// Created by poh on 8/16/17.
//

#ifndef GTK_WINDOW_GUI_WINDOW_H
#define GTK_WINDOW_GUI_WINDOW_H

#include <gtkmm/window.h>
#include "data/data.h"
#include "mainbox/mainbox.h"

class gui_window: public Gtk::Window
{
public:
    gui_window();
    virtual ~gui_window();

protected:
    //forward declaration of nested classes
    mainbox gui_main_box;

    class startup;
    startup *startup_box;
    //end of forward declaration

    //change window content function declaration
    void startup_btn1_func();
    void startup_btn2_func();
};


#endif //GTK_MAIN_GUI_MAIN_H
