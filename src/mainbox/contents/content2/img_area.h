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
    int alloc_wid, alloc_hei;
protected:
    content2 *pContent;

    Glib::RefPtr<Gdk::Pixbuf> m_image,cursor_img;
    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
    Glib::RefPtr< Gdk::Display > display;
    Glib::RefPtr< Gdk::Cursor > cursor1;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    void on_realize() override;
    bool on_enter_notify_event(GdkEventCrossing *crossing_event) override;
    void on_size_allocate(Gtk::Allocation &allocation) override;
//    bool on_leave_notify_event(GdkEventCrossing *crossing_event) override;
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
