//
// Created by poh on 8/22/17.
//

#include "_dialog_qn.h"
//
// Created by poh on 8/21/17.
//
#include <iostream>
#include "../../../../functions/functions.h"

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

Gtk::Entry* dialog_qn::add_field (Glib::ustring label_string, Glib::ustring text)
{
    auto lab = Gtk::manage(new Gtk::Label(label_string));
    auto entry = Gtk::manage(new Gtk::Entry());

    entry->signal_activate().connect(sigc::mem_fun(*this, &dialog_qn::on_entry_activate));
    entry->set_text(text);

    attach(*lab,0,no_params,1,1);
    attach(*entry,1,no_params,2,1);
    no_params++;
    return entry;
}

Gtk::Entry* dialog_qn::add_int_field(Glib::ustring label_string, Glib::ustring text)
{
    text_check_results.push_back(true);
    auto label = Gtk::manage(new Gtk::Label(label_string));
    auto entry = Gtk::manage(new Gtk::Entry());
    entry->signal_activate().connect(sigc::mem_fun(*this, &dialog_qn::on_entry_activate));
    entry->signal_changed().connect(sigc::bind<Gtk::Entry*,unsigned int>(sigc::mem_fun(*this, &dialog_qn::text_check),entry,no_checkable));
    entry->set_text(text);

    attach(*label,0,no_params,1,1);
    attach(*entry,1,no_params,2,1);
    no_checkable++;
    no_params++;
    return entry;
}


void dialog_qn::add_color_selector(Gdk::RGBA color)
{
    attach(color_label,0,no_params,1,1);
    attach(m_ColorButton,1,no_params,1,1);
    attach_next_to(m_Button_Dialog,m_ColorButton,Gtk::POS_RIGHT,1,1);
    m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,&dialog_qn::on_color_button_color_set));
    m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,&dialog_qn::color_chooser_clicked));
    m_Color = color;
    m_ColorButton.set_rgba(m_Color);

    no_params++;
}


Gtk::ComboBox* dialog_qn::add_icon_combobox(Glib::ustring label, entries entry_vec,
                                  entries icon_path_vec, unsigned int icon_size, Glib::ustring input_value)
{
    if (entry_vec.size() != icon_path_vec.size())
    {
        std::cerr << "Entry array and icon path array size mismatch;";
        return nullptr;
    }
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

        //Create all rows
        int count=0;
        for (int i = 0; i<icon_vec.size();i++)
        {
            row = *(treemodel->append());
            row[columns.col_name] = entry_vec[i];
            row[columns.col_icon] = icon_vec[i];
            //Get the line number of the input variable
            entry_vec[i].uppercase()==input_value.uppercase() ? count = i : i;
        }
        //Set the active to match that of the input from data
        p_combo -> set_active(count);

        p_combo -> pack_start(columns.col_name);
        p_combo -> pack_start(columns.col_icon);

        attach(*combobox_label, 0, no_params, 1, 1);
        attach(*p_combo, 1, no_params, 2, 1);

        no_params++;
        return p_combo;
    }

}


//Signal handlers
//void dialog_qn::on_entry_activate(int j)
//{
//    auto asd = get_children();
//    if(j!=(no_checkable-1))
//    {
////        auto entry = combobox_arr[j+1].get_entry();
////        entry->grab_focus();
//        std::cout << "ACTIVATED (THIS PART NEEDS CHANGING)" << std::endl;
//    }
//    else if(j==no_checkable-1)
//    {
//        std::cout << "THE END" << std::endl;
//        m_Button_Dialog.grab_focus();
//    } else
//    {
//        std::cout << "WHAT THE FUCK" << std::endl;
//    }
//}

void dialog_qn::on_entry_activate()
{
    auto children = get_children();
    auto focus = get_focus_child();
    int count=0;
    for(int i=0; i < children.size(); i++)
    {
        children[i]==focus ? count = i : i;
    }
    if(count<no_params*2){children[count-2]->grab_focus();}
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


void dialog_qn::save_values()
{
    std::cout << "BASE CLASS GET ALL VALUES CALLED" << std::endl;
}

void dialog_qn::text_check(Gtk::Entry *p_entry, unsigned int index)
{
    std::string text = p_entry->get_text();
    bool isInteger = functions::isInteger(text);
    if(isInteger)
    {
        text_check_results[index] = true;
        p_entry->set_name("content2_dialog_default");
    }
    else
    {
        text_check_results[index] = false;
        p_entry->set_name("content2_dialog_wrong_value");
    }
/*
    int inp_int=-1;
    try {
        inp_int = std::stoi(text);
    }
    catch(std::invalid_argument& e)
    {
//        std::cerr << "INVALID ARGUMENT" << std::endl;
        text_check_results[index] = false;
        p_entry->set_name("content2_dialog_wrong_value");
    }
    catch(std::out_of_range& e){
//        std::cerr << "OUT OF RANGE" << std::endl;
        text_check_results[index] = false;
        p_entry->set_name("content2_dialog_wrong_value");
    }
    if(inp_int!=-1){
        text_check_results[index] = true;
        p_entry->set_name("content2_dialog_default");
    }
    else
    {
        text_check_results[index] = false;
        p_entry->set_name("content2_dialog_wrong_value");
    }*/
}

bool dialog_qn::text_check_all()
{
    for (auto const& value:text_check_results)
    {
        if(value == false){return false;}
    }
    return true;
}

void dialog_qn::set_coords(coords input_coords_init, coords input_coords_final)
{
    coords_init = input_coords_init;
    coords_final = input_coords_final;
}

