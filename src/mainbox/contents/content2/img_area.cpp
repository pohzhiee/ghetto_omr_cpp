//
// Created by poh on 8/18/17.
//

#include "img_area.h"
#include <iostream>

mainbox::content2::img_area::img_area(content2 *pinp)
{

//    pContent = pinp;
    set_name("image_box");
    set_vexpand(FALSE);
    set_hexpand(FALSE);
    set_halign(Gtk::ALIGN_CENTER);
    set_valign(Gtk::ALIGN_CENTER);
    try
    {
        m_image = Gdk::Pixbuf::create_from_file("../img_data/omsoval2c.jpg");
    }
    catch(const Gio::ResourceError& ex)
    {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    }
    catch(const Gdk::PixbufError& ex)
    {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
//     Show at least a quarter of the image.
    if (m_image)
        set_size_request(m_image->get_width()/2, m_image->get_height()/2);
}

mainbox::content2::img_area::~img_area()
{
};

bool mainbox::content2::img_area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if (!m_image)
        return false;

    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // Draw the image in the middle of the drawing area, or (if the image is
    // larger than the drawing area) draw the middle part of the image.
    int a = (width - m_image->get_width())/2;
    int b = (height - m_image->get_height())/2;
    Gdk::Cairo::set_source_pixbuf(cr, m_image,a, b);
    cr->paint();

    return true;
}

bool mainbox::content2::img_area::on_enter_notify_event(GdkEventCrossing *crossing_event)
{
    if(!m_image)
        return false;
    try
    {
        cursor_img = Gdk::Pixbuf::create_from_file("../icons/cs-network.svg",20,20,FALSE);
    }
    catch(const Gio::ResourceError& ex)
    {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    }
    catch(const Gdk::PixbufError& ex)
    {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
    display = get_display();
    cursor1 = Gdk::Cursor::create(display,cursor_img,0,0);
    m_refGdkWindow->set_cursor(cursor1);
    gdouble a = (*crossing_event).x;
    gdouble b = (*crossing_event).y;
    std::cout << a << std::endl << b << std::endl << "------" << std::endl;
    return true;

}


void mainbox::content2::img_area::on_realize()
{
    set_realized();
    std::cout << "Realized" << std::endl;
    if(!m_refGdkWindow)
    {
        //Create the GdkWindow:

        GdkWindowAttr attributes;
        memset(&attributes, 0, sizeof(attributes));

        Gtk::Allocation allocation = get_allocation();

        //Set initial position and size of the Gdk::Window:
        attributes.x = allocation.get_x();
        attributes.y = allocation.get_y();
        attributes.width = allocation.get_width();
        attributes.height = allocation.get_height();

        attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK | Gdk::ENTER_NOTIFY_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;

        m_refGdkWindow = Gdk::Window::create(get_parent_window(), &attributes,
                                             GDK_WA_X | GDK_WA_Y);
        set_window(m_refGdkWindow);

        //make the widget receive events
        m_refGdkWindow->set_user_data(gobj());
    }


}