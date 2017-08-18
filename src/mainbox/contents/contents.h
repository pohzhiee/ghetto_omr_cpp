//
// Created by poh on 8/17/17.
//

#ifndef GTK_MAIN_CONTENTS_H
#define GTK_MAIN_CONTENTS_H
#include "../mainbox.h"
#include "../../data/data.h"

class mainbox::content1 : public Gtk::Box
{
public:
    content1(mainbox *pMainBox);
protected:
    Gtk::Button btn1;
};


#include "content2/content2_imgbox.h"
class mainbox::content2 : public Gtk::Box
{
public:
    content2(mainbox *pMainBox);
protected:
    class worktools;
    worktools *worktools_box;
    class img_area;
    img_area *imgarea;
    Gtk::Box img_box2;
    content2_imgbox img_box1;

    Glib::RefPtr<Gdk::Window> window;

};



class mainbox::content3 : public Gtk::Box
{
public:
    content3(mainbox *pMainBox);
protected:
    Gtk::Button btn1;
};

class mainbox::content4 : public Gtk::Box
{
public:
    content4(mainbox *pMainBox);
protected:
    Gtk::Button btn1;
};


#endif //GTK_MAIN_CONTENTS_H
