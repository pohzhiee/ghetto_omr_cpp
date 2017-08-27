//
// Created by poh on 8/19/17.
//

#include "bottombar.h"
#include <iostream>



bottombar::bottombar(content2 *p_inp)
{
    p_content2 = p_inp;
    guide_label = Gtk::Label("ASD");
    //settings for zoom in button
    zoom_in_btn = Gtk::Button();
    zoom_in_pix = Gdk::Pixbuf::create_from_file("../icons/zoom-in.svg",20,20,TRUE);
    zoom_in_img = Gtk::Image(zoom_in_pix);
    zoom_in_btn.set_image(zoom_in_img);
    zoom_in_btn.signal_clicked().connect(sigc::mem_fun(*this,&bottombar::zoom_in));


    //settings for zoom out button
    zoom_out_btn = Gtk::Button();
    zoom_out_pix = Gdk::Pixbuf::create_from_file("../icons/zoom-out.svg",20,20,TRUE);
    zoom_out_img = Gtk::Image(zoom_out_pix);
    zoom_out_btn.set_image(zoom_out_img);
    zoom_out_btn.signal_clicked().connect(sigc::mem_fun(*this,&bottombar::zoom_out));

    //settings for text entry box
    size_entry = Gtk::Entry();
    size_entry.set_max_length(8);
    text_buffer = percent_to_string(data::content2_img_siz); //set initial text as buffer
    icon_pix = Gdk::Pixbuf::create_from_file("../icons/magnifier.svg",20,20,TRUE);
    size_entry.set_icon_from_pixbuf(icon_pix,Gtk::ENTRY_ICON_PRIMARY);
    size_entry.set_editable(true);
    size_entry.set_text(text_buffer);
//    size_entry.signal_activate().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this,&bottombar::set_text_proper),size_entry.get_text()));
    size_entry.signal_activate().connect(sigc::mem_fun(*this,&bottombar::set_text_proper));

    pack_start(zoom_out_btn,Gtk::PACK_SHRINK);
    pack_start(size_entry,Gtk::PACK_SHRINK);
    pack_start(zoom_in_btn,Gtk::PACK_SHRINK);
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
        p_content2 -> resize_img();
    }
}

void bottombar::zoom_in()
{
    data::content2_img_siz *=2;
    this->size_entry.set_text(percent_to_string(data::content2_img_siz));
    p_content2 -> resize_img();

}

void bottombar::zoom_out()
{
    data::content2_img_siz /=2;
    this->size_entry.set_text(percent_to_string(data::content2_img_siz));
    p_content2 -> resize_img();

}

Glib::ustring bottombar::percent_to_string(int &percent)
{
    return (std::to_string(percent) + "%");
};

Glib::ustring bottombar::percent_to_string(double &percent)
{
    int temp =(int)round(percent);
    return (std::to_string(temp) + "%");
};


void bottombar::set_instruction(int tool_num)
{
    switch (tool_num){
        case 0:
        {
            guide_label.set_label("TOOL 0 SELECTED");
            break;
        }
        case 1:
        {
            guide_label.set_label("TOOL 1 SELECTED");
            break;
        }
        case 2:
        {
            guide_label.set_label("TOOL 2 SELECTED");
            break;
        }
        case 3:
        {
            guide_label.set_label("TOOL 3 SELECTED");
            break;
        }
        default:
        {
            std::cout << "UNKNOWN SELECTED" << std::endl;
            guide_label.set_label("UNKNOWN TOOL SELECTED");
            break;
        }
    }
    queue_draw();

}