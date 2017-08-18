//
// Created by poh on 8/17/17.
//

#ifndef GTK_MAIN_GUI_MAIN_H
#define GTK_MAIN_GUI_MAIN_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>



class mainbox : public Gtk::Box
{
public:
    mainbox();
    virtual ~mainbox();
protected:
    //forward declarations of nested classes
    class stepbox;
    stepbox *step_box;

    class content1;
    content1 *content1_box;
    class content2;
    content2 *content2_box;
    class content3;
    content3 *content3_box;
    class content4;
    content4 *content4_box;

    Gtk::Widget *curr_content;

    void set_content1();
    void set_content2();
    void set_content3();
    void set_content4();
};


#endif //GTK_MAIN_GUI_MAIN_H
