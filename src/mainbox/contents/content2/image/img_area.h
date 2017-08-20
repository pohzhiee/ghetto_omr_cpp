//
// Created by poh on 8/18/17.
//

#ifndef GTK_MAIN_IMGBOX_H
#define GTK_MAIN_IMGBOX_H

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <gdkmm/event.h>
#include <gdkmm/cursor.h>
#include <glibmm/fileutils.h>
#include "../../content2.h"

class img_area : public Gtk::DrawingArea
{
public:
    img_area(content2 *p_inp);
    virtual ~img_area();

    void resize_img();
protected:
    content2 *p_content2;
    //temp data
    guint32 time_init,time_final,time_change;
    gdouble x_init, x_final,x_curr;
    gdouble y_init,y_final,y_curr;

    int img_width, img_height;
    gdouble img_scale; //scale is in absolute number, no more % (e.g. 1 = 100%)
    //various pointers used in functions

    Glib::RefPtr<Gdk::Pixbuf> m_image,cursor_img;
    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
    Glib::RefPtr< Gdk::Display > display;
    Glib::RefPtr< Gdk::Cursor > cursor1;

    //custom functions
    void draw_all_rect(const Cairo::RefPtr<Cairo::Context>& cr);
//    void refresh_layers();

    //default handler overriding
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_realize() override;
    bool on_enter_notify_event(GdkEventCrossing *crossing_event) override;
    bool on_button_press_event(GdkEventButton* button_event) override;
    bool on_button_release_event(GdkEventButton* release_event) override;
    bool on_motion_notify_event(GdkEventMotion* motion_event) override;
//    bool on_leave_notify_event(GdkEventCrossing *crossing_event) override;

};




#endif //GTK_MAIN_IMGBOX_H
