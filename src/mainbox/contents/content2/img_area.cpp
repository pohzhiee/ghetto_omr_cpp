//
// Created by poh on 8/18/17.
//

#include "img_area.h"
#include <iostream>

mainbox::content2::img_area::img_area(content2 *pinp)
{
    x_init = 0;
    x_change = 0;
    x_final = 0;
    x_curr = -1;
    y_init = 0;
    y_change = 0;
    y_final = 0;
    y_curr = -1;
    time_init =0;
    time_change = 0;
    time_final = 0;

    pContent = pinp;
    set_name("img_area");
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
        set_size_request(m_image->get_width(), m_image->get_height());
}


mainbox::content2::img_area::~img_area()
{
};

bool mainbox::content2::img_area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if (x_curr!=-1 && y_curr!=-1)
    {

        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        // Draw the image in the middle of the drawing area, or (if the image is
        // larger than the drawing area) draw the middle part of the image.
        Gdk::Cairo::set_source_pixbuf(cr, m_image, (height - m_image->get_height()) / 2,
                                      (width - m_image->get_width()) / 2);

        cr->paint();

        cr->save();
        cr->set_line_width(2);
        cr->set_source_rgb(0,0,0);
        if (data::layers.size() !=0){draw_all_rect(cr);}
        cr->stroke();
        cr->restore();
        cr->save();
        cr->set_line_width(2);
        cr->set_source_rgb(0,0,0);
        cr->move_to(x_init,y_init);
        cr->line_to(x_init,y_curr);
        cr->line_to(x_curr,y_curr);
        cr->line_to(x_curr,y_init);
        cr->line_to(x_init,y_init);
        cr->stroke();
        cr->restore();
        return true;
    }
    else {
        if (!m_image)
            return false;

        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        // Draw the image in the middle of the drawing area, or (if the image is
        // larger than the drawing area) draw the middle part of the image.
        Gdk::Cairo::set_source_pixbuf(cr, m_image, (height - m_image->get_height()) / 2,
                                      (width - m_image->get_width()) / 2);
        cr->paint();

        return true;
    }
}

void mainbox::content2::img_area::on_realize()
{
    set_realized();
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

        attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK | Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK
                                | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::BUTTON1_MOTION_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;

        m_refGdkWindow = Gdk::Window::create(get_parent_window(), &attributes,
                                             GDK_WA_X | GDK_WA_Y);
        set_window(m_refGdkWindow);

        //make the widget receive events
        m_refGdkWindow->set_user_data(gobj());
    }


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

void mainbox::content2::img_area::on_size_allocate(Gtk::Allocation &allocation)
{
    //Do something with the space that we have actually been given:
    //(We will not be given heights or widths less than we have requested, though
    //we might get more)
    //Use the offered allocation for this container:
    set_allocation(allocation);

    if(m_refGdkWindow)
    {
        m_refGdkWindow->move_resize( allocation.get_x(), allocation.get_y(),
                                     allocation.get_width(), allocation.get_height() );
    }
}

bool mainbox::content2::img_area::on_button_press_event(GdkEventButton* button_event)
{
    if (button_event->button ==1)
    {
        time_init = button_event->time;
        x_init = button_event->x;
        y_init = button_event->y;
        std::cout << "LEFT MOUSE PRESSED" << std::endl;
    }
    return true;
}

bool mainbox::content2::img_area::on_button_release_event(GdkEventButton* release_event)
{
//    gdouble x_coord = (*release_event).x;
//    gdouble y_coord = (*release_event).y;
//    guint btn_pressed = (*release_event).button;
//    std::cout << "ASD" << std::endl;
    if (release_event->button ==1)
    {
        time_final = release_event->time;
        x_final = release_event->x;
        y_final = release_event->y;


        data::layers.push_back(selection_box(x_init,x_final,y_init,y_final));
        std::cout << "LEFT MOUSE RELEASED" << std::endl;

        time_change = time_final-time_init;
        x_change = x_final-x_init;
        y_change = y_final-y_init;
        std::cout << "X: " << x_init << '\t' << x_final << std::endl;
        std::cout << "Y: " << y_init << '\t' << y_final << std::endl;
        std::cout << "Change in time: " << time_change << std::endl;
        x_init =0;
        y_init=0;
        time_init=0;
    }
    return true;
}

bool mainbox::content2::img_area::on_motion_notify_event(GdkEventMotion* motion_event)
{
    //note that this motion event only accepts motion during left click due to the event mask being set to button1 only
    GdkEventType type = motion_event->type;
    x_curr = motion_event->x;
    y_curr = motion_event->y;
    time_change = motion_event->time -time_init;
    queue_draw();

    return true;
}

void mainbox::content2::img_area::draw_all_rect(const Cairo::RefPtr<Cairo::Context>& cr)
{
    for(int i=0;i<data::layers.size();i++)
    {
        cr->move_to(data::layers[i].x_init,data::layers[i].y_init);
        cr->line_to(data::layers[i].x_init,data::layers[i].y_final);
        cr->line_to(data::layers[i].x_final,data::layers[i].y_final);
        cr->line_to(data::layers[i].x_final,data::layers[i].y_init);
        cr->line_to(data::layers[i].x_init,data::layers[i].y_init);
//        std::cout << data::layers[i].x_init << '\t' << data::layers[i].x_final;
    }
    std::cout << "DRAWN";
};
