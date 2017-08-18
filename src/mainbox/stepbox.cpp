//
// Created by poh on 8/17/17.
//

#include "stepbox.h"

mainbox::stepbox::stepbox(mainbox *pinput){
    //set to vertical box
    pMainBox = pinput;
    set_orientation(Gtk::ORIENTATION_VERTICAL);

    //set button labels
    step1.set_label("Step1: ASD");
    step2.set_label("Step2: ASDDAS");
    step3.set_label("STEP 3:");
    step4.set_label("STEP 4: asd");

    //remove radio button indicator, leave only text
    step1.set_mode(FALSE);
    step2.set_mode(FALSE);
    step3.set_mode(FALSE);
    step4.set_mode(FALSE);

    //set relief
    auto reliefstyle = Gtk::RELIEF_NONE;
    step1.set_relief(reliefstyle);
    step2.set_relief(reliefstyle);
    step3.set_relief(reliefstyle);
    step4.set_relief(reliefstyle);

    //join all the buttons to the same group
    step2.join_group(step1);
    step3.join_group(step1);
    step4.join_group(step1);

    //connect the relevant functions
    step1.signal_toggled().connect(sigc::mem_fun(*this,&mainbox::stepbox::step1_func));
    step2.signal_toggled().connect(sigc::mem_fun(*this,&mainbox::stepbox::step2_func));
    step3.signal_toggled().connect(sigc::mem_fun(*this,&mainbox::stepbox::step3_func));
    step4.signal_toggled().connect(sigc::mem_fun(*this,&mainbox::stepbox::step4_func));

    //set the names for styling
    Glib::ustring name = "step_button";
    step1.set_name(name);
    step2.set_name(name);
    step3.set_name(name);
    step4.set_name(name);

    //add to the box
    pack_start(step1,Gtk::PackOptions::PACK_SHRINK);
    pack_start(step2,Gtk::PackOptions::PACK_SHRINK);
    pack_start(step3,Gtk::PackOptions::PACK_SHRINK);
    pack_start(step4,Gtk::PackOptions::PACK_SHRINK);
}

//functions to call mainbox to change the contents
void mainbox::stepbox::step1_func()
{
    pMainBox->set_content1();
}

void mainbox::stepbox::step2_func()
{
    pMainBox->set_content2();
}

void mainbox::stepbox::step3_func()
{
    pMainBox->set_content3();
}

void mainbox::stepbox::step4_func()
{
    pMainBox->set_content4();
}
