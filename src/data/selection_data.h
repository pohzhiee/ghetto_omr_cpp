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
    selection_data();
    coords init_coord,final_coord;
    rect_coords rect;
    static long unique_index;

public:
    bool isVisible;
    //Virtual getters
    virtual std::pair <coords,coords> get_coords();
    virtual Gdk::RGBA get_color() const=0;
    virtual Glib::ustring get_value_by_key(std::string key)=0;
    virtual long get_index() const =0;

    //Virtual setters
    virtual void set_coords(coords init_coord, coords final_coord);
    virtual void set_color(Gdk::RGBA color)=0;
    virtual void set_value_by_key(std::pair<std::string,Glib::ustring> pair)=0;

};


#endif //GTK_MAIN_SELECTION_DATA_H
