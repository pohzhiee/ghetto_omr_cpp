//
// Created by poh on 8/18/17.
//

#include "imgbox.h"
#include <iostream>

mainbox::content2::imgbox::imgbox(content2 *pinp)
{
    set_name("image_box");
    pContent = pinp;
    try
    {
        m_image = Gdk::Pixbuf::create_from_file("../img_data/oms3.jpg");
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

mainbox::content2::imgbox::~imgbox()
{
};

bool mainbox::content2::imgbox::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
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
