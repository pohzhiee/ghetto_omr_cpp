//
// Created by poh on 8/22/17.
//

#ifndef GTK_DIALOG_MCQ_H
#define GTK_DIALOG_MCQ_H


#include "_dialog_qn.h"
#include "../../../../data/mcq_data.h"

class mcq_class : public dialog_qn {
protected:
    std::shared_ptr<selection_data> p_data;
    Gtk::ComboBox *shape_combobox, *orientation_combobox;
    Gtk::Entry *col_entry, *row_entry, *qn_entry;
public:
    mcq_class(std::shared_ptr<selection_data> input_pointer = nullptr);
    void save_values() override;

};


#endif //GTK_DIALOG_MCQ_H
