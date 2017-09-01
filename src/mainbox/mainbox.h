//
// Created by poh on 8/17/17.
//

#ifndef GTK_MAIN_GUI_MAIN_H
#define GTK_MAIN_GUI_MAIN_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include "contents/content2.h"



class stepbox;
class content1;
class content3;
class content4;
class mainbox : public Gtk::Box
{
public:
    mainbox();
    virtual ~mainbox();


    void set_content1();
    void set_content2();
    void set_content3();
    void set_content4();
protected:
    //forward declarations of nested classes
    stepbox *step_box;

    content1 *content1_box;
    content3 *content3_box;
    content4 *content4_box;

    std::shared_ptr<Gtk::Widget> p_current_content;
    Gtk::Widget *curr_content;
    Gtk::Widget **p_curr;
    content2 *content2_box;
//
    std::shared_ptr<stepbox> p_step_box;
//
//    std::shared_ptr<content1> p_content1_box;
//    std::shared_ptr<content2> p_content2_box;
//    std::shared_ptr<content3> p_content3_box;
//    std::shared_ptr<content4> p_content4_box;


};


#endif //GTK_MAIN_GUI_MAIN_H
