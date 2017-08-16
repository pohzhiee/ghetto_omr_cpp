//
// Created by poh on 8/16/17.
//

#include "gui_main.h"
#include <iostream>
#include "startup/startup.h"

gui_main::gui_main()
{
    startup_box = new startup(this);
    add(*startup_box);


    show_all_children();
}

gui_main::~gui_main()
{
    delete startup_box;
}


void gui_main::btn1_clicked()
{
    std::cout << "btn1 clicked, main" << std::endl;
}

//button2 function
void gui_main::btn2_clicked()
{
    std::cout << "btn2 clicked, main" << std::endl;
}


void gui_main::change_1()
{
    std::cout << "change1 called" << std::endl;
}