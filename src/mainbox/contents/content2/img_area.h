//
// Created by poh on 8/18/17.
//

#ifndef GTK_MAIN_IMGBOX_H
#define GTK_MAIN_IMGBOX_H

#include "../contents.h"
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <gdkmm/event.h>
#include <gdkmm/cursor.h>
#include <glibmm/fileutils.h>

class mainbox::content2::img_area : public Gtk::DrawingArea
{
public:
    img_area(content2 *pinp);
    virtual ~img_area();
protected:
    content2 *pContent;
    //data
    Cairo::RefPtr<Cairo::Context> context1;
    guint32 time_init,time_final,time_change;
    gdouble x_init, x_final,x_change,x_curr;
    gdouble y_init,y_final,y_change,y_curr;

    //various pointers used in functions
    Glib::RefPtr<Gdk::Pixbuf> m_image,cursor_img;
    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
    Glib::RefPtr< Gdk::Display > display;
    Glib::RefPtr< Gdk::Cursor > cursor1;
    //override functions
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_realize() override;
    bool on_enter_notify_event(GdkEventCrossing *crossing_event) override;
    void on_size_allocate(Gtk::Allocation &allocation) override;
    bool on_button_press_event(GdkEventButton* button_event) override;
    bool on_button_release_event(GdkEventButton* release_event) override;
    bool on_motion_notify_event(GdkEventMotion* motion_event) override;
//    bool on_leave_notify_event(GdkEventCrossing *crossing_event) override;

    void draw_all_rect(const Cairo::RefPtr<Cairo::Context>& cr);
};


//class mainbox::content2::img_box : public Gtk::Box
//{
//public:
//    img_box(content2 *pinp);
//    virtual ~img_area();
//    int alloc_wid, alloc_hei;
//protected:
////    content2 *pContent;
//    void on_size_allocate(Gtk::Allocation &allocation) override;
////    bool on_leave_notify_event(GdkEventCrossing *crossing_event) override;
//};


#endif //GTK_MAIN_IMGBOX_H
