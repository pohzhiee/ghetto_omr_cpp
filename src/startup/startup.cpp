//
// Created by poh on 8/16/17.
//

#include "startup.h"
//constructor functions
//default constructor:
gui_window::startup::startup(gui_window *pinput)
{
    //box object settings
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    gui_window *pMain = pinput;

    //set button label strings
    btn1_label = "NEW";
    btn2_label = "OPEN";

    //set button labels
    btn1.set_label(btn1_label);
    btn2.set_label(btn2_label);

    //set button styles
    btn1.set_name("startup_buttons");
    btn2.set_name("startup_buttons");


    //connect respective functions
    btn1.signal_clicked().connect(sigc::bind<gui_window*>(sigc::mem_fun(*this, &gui_window::startup::btn1_clicked), pMain) );
    btn2.signal_clicked().connect(sigc::bind<gui_window*>(sigc::mem_fun(*this, &gui_window::startup::btn2_clicked), pMain) );
    //box content end

    //add contents to the box
    pack_start(btn1,Gtk::PackOptions::PACK_SHRINK);
    pack_start(btn2,Gtk::PackOptions::PACK_SHRINK);
}
//constructor functions end

//destructor functions
gui_window::startup::~startup()
{
}

//destructor functions end

//button functions start
//button1 function
void gui_window::startup::btn1_clicked(gui_window *pinp)
{
    (*pinp).startup_btn1_func();
    std::cout << "btn1 clicked" << std::endl;
}

//button2 function

void gui_window::startup::btn2_clicked(gui_window *pinp) {
    (*pinp).startup_btn2_func();
    std::cout << "btn2 clicked" << std::endl;
}
//button functions end