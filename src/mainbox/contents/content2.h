//
// Created by poh on 8/20/17.
//

#ifndef GHETTO_OMR_CONTENT2_H
#define GHETTO_OMR_CONTENT2_H

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include "../../data/data.h"

//all classes need to be forward declared such that no circular dependency happens
// except for custom container (img_border_box)
//so only this is declared here
#include "content2/image/img_border_box.h"

#include <gtkmm/label.h>
class layerbox;
class bottombar;
class img_area;
class worktools;
class content2 : public Gtk::Box
{
public:
    content2();

    void resize_img();
    void set_instruction_btm(int &tool_count);
protected:
    //forward declarations

    Gtk::Box *img_box, *box1;
    Gtk::ScrolledWindow *scrolledwin,*img_scrolledwin;
    img_border_box *borderbox;

    Gtk::ScrolledWindow* add_img_to_scrolled_win();

public:
    layerbox *layers;

    //class declarations
    worktools *worktools_box;
    img_area *imgarea;
    bottombar *btm_bar;

};


#endif //GHETTO_OMR_CONTENT2_H
