//
// Created by poh on 8/18/17.
//

#ifndef GTK_MAIN_CONTENT2_IMGBOX_H
#define GTK_MAIN_CONTENT2_IMGBOX_H

#include <gtkmm/box.h>

class content2_imgbox: public Gtk::Box
{
public:
    content2_imgbox();
    virtual ~content2_imgbox();

    void set_child_widget(Gtk::Widget &child);
protected:
    //Parameters
    const int border_width = 3;

    //Overrides
    Gtk::SizeRequestMode get_request_mode_vfunc() const override;
    void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
    void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const override;
    void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
    void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const override;
    void on_size_allocate(Gtk::Allocation& allocation) override;

    void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data) override;

    void on_add(Gtk::Widget* child) override;
    void on_remove(Gtk::Widget* child) override;
    GType child_type_vfunc() const override;

    //objects
    Gtk::Widget *child;
//    void on_size_allocate(Gtk::Allocation& allocation) override;
//    void on_add(Gtk::Widget* child) override;
//    void on_realize() override;

};

#endif //GTK_MAIN_CONTENT2_IMGBOX_H
