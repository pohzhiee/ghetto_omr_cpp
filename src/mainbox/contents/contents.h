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


#include "content2/image/img_area.h"
#include "content2/image/img_scrollable.h"
#include "content2/image/bottombar.h"
#include "content2/tools/worktools.h"
class mainbox::content2 : public Gtk::Box
{
public:
    content2(mainbox *pMainBox);
protected:
    worktools *worktools_box;
    img_area *imgarea;
    img_scrollable *img_scroll;
    bottombar *btm_bar;

    Glib::RefPtr<Gdk::Window> window;
    Gtk::Box *img_box;

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
