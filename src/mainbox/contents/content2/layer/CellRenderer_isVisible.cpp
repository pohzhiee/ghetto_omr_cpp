//
// Created by poh on 8/30/17.
//

#include <iostream>
#include "CellRenderer_isVisible.h"

CellRenderer_isVisible::CellRenderer_isVisible()
        :
        Glib::ObjectBase      (typeid(CellRenderer_isVisible)),
        Gtk::CellRenderer     (),
        property_activatable_ (*this, "activatable", true),
        property_active_      (*this, "active",      false),
        icon(Gdk::Pixbuf::create_from_file("../icons/eye.svg",20,20,true))
{
    property_mode() = Gtk::CellRendererMode::CELL_RENDERER_MODE_ACTIVATABLE;
    property_xpad() = 2;
    property_ypad() = 2;
}

CellRenderer_isVisible::~CellRenderer_isVisible()
{}

Glib::PropertyProxy<bool> CellRenderer_isVisible::property_active()
{
    return property_active_.get_proxy();
}

CellRenderer_isVisible::SignalToggled& CellRenderer_isVisible::signal_toggled()
{
    return signal_toggled_;
}

enum { TOGGLE_WIDTH = 25 };

void CellRenderer_isVisible::get_preferred_width_vfunc(Gtk::Widget& /* widget */,
                                                     int& minimum_width, int& natural_width) const
{
    const unsigned int xpad = property_xpad();
    const int calc_width = xpad * 2 + TOGGLE_WIDTH;
    minimum_width = calc_width;
    natural_width = calc_width;
}

void CellRenderer_isVisible::get_preferred_width_for_height_vfunc(Gtk::Widget& widget,
                                                                int /* height */, int& minimum_width, int& natural_width) const
{
    get_preferred_width_vfunc(widget, minimum_width, natural_width);
}

void CellRenderer_isVisible::get_preferred_height_vfunc(Gtk::Widget& /* widget */,
                                                      int& minimum_height, int& natural_height) const
{
    const unsigned int ypad = property_ypad();
    const int calc_height = ypad * 2 + TOGGLE_WIDTH;
    minimum_height = calc_height;
    natural_height = calc_height;
}

void CellRenderer_isVisible::get_preferred_height_for_width_vfunc(Gtk::Widget& widget,
                                                                int /* width */, int& minimum_height, int& natural_height) const
{
    get_preferred_height_vfunc(widget, minimum_height, natural_height);
}

void CellRenderer_isVisible::render_vfunc(const ::Cairo::RefPtr<::Cairo::Context> &cr, Gtk::Widget &widget,
                                        const Gdk::Rectangle &background_area, const Gdk::Rectangle &cell_area,
                                        Gtk::CellRendererState flags)
{
    const unsigned int cell_xpad = property_xpad();
    const unsigned int cell_ypad = property_ypad();

    int width = 0, height = 0;

    GtkRequisition requisition_min, requisition_natural;
    get_preferred_size(widget, requisition_min, requisition_natural);
    width = requisition_min.width;
    height = requisition_min.height;

    width  -= cell_xpad * 2;
    height -= cell_ypad * 2;

    if(width <= 0 || height <= 0)
        return;

    auto state = Gtk::STATE_FLAG_INSENSITIVE;

    if (property_activatable_)
        state = Gtk::STATE_FLAG_NORMAL;

    if ((flags & Gtk::CELL_RENDERER_SELECTED) == Gtk::CELL_RENDERER_SELECTED)
        state = (widget.has_focus()) ? Gtk::STATE_FLAG_SELECTED : Gtk::STATE_FLAG_ACTIVE;

    if (property_active_)
        state |= Gtk::STATE_FLAG_CHECKED;

    auto style_context = widget.get_style_context();
    style_context->set_state(state);

    if ((state & Gtk::STATE_FLAG_CHECKED) == Gtk::STATE_FLAG_CHECKED)
    {
        style_context -> render_icon(cr,icon,cell_area.get_x() + cell_xpad, cell_area.get_y() + cell_ypad);
    }

}

bool CellRenderer_isVisible::activate_vfunc(GdkEvent*,
                                          Gtk::Widget&,
                                          const Glib::ustring& path,
                                          const Gdk::Rectangle&,
                                          const Gdk::Rectangle&,
                                          Gtk::CellRendererState)
{
    if(property_activatable_)
    {
        signal_toggled_(path);
        return true;
    }

    return false;
}