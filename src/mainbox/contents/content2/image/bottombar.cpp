//
// Created by poh on 8/19/17.
//

#include "bottombar.h"
#include <iostream>



bottombar::bottombar(img_area *pimg_area)
{
    pimgarea = pimg_area;
    text_buffer = percent_to_string(data::content2_img_siz); //set initial text as buffer
    guide_label = Gtk::Label("ASD");
    size_entry = Gtk::Entry();
    size_entry.set_icon_from_icon_name("zoom",Gtk::ENTRY_ICON_SECONDARY);
    size_entry.set_editable(true);
    size_entry.set_text(text_buffer);
//    size_entry.signal_activate().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this,&bottombar::set_text_proper),size_entry.get_text()));
    size_entry.signal_activate().connect(sigc::mem_fun(*this,&bottombar::set_text_proper));


    pack_start(size_entry,Gtk::PACK_SHRINK);
    pack_start(guide_label,Gtk::PACK_EXPAND_WIDGET);

};


void bottombar::set_text_proper()
{
    text = this ->size_entry.get_text();
    try {
        inp_int = std::stoi(text);
    }
    catch(std::invalid_argument& e){
        text = text_buffer;
        std::cout << "INVALID ARGUMENT" << std::endl;
        // if no conversion could be performed
    }
    catch(std::out_of_range& e){
        text = text_buffer;
        // if the converted value would fall out of the range of the result type
        // or if the underlying function (std::strtol or std::strtoull) sets errno
        // to ERANGE.
        std:: cout << "OUT OF RANGE" << std::endl;
    }
    if(inp_int){
        this->size_entry.set_text(percent_to_string(inp_int));
        text_buffer = text;
        data::content2_img_siz = inp_int;
        pimgarea -> resize_img();
    }
}

Glib::ustring bottombar::percent_to_string(int &percent)
{
    return (std::to_string(percent) + "%");
};