//
// Created by poh on 8/23/17.
//

#include "dialog.h"
std::shared_ptr<selection_data> dialog::temp = nullptr;

dialog::dialog(std::shared_ptr<selection_data> &p_data_input) : current_set(nullptr)
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
    Glib::ustring type;
    if(p_data_input == nullptr)
    {
        content_array.push_back(std::make_shared<mcq_class>());
        content_array.push_back(std::make_shared<numerical_class>());
        content_array.push_back(std::make_shared<marker_class>());
    }
    else
    {
            type = (p_data_input->get_value_by_key("type")).uppercase();
            content_array.push_back(std::make_shared<mcq_class>(
                                            type == "MCQ" ? p_data_input : nullptr));
            content_array.push_back(std::make_shared<numerical_class>(
                    type == "NUMERICAL" ? p_data_input : nullptr));
            content_array.push_back(std::make_shared<marker_class>(
                    type == "MARKER" ? p_data_input : nullptr));
    }
    //Create combo box for type selection (i.e. numerical answer, surface marker etc)
    response_type = Gtk::ComboBoxText(false);
    response_type.append("Multiple Choice Question (e.g. ABCDE)");
    response_type.append("Numerical Answer (e.g. 333");
    response_type.append("Surface Marker");
    response_type.signal_changed().connect(sigc::mem_fun(*this,&dialog::response_type_change));

    //sets the type appropriately
    type == "MCQ" ? response_type.set_active(0) : type =="NUMERICAL" ? response_type.set_active(1) :
                                                  type == "MARKER" ? response_type.set_active(2) :
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
    int row_num = response_type.get_active_row_number();
    if(current_set){
        p_content_vbox->remove(*(current_set));
        p_content_vbox->pack_start(*(content_array[row_num]),Gtk::PACK_SHRINK);
        current_set = content_array[row_num];
        p_content_vbox->show_all_children();
    }
    else
    {
        p_content_vbox->pack_start(response_type_box,Gtk::PACK_SHRINK);
        p_content_vbox->pack_start(*(content_array[row_num]));
        current_set = content_array[row_num];
    }
    show_all_children();
}


void dialog::set_coords(coords input_coords_init, coords input_coords_final, double scale)
{
    coords_init = input_coords_init /scale;
    coords_final = input_coords_final /scale;

    for (auto &content_obj: content_array)
    {
        content_obj->set_coords(coords_init, coords_final);
    }

};