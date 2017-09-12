//
// Created by poh on 8/23/17.
//

#ifndef GTK_MAIN_DIALOG_H
#define GTK_MAIN_DIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/messagedialog.h>
#include "numerical_class.h"
#include "mcq_class.h"
#include "marker_class.h"
#include <memory>


class dialog : public Gtk::Dialog {
    static std::shared_ptr<selection_data> temp;
public:
    dialog(std::shared_ptr<selection_data> &p_data_input = temp);
    virtual ~dialog();

    //to access current set of parameters (e.g. numerical)
    std::shared_ptr<dialog_qn> current_set;

    dialog_qn* curr_set;

    //warning message when input parameters dont make sense
    std::shared_ptr<Gtk::MessageDialog> p_warning;

    void set_coords(coords input_coords_init, coords input_coords_final, double scale = 1.0);
protected:
    //coordinates of the selection
    coords coords_init, coords_final;

    //content box of the dialog
    Gtk::Box *p_content_vbox;

    //signal handlers
    void response_type_change();

    //widgets for getting response type
    Gtk::ComboBoxText response_type;
    Gtk::Box response_type_box;
    Gtk::Label response_type_label;

    //widgets for getting response parameters

    //list of derived classes for getting response parameters
    std::vector<dialog_qn*> content_arr;


    std::vector<std::shared_ptr<dialog_qn>> content_array;

};


#endif //GTK_MAIN_DIALOG_H
