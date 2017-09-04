//
// Created by poh on 8/30/17.
//

#ifndef GTK_TREEVIEW1_MYCELLRENDERERTOGGLE_H
#define GTK_TREEVIEW1_MYCELLRENDERERTOGGLE_H

#include <gtkmm/cellrenderer.h>
#include <giomm.h>

class CellRenderer_isVisible : public Gtk::CellRenderer
{
public:
    CellRenderer_isVisible();
    virtual ~CellRenderer_isVisible();

    Glib::PropertyProxy<bool> property_active();

    using SignalToggled = sigc::signal<void,const Glib::ustring&>;
    SignalToggled& signal_toggled();

protected:
    void get_preferred_width_vfunc(Gtk::Widget& widget,
                                   int& minimum_width, int& natural_width) const override;
    void get_preferred_width_for_height_vfunc(Gtk::Widget& widget, int height,
                                              int& minimum_width, int& natural_width) const override;
    void get_preferred_height_vfunc(Gtk::Widget& widget,
                                    int& minimum_height, int& natural_height) const override;
    void get_preferred_height_for_width_vfunc(Gtk::Widget& widget, int width,
                                              int& minimum_height, int& natural_height) const override;


    void render_vfunc(const ::Cairo::RefPtr< ::Cairo::Context >& cr,
                      Gtk::Widget& widget,
                      const Gdk::Rectangle& background_area,
                      const Gdk::Rectangle& cell_area,
                      Gtk::CellRendererState flags) override;

    bool activate_vfunc(GdkEvent *event,
                        Gtk::Widget& widget,
                        const Glib::ustring& path,
                        const Gdk::Rectangle& background_area,
                        const Gdk::Rectangle& cell_area,
                        Gtk::CellRendererState flags) override;

private:
    Glib::Property<bool> property_activatable_;
    Glib::Property<bool> property_active_;

    SignalToggled signal_toggled_;

    Glib::RefPtr<Gdk::Pixbuf> icon;
};


#endif //GTK_TREEVIEW1_MYCELLRENDERERTOGGLE_H
