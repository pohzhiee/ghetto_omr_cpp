//
// Created by poh on 8/22/17.
//

#ifndef GTK_DIALOG_DIALOG_QN_BASE_H
#define GTK_DIALOG_DIALOG_QN_BASE_H

#include <gtkmm/comboboxtext.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/colorchooserdialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/liststore.h>
#include <glibmm/ustring.h>
#include <gdkmm/pixbuf.h>
#include "../../../../data/data.h"


class dialog_qn: public Gtk::Grid  {
protected:
    //array declaration
    typedef std::vector<Glib::ustring> entries;

    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

        ModelColumns()
        { add(col_name); add(col_icon);}

        Gtk::TreeModelColumn<Glib::ustring> col_name;
        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf>> col_icon;
    };

public:
    dialog_qn();
    virtual ~dialog_qn();

    virtual void save_values() = 0;

    bool text_check_all();
    void set_coords(coords input_coords_init, coords input_coords_final);

protected:
    //data
    unsigned int no_params, no_checkable;
    Gdk::RGBA m_Color;
    coords coords_init, coords_final;
    Gtk::Entry *layer_entry;
    std::vector<bool> text_check_results;

    //Signal Handlers
    void on_entry_activate();
    void color_chooser_clicked();
    void on_color_button_color_set();

    //Adding field functions
    Gtk::Entry* add_field (Glib::ustring label_string, Glib::ustring text = "");
    Gtk::Entry* add_int_field(Glib::ustring label, Glib::ustring text = "");
    void add_color_selector(Gdk::RGBA color);
    Gtk::ComboBox* add_icon_combobox(Glib::ustring label, entries entry_vec, entries icon_path_vec, unsigned int icon_size, Glib::ustring value);

    //custom functions
    void text_check(Gtk::Entry *p_entry, unsigned int index);


    //Child Widgets:

    Gtk::Label color_label;
    Gtk::ColorButton m_ColorButton;
    Gtk::Button m_Button_Dialog;
};


#endif //GTK_DIALOG_DIALOG_QN_BASE_H
