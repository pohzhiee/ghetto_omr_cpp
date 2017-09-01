//
// Created by poh on 8/17/17.
//

#ifndef GTK_MAIN_STEPBOX_H
#define GTK_MAIN_STEPBOX_H

#include "mainbox.h"
#include <gtkmm/radiobutton.h>

class stepbox : public Gtk::Box{
public:
    stepbox(mainbox *pinput);
    //expect pinput to be pointer to mainbox
protected:
    Gtk::RadioButton step1,step2,step3,step4;
    mainbox *pMainBox;

    void step1_func();
    void step2_func();
    void step3_func();
    void step4_func();
};

#endif //GTK_MAIN_STEPBOX_H
