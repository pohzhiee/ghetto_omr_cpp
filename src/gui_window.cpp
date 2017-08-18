//
// Created by poh on 8/16/17.
//

#include "gui_window.h"
#include <iostream>
#include "startup/startup.h"

gui_window::gui_window()
{
    startup_box = new startup(this);
    add(*startup_box);

    set_position(Gtk::WIN_POS_CENTER);
    show_all_children();
}

gui_window::~gui_window()
{
    delete startup_box;
}


//startup functions
void gui_window::startup_btn1_func()
{
    remove();
    data::set_val(1,2,3);
    data::print_val();
    add(gui_main_box);
    std::vector< Gtk::Widget* > list1 = gui_main_box.get_children();
    maximize();
    show_all_children();
    std::cout << "btn1 clicked, mainbox" << std::endl;
}

//button2 function
void gui_window::startup_btn2_func()
{
    std::cout << "btn2 clicked, mainbox" << std::endl;
}