//
// Created by poh on 8/23/17.
//

#ifndef GTK_MAIN_SELECTION_DATA_H
#define GTK_MAIN_SELECTION_DATA_H
#include <glibmm/fileutils.h>
#include <gdkmm/rgba.h>
#include <vector>
#include <unordered_map>

#include "coords_data.h"


class selection_data {
public:
    coords init_coord,final_coord;
    rect_coords rect;
    Gdk::RGBA border_color;
    Glib::ustring layer_name;
    bool isnum, ismcq, ismarker;
    selection_data();
    virtual void print_params();
    virtual std::unordered_map<std::string, Glib::ustring> get_param_map();

};

class numerical_data : public selection_data{
public:
    numerical_data();
    void print_params() override;
    Glib::ustring bubble_shape,orientation;
    Glib::ustring no_col,no_row,no_qn,no_digit;

};

class mcq_data : public selection_data{
public:
    mcq_data();
    void print_params() override;
    std::unordered_map<std::string, Glib::ustring> get_param_map() override;
    Glib::ustring bubble_shape,orientation;
    Glib::ustring no_col,no_row,no_qn;
    Gdk::RGBA border_color;
};

class marker_data : public selection_data{
public:
    marker_data();
};


#endif //GTK_MAIN_SELECTION_DATA_H
