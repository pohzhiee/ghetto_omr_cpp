//
// Created by poh on 8/22/17.
//

#include "_dialog_qn.h"
//
// Created by poh on 8/21/17.
//
#include <iostream>

dialog_qn::dialog_qn() :
        m_Button_Dialog("Choose Color"),
        color_label("Border Color: ")
{
    set_column_homogeneous(true);
    set_row_spacing(7);

    no_params = 0;
    no_checkable = 0;
}

dialog_qn::~dialog_qn()
{
}


//Add widget functions
void dialog_qn::add_checkable_field(Glib::ustring label_string, entries entry_vec)
{
    //add to storage arrays
    auto checkable_field_label = Gtk::manage(new Gtk::Label(label_string));

    auto comboboxtext = Gtk::manage(new Gtk::ComboBoxText(true));
    for (const Glib::ustring &entry_value : entry_vec)
    {
        comboboxtext -> append(entry_value);
    }
    comboboxtext -> set_active(0);
    connect_to_signals(comboboxtext,no_checkable);
    //Attach to the appropriate row
    attach(*checkable_field_label,0,no_params,1,1);
    attach(*comboboxtext,1,no_params,2,1);

    //add to storage arrays
    combobox_arr.push_back(comboboxtext);
    entries_arr.push_back(entry_vec);
    //Increment counters, no_params = number of entry fields, no_checkable = number of fields with text check
    // no_checkable ≤ no_params AT ALL TIMES
    no_params++;
    no_checkable++;

}

void dialog_qn::add_field (Gtk::Label *lab, Gtk::Widget *widg)
{
    attach(*lab,0,no_params,1,1);
    attach(*widg,1,no_params,2,1);
    no_params++;
}

void dialog_qn::add_color_selector()
{
    attach(color_label,0,no_params,1,1);
    attach(m_ColorButton,1,no_params,1,1);
    attach_next_to(m_Button_Dialog,m_ColorButton,Gtk::POS_RIGHT,1,1);
    m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,&dialog_qn::on_color_button_color_set));
    m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,&dialog_qn::color_chooser_clicked));
    //set initial color
    m_Color.set_red(0.0);
    m_Color.set_green(0.0);
    m_Color.set_blue(1.0);
    m_Color.set_alpha(1.0); //opaque
    m_ColorButton.set_rgba(m_Color);

    no_params++;
}


void dialog_qn::add_icon_combobox(Glib::ustring label, entries entry_vec, entries icon_path_vec, unsigned int icon_size)
{
    if (entry_vec.size() != icon_path_vec.size()) {std::cerr << "Entry array and icon path array size mismatch;";}
    else
    {
        //create necessary variables
        ModelColumns columns;
        std::vector<Glib::RefPtr<Gdk::Pixbuf>> icon_vec;
        Gtk::Label *combobox_label = Gtk::manage(new Gtk::Label(label));
        Glib::RefPtr<Gtk::ListStore> treemodel = Gtk::ListStore::create(columns);
        Gtk::ComboBox *p_combo = Gtk::manage(new Gtk::ComboBox());
        Gtk::TreeModel::Row row;

        //create array of icons
        for (auto const &value: icon_path_vec)
        {
            icon_vec.push_back(Gdk::Pixbuf::create_from_file(value, icon_size, icon_size, true));
        }

        p_combo->set_model(treemodel);

        for (int i = 0; i<icon_vec.size();i++)
        {
            row = *(treemodel->append());
            row[columns.col_name] = entry_vec[i];
            row[columns.col_icon] = icon_vec[i];
        }
        p_combo -> set_active(0);

        p_combo -> pack_start(columns.col_name);
        p_combo -> pack_start(columns.col_icon);

        attach(*combobox_label, 0, no_params, 1, 1);
        attach(*p_combo, 1, no_params, 2, 1);

        icon_combobox_arr.push_back(p_combo);
        no_params++;
    }

}


//Signal handlers
void dialog_qn::on_entry_activate(int j)
{
    if(j!=(no_checkable-1))
    {
//        auto entry = combobox_arr[j+1].get_entry();
//        entry->grab_focus();
        std::cout << "ACTIVATED (THIS PART NEEDS CHANGING)" << std::endl;
    }
    else if(j==no_checkable-1)
    {
        std::cout << "THE END" << std::endl;
        m_Button_Dialog.grab_focus();
    } else
    {
        std::cout << "WHAT THE FUCK" << std::endl;
    }
}

void dialog_qn::on_text_change(int j)
{
    text_check(j);
}

void dialog_qn::color_chooser_clicked()
{
    Gtk::ColorChooserDialog dialog("Please choose a color");
    Gtk::Window *window = dynamic_cast <Gtk::Window*> (get_toplevel());
    if(window->get_is_toplevel())
    {

        dialog.set_transient_for(*window);
    }

    //Get the previously selected color:
    dialog.set_rgba(m_Color);

    const int result = dialog.run();

    //Handle the response:
    switch(result)
    {
        case Gtk::RESPONSE_OK:
        {
            //Store the chosen color:
            m_Color = dialog.get_rgba();
            m_ColorButton.set_rgba(m_Color);
            break;
        }
        case Gtk::RESPONSE_CANCEL:
        {
            std::cout << "Cancel clicked." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Unexpected button clicked: " << result << std::endl;
            break;
        }
    }
}

void dialog_qn::on_color_button_color_set()
{
    //Store the chosen color:
    m_Color = m_ColorButton.get_rgba();
}


//Custom functions
void dialog_qn::connect_to_signals(Gtk::ComboBoxText *p_combo, int j)
{
    p_combo->signal_changed().connect(sigc::bind <int>(sigc::mem_fun(*this, &dialog_qn::on_text_change), j));
    text_checkable.push_back(j);
    auto entry = p_combo -> get_entry();
    // Alternatively you can connect to entry->signal_changed().
    if (entry)
    {
        //connect activate event (when Enter key is pressed)
        entry->signal_activate().connect(sigc::bind<int>
                                                 (sigc::mem_fun(*this,&dialog_qn::on_entry_activate),j ));
    }
    else
        std::cerr << "No Entry in combobox??? Check combobox settings" << std::endl;
}

void dialog_qn::save_values()
{
    std::cout << "BASE CLASS GET ALL VALUES CALLED" << std::endl;
}

bool dialog_qn::text_check_all()
{
    for (auto const& value:text_checkable)
    {
        if(!text_check(value)){return false;}
    }
    return true;
}

bool dialog_qn::text_check(int j)
{
    Glib::ustring text = combobox_arr[j]->get_active_text().uppercase();
    auto entry = combobox_arr[j]->get_entry();
    int i =0;
    while ( i < entries_arr[j].size() && text.compare((entries_arr[j][i]).uppercase())!=0)
        //case insensitive
    {
        i++;
    }
    if (i==entries_arr[j].size())
    {
        entry->set_name("content2_dialog_wrong_value");
        return false;
    }
    else
    {
        entry->set_name("content2_dialog_default");
        return true;
    }


}

void dialog_qn::set_coords(coords input_coords_init, coords input_coords_final)
{
    coords_init = input_coords_init;
    coords_final = input_coords_final;
}

