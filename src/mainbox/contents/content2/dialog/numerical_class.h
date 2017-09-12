//
// Created by poh on 8/22/17.
//

#ifndef GTK_DIALOG_TESTING_H
#define GTK_DIALOG_TESTING_H

#include "_dialog_qn.h"
#include "../../../../data/numerical_data.h"

class numerical_class: public dialog_qn {
protected:
    std::shared_ptr<selection_data> p_data;
    Gtk::ComboBox *shape_combobox, *orientation_combobox;
    Gtk::Entry *col_entry, *row_entry, *qn_entry, *digit_entry;

public:
    numerical_class(std::shared_ptr<selection_data> p_data = nullptr);
    std::shared_ptr<selection_data> save_values() override;
};


#endif //GTK_DIALOG_TESTING_H
