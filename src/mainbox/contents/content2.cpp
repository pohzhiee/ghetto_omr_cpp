//
// Created by poh on 8/17/17.
//

//#include "contents.h"

//all classes are nested and hence are declared here
#include "content2.h"

#include "content2/image/img_area.h"
#include "content2/image/bottombar.h"
#include "content2/layer/LayerBox.h"
#include "content2/tools/worktools.h"




content2::content2(){
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    imgarea = Gtk::manage(new img_area(this));

    layer_box = Gtk::manage(new LayerBox(this));
//    imgarea = Gtk::manage(new img_area(this));


    btm_bar = Gtk::manage(new bottombar(this));
    worktools_box =  Gtk::manage(new worktools(this));

    //pack imgarea into a scrolledwindow with custom container for border
    //must be done after imgarea is created, otherwise segmentation fault
    img_scrolledwin = add_img_to_scrolled_win();

    //pack scrolled window and bottom bar into 1 container
    img_box = Gtk::manage(new Gtk::Box());
    img_box->set_orientation(Gtk::ORIENTATION_VERTICAL);
    img_box->pack_start(*img_scrolledwin,Gtk::PACK_EXPAND_WIDGET);
    img_box->pack_start(*btm_bar,Gtk::PACK_SHRINK);

    //pack into main content
    pack_start(*img_box,Gtk::PACK_EXPAND_WIDGET);
    pack_start(right_bar,Gtk::PACK_SHRINK);

    right_bar.set_orientation(Gtk::ORIENTATION_VERTICAL);
    right_bar.pack_start(*worktools_box,Gtk::PACK_SHRINK);
    right_bar.pack_start(*layer_box,Gtk::PACK_EXPAND_WIDGET);
};

//btm bar functions
/**
 * Sets the instruction label at the bottom
 * @param tool_count
 */
void content2::set_instruction_btm(int &tool_count)
{
    btm_bar->set_instruction(tool_count);
};

void content2::resize_img()
{
    imgarea->resize_img();
}

//general functions
Gtk::ScrolledWindow* content2::add_img_to_scrolled_win()
{
    scrolledwin = Gtk::manage(new Gtk::ScrolledWindow());

    borderbox = Gtk::manage(new img_border_box(*imgarea));
    borderbox->set_valign(Gtk::ALIGN_CENTER);

    box1 = Gtk::manage(new Gtk::Box());
    box1->set_name("content2_img_padding");
    box1->pack_start(*borderbox,Gtk::PACK_EXPAND_PADDING);
    scrolledwin->add(*box1);
    scrolledwin->set_name("content2_img_scrollable");

    return scrolledwin;
}



