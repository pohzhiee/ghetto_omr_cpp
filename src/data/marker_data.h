//
// Created by poh on 9/6/17.
//

#ifndef GHETTO_OMR_MARKER_DATA_H
#define GHETTO_OMR_MARKER_DATA_H
#include "selection_data.h"
class marker_data : public selection_data{
protected:
    std::unordered_map<std::string, Glib::ustring> variables;
    Gdk::RGBA border_color;
    const long index;
public:
    static int marker_count;
    marker_data();
    virtual ~marker_data();

    //Virtual getters
    virtual Glib::ustring get_value_by_key(std::string key) override;
    virtual Gdk::RGBA get_color() const override;
    virtual long get_index() const override;

    //Virtual setters
    virtual void set_value_by_key(std::pair<std::string,Glib::ustring> pair) override;
    virtual void set_color(Gdk::RGBA color) override;
};


#endif //GHETTO_OMR_MARKER_DATA_H
