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
protected:
//    selection_data();
    selection_data();
public:
    coords init_coord,final_coord;
    rect_coords rect;
    Gdk::RGBA border_color;
    Glib::ustring layer_name;
    bool isnum, ismcq, ismarker;
    virtual void print_params();
//    virtual void set_params(Gdk::RGBA color_inp, coords init, coords final, std::vector<Glib::ustring>);
//    virtual void set_numerical();
//    virtual void set_mcq();
//    virtual void set_marker();
    virtual std::unordered_map<std::string, Glib::ustring> get_param_map();
    virtual Gdk::RGBA get_color();

};

class numerical_data : public selection_data{
public:
    numerical_data();
    void print_params() override;
    Gdk::RGBA get_color() override;
    Glib::ustring bubble_shape,orientation;
    Glib::ustring no_col,no_row,no_qn,no_digit;

};

class mcq_data : public selection_data{
public:
    mcq_data();
    void print_params() override;
    Gdk::RGBA get_color() override;
    std::unordered_map<std::string, Glib::ustring> get_param_map() override;
    Glib::ustring bubble_shape,orientation;
    Glib::ustring no_col,no_row,no_qn;
    Gdk::RGBA border_color;
};

class marker_data : public selection_data{
public:
    marker_data();
    Gdk::RGBA get_color() override;
};


#endif //GTK_MAIN_SELECTION_DATA_H
