//
// Created by poh on 9/6/17.
//

#ifndef GHETTO_OMR_NUMERICAL_DATA_H
#define GHETTO_OMR_NUMERICAL_DATA_H
#include "selection_data.h"

class numerical_data : public selection_data{
protected:
    std::unordered_map<std::string, Glib::ustring> variables;
    Gdk::RGBA border_color;
public:
    static int num_count;
    numerical_data();
    virtual ~numerical_data();

    //Virtual getters
    virtual Glib::ustring get_value_by_key(std::string key) override;
    virtual Gdk::RGBA get_color() const override;

    //Virtual setters
    virtual void set_value_by_key(std::pair<std::string,Glib::ustring> pair) override;
    virtual void set_color(Gdk::RGBA color) override;

};
#endif //GHETTO_OMR_NUMERICAL_DATA_H
