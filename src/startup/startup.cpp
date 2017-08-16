//
// Created by poh on 8/16/17.
//

#include "startup.h"
#include <iostream>
//constructor functions
//default constructor:
gui_main::startup::startup(gui_main *pinput)
{
    //box object settings
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    gui_main *pMain = pinput;
    //box content start
    //set button label strings
    btn1_label = "NEW";
    btn2_label = "OPEN";

    //set button labels
    btn1.set_label(btn1_label);
    btn2.set_label(btn2_label);

    //connect respective functions
    btn1.signal_clicked().connect(sigc::bind<gui_main*>(sigc::mem_fun(*this, &gui_main::startup::btn1_clicked), pMain) );
    btn2.signal_clicked().connect(sigc::bind<gui_main*>(sigc::mem_fun(*this, &gui_main::startup::btn2_clicked), pMain) );
    //box content end

    //add contents to the box
    pack_start(btn1,Gtk::PackOptions::PACK_SHRINK);
    pack_start(btn2,Gtk::PackOptions::PACK_SHRINK);
}
//constructor functions end

//destructor functions
gui_main::startup::~startup()
{
}

//destructor functions end

//button functions start
//button1 function
void gui_main::startup::btn1_clicked(gui_main *pinp)
{
    (*pinp).btn1_clicked();
    std::cout << "btn1 clicked" << std::endl;
}

//button2 function

void gui_main::startup::btn2_clicked(gui_main *pinp) {
    (*pinp).btn2_clicked();
    std::cout << "btn2 clicked" << std::endl;
}
//button functions end