//
// Created by poh on 8/17/17.
//

#include "mainbox.h"
#include "contents/contents.h"
#include "stepbox.h"

mainbox::mainbox()
{
    auto p_content1_box = std::make_shared<content1>(this);
    p_step_box = std::make_shared<stepbox>(this);

    content1_box = Gtk::manage(new content1(this));
    step_box = Gtk::manage(new stepbox(this));


    pack_start(*p_step_box,Gtk::PackOptions::PACK_SHRINK);
    pack_start(*p_content1_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    p_current_content = p_content1_box;
}

mainbox::~mainbox()
{
}

void mainbox::set_content1()
{
    //clear previous content
    remove(*p_current_content);
    p_current_content.reset();

    //add new content in
    auto p_content1_box = std::make_shared<content1>(this);
    pack_start(*p_content1_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    p_current_content = p_content1_box;

    show_all_children();
}

void mainbox::set_content2()
{
    //clear previous content
    remove(*p_current_content);
    p_current_content.reset();

    //add new content in
    auto p_content2_box = std::make_shared<content2>();
    pack_start(*p_content2_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    p_current_content = p_content2_box;

    show_all_children();

//    remove(*curr_content);
//    content2_box = Gtk::manage(new content2());
//    pack_start(*content2_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
//    delete(*p_curr);
//    curr_content = content2_box;
//    p_curr = &curr_content;
//    show_all_children();
}

void mainbox::set_content3()
{
    //clear previous content
    remove(*p_current_content);
    p_current_content.reset();

    //add new content in
    auto p_content3_box = std::make_shared<content3>(this);
    pack_start(*p_content3_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    p_current_content = p_content3_box;

    show_all_children();
}

void mainbox::set_content4()
{
    //clear previous content
    remove(*p_current_content);
    p_current_content.reset();

    //add new content in
    auto p_content4_box = std::make_shared<content4>(this);
    pack_start(*p_content4_box,Gtk::PackOptions::PACK_EXPAND_WIDGET);
    p_current_content = p_content4_box;

    show_all_children();
}