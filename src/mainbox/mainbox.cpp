//
// Created by poh on 8/17/17.
//

#include "mainbox.h"
#include "contents/contents.h"
#include "stepbox.h"

mainbox::mainbox()
{
    content1_box = new content1(this);
    step_box = new stepbox(this);


    pack_start(*step_box,Gtk::PackOptions::PACK_SHRINK);
    pack_start(*content1_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    curr_content = content1_box;
}

mainbox::~mainbox()
{
}

void mainbox::set_content1()
{
    remove(*curr_content);
    pack_start(*content1_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    curr_content = content1_box;
    show_all_children();
}

void mainbox::set_content2()
{
    remove(*curr_content);
    content2_box = new content2();
    pack_start(*content2_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    curr_content = content2_box;
    show_all_children();
}

void mainbox::set_content3()
{
    remove(*curr_content);
    content3_box = new content3(this);
    pack_start(*content3_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    curr_content = content3_box;
    show_all_children();
}

void mainbox::set_content4()
{
    remove(*curr_content);
    content4_box = new content4(this);
    pack_start(*content4_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    curr_content = content4_box;
    show_all_children();
}