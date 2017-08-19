//
// Created by poh on 8/18/17.
//

#include "worktools.h"
#include <iostream>

//constructor
worktools::worktools(img_area *inp, bottombar *pbottom){
    pbtmbar = pbottom;
    imgarea = inp;
    tool_icon_path = {icon_dir+"alienarena.svg",icon_dir+"facebook.svg",icon_dir+"live.svg",icon_dir+"darktable.svg"};
    //define toolbuttons
    //toolbutton1
    for (int i = 0; i<tool_icon_path.size();i++)
    {
        tool_btn_pixbuf.push_back(Gdk::Pixbuf::create_from_file(tool_icon_path[i],tool_width,tool_height,TRUE));
        tool_btn_img.push_back(Gtk::Image(tool_btn_pixbuf[i]));
        toolbtns.push_back(Gtk::RadioButton());
        toolbtns[i].set_image(tool_btn_img[i]);
        toolbtns[i].set_mode(FALSE);
        toolbtns[i].signal_toggled().connect(sigc::bind<int>(sigc::mem_fun(*this,&worktools::tool_func),i));
        //note that both toggled and clicked event activate when state of button change, i.e. active->inactive or inactive->active
        if (i !=0){toolbtns[i].join_group(toolbtns[0]);}
        add_to_grid(&toolbtns[i],i);
    }

}

//destructor
worktools::~worktools()
{
}

void worktools::add_to_grid(Gtk::RadioButton *inp_tool_btn,int &tool_count)
{
    attach(*inp_tool_btn,tool_count%tool_no_cols,tool_count/tool_no_cols,1,1);
}

void worktools::tool_func(int tool_count)
{
    pbtmbar->set_instruction(tool_count);
    std::cout << "ASD" << tool_count << std::endl;
}
