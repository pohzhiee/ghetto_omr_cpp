//
// Created by poh on 8/16/17.
//

#ifndef GTK_MAIN_GUI_MAIN_H
#define GTK_MAIN_GUI_MAIN_H

#include <gtkmm/window.h>

//#include "startup/startup.h"
#include "data.h"

class gui_main: public Gtk::Window
{
public:
    gui_main();
    virtual ~gui_main();
    void change_1();

protected:
    class startup;
    void btn1_clicked();
    void btn2_clicked();

    startup *startup_box;
    //content1 content1
    //content2 content2
    //...
    //steps steps_box
};


#endif //GTK_MAIN_GUI_MAIN_H
