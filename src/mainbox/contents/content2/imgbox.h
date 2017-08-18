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
#include <glibmm/fileutils.h>

class mainbox::content2::imgbox : public Gtk::DrawingArea
{
public:
    imgbox(content2 *pinp);
    virtual ~imgbox();
protected:
    Gtk::DrawingArea imgarea;
    content2 *pContent;
    Glib::RefPtr<Gdk::Pixbuf> m_image;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};


#endif //GTK_MAIN_IMGBOX_H
