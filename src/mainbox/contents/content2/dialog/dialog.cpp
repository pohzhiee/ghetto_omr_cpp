//
// Created by poh on 8/23/17.
//

#include "dialog.h"
dialog::dialog()
{
    p_warning = std::make_shared<Gtk::MessageDialog>("Values out of bounds, please make sure all values are correct",
                                                     false,Gtk::MESSAGE_WARNING,Gtk::BUTTONS_OK,true);
    Gtk::Window *window = dynamic_cast <Gtk::Window*> (get_toplevel());
    if(window->get_is_toplevel())
    {
//        warning.set_transient_for(*window);
//        warning.set_modal(true);
//        warning.set_title("Warning: Value Error");
//        warning.set_icon_from_file("../icons/dialog-warning.png");
        p_warning->set_transient_for(*window);
        p_warning->set_title("Warning: Value Error");
    }


    set_modal(true);
    set_title("Define Selection");
    p_content_vbox = get_content_area();

    //Create array of possible selection objects
    content_arr.push_back(Gtk::manage(new mcq_class()));
    content_arr.push_back(Gtk::manage(new numerical_class()));
    content_arr.push_back(Gtk::manage(new marker_class()));

    //Create combo box for type selection (i.e. numerical answer, surface marker etc)
    response_type = Gtk::ComboBoxText(false);
    response_type.append("Multiple Choice Question (e.g. ABCDE)");
    response_type.append("Numerical Answer (e.g. 333");
    response_type.append("Surface Marker");
    response_type.signal_changed().connect(sigc::mem_fun(*this,&dialog::response_type_change));
    response_type.set_active(0);

    //Create horizontal box to pack the combo box and label together
    response_type_box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    response_type_label = Gtk::Label("SELECTION TYPE: ");
    response_type_box.pack_start(response_type_label,Gtk::PACK_SHRINK);
    response_type_box.pack_start(response_type,Gtk::PACK_SHRINK);
    response_type_box.set_halign(Gtk::ALIGN_CENTER);
//
//    //pack content into the content box of the dialog
//    p_content_vbox->pack_start(response_type_box,Gtk::PACK_SHRINK);
//    p_content_vbox->pack_start(*(content_arr[0]));

    //Add response buttons
    add_button("CANCEL", Gtk::RESPONSE_CANCEL);
    add_button("OK", Gtk::RESPONSE_OK);

    show_all_children();
}

dialog::~dialog()
{
}

void dialog::response_type_change()
{
    auto asd = p_content_vbox->get_children();
    int row_num = response_type.get_active_row_number();
    if(curr_set){
        p_content_vbox->remove(*(curr_set));
        p_content_vbox->pack_start(*(content_arr[row_num]),Gtk::PACK_SHRINK);
        curr_set = content_arr[row_num];
        p_content_vbox->show_all_children();
    }
    else
    {
        p_content_vbox->pack_start(response_type_box,Gtk::PACK_SHRINK);
        p_content_vbox->pack_start(*(content_arr[0]));
        curr_set = content_arr[0];
    }
    show_all_children();
}


void dialog::set_coords(coords input_coords_init, coords input_coords_final)
{
    coords_init = input_coords_init;
    coords_final = input_coords_final;

    for (auto &content_obj: content_arr)
    {
        content_obj->set_coords(input_coords_init, input_coords_final);
    }

};