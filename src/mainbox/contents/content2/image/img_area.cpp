//
// Created by poh on 8/18/17.
//

#include "img_area.h"
#include <iostream>
//-----Constructors and destructors start--------

//default constructor
img_area::img_area() {
    x_init = 0;
    x_final = 0;
    x_curr = 0;
    y_init = 0;
    y_final = 0;
    y_curr = 0;
    time_init = 0;
    time_change = 0;
    time_final = 0;
    img_scale = 1;

    set_vexpand(FALSE);
    set_hexpand(FALSE);
    set_halign(Gtk::ALIGN_CENTER);
    set_valign(Gtk::ALIGN_CENTER);
    set_redraw_on_allocate(true);
    try {
        m_image = Gdk::Pixbuf::create_from_file("../img_data/test1.jpg");
    }
    catch (const Gio::ResourceError &ex) {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
        std::cerr << "Please re-check file name and path" << std::endl;
    }
    catch (const Gdk::PixbufError &ex) {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
// request for image original size.
    if (m_image)
    {
    img_height = m_image->get_height();
    img_width = m_image->get_width();
    set_size_request(img_width, img_height);
    }
}

//default destructor
img_area::~img_area()
{
};
//-----Constructors and destructors end--------

//---------Custom Functions Start-------------
//custom functions start
void img_area::draw_all_rect(const Cairo::RefPtr<Cairo::Context>& cr)
{
    for(int i=0;i<data::selections.size();i++)
    {
        cr->move_to(data::selections[i].x_init,data::selections[i].y_init);
        cr->line_to(data::selections[i].x_init,data::selections[i].y_final);
        cr->line_to(data::selections[i].x_final,data::selections[i].y_final);
        cr->line_to(data::selections[i].x_final,data::selections[i].y_init);
        cr->line_to(data::selections[i].x_init,data::selections[i].y_init);
    }
    cr->stroke();
};

void img_area::resize_img()
{
    img_scale = ((double) data::content2_img_siz)/100; //1 is 100%, 2 is 200%
    std::cout << img_scale << std::endl;
    for (int i = 0;i<data::selections.size();i++)
    {
        data::selections[i] = data::selections_abs[i] * img_scale;
    }

    if (m_image)
    {
        long new_height = lround(img_height * img_scale);
        long new_width = lround(img_width * img_scale);
        m_image = m_image->scale_simple((int) new_width,(int) new_height,Gdk::INTERP_BILINEAR);
        set_size_request((int) new_width, (int) new_height);
    }
    queue_resize();

}

//---------Custom Functions End---------------

//---------Default handler overrides start---------------
bool img_area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if (x_init!=0 && y_init!=0)
    {

        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        // Draw the image in the middle of the drawing area, or (if the image is
        // larger than the drawing area) draw the middle part of the image.
        Gdk::Cairo::set_source_pixbuf(cr, m_image, (height - m_image->get_height()) / 2,
                                      (width - m_image->get_width()) / 2);

        cr->paint();

//        cr->save();
        cr->set_line_width(2);
        cr->set_source_rgb(0,0,0);
        if (data::selections.size() !=0){draw_all_rect(cr);}
//        cr->restore();
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

        if (data::selections.size() !=0)
        {
            cr->set_line_width(2);
            cr->set_source_rgb(0,0,0);
            draw_all_rect(cr);
        }

        return true;
    }
}

void img_area::on_realize()
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
//when mouse pointer enters the area
bool img_area::on_enter_notify_event(GdkEventCrossing *crossing_event)
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

/*when mouse button is pressed
button values:
1: left  || 2: middle || 3: right
9: thumb front || 8: thumb back  (for avf gaming freak II mouse)*/
bool img_area::on_button_press_event(GdkEventButton* button_event)
{
    if (button_event->button ==1)
    {
        time_init = button_event->time;
        x_init = (button_event->x);
        y_init = button_event->y;
        std::cout << "LEFT MOUSE PRESSED" << std::endl;
    }
    return true;
}

//when button is released, follows similar rules to button press
bool img_area::on_button_release_event(GdkEventButton* release_event)
{
    if (release_event->button ==1)
    {
        time_final = release_event->time;
        x_final = release_event->x;
        y_final = release_event->y;

        data::selections.push_back(selection_box(x_init,x_final,y_init,y_final));
        data::selections_abs.push_back(selection_box(x_init/img_scale,x_final/img_scale,y_init/img_scale,y_final/img_scale));
        std::cout << "LEFT MOUSE RELEASED" << std::endl;

        time_change = time_final-time_init;
        std::cout << "X: " << x_init << '\t' << x_final << std::endl;
        std::cout << "Y: " << y_init << '\t' << y_final << std::endl;
        std::cout << "Change in time: " << time_change << std::endl;
        x_init =0;
        y_init=0;
        time_init=0;
    }
    return true;
}

//only cursor motion when left mouse is pressed is detected due to event mask of Gdk::BUTTON1_MOTION_MASK
//change mask at on_realize() function if needed
bool img_area::on_motion_notify_event(GdkEventMotion* motion_event)
{
    x_curr = motion_event->x;
    y_curr = motion_event->y;
    queue_draw();

    return true;
}
//---------Default handler overrides end---------------


