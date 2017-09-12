//
// Created by poh on 8/18/17.
//

#include "img_area.h"
#include "../layer/LayerBox.h"
#include <iostream>
#include <thread>
//-----Constructors and destructors start--------

//default constructor
img_area::img_area(content2 *p_content2_input) {
    p_content2 = p_content2_input;
    time_init = 0;
    time_change = 0;
    time_final = 0;
    img_scale = (data::content2_img_siz)/100;

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
        int new_height = (int) round(img_height * img_scale);
        int new_width = (int) round(img_width * img_scale);
        m_image = m_image->scale_simple( new_width, new_height,Gdk::INTERP_BILINEAR);
        set_size_request(new_width, new_height);
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
    for (auto &pair : data::selections_map)
    {
        std::shared_ptr<selection_data> &selection = pair.second;
        if(selection->isVisible){
            cr->set_line_width(2*img_scale);
            Gdk::RGBA rgba = selection->get_color();
            cr->set_source_rgb(rgba.get_red(),rgba.get_green(),rgba.get_blue());

            coords init_coord = selection->get_coords().first;
            coords final_coord = selection->get_coords().second;
            gdouble x_init = init_coord.x * img_scale;
            gdouble x_final = final_coord.x * img_scale;
            gdouble y_init = init_coord.y * img_scale;
            gdouble y_final = final_coord.y *img_scale;

            cr->move_to(x_init,y_init);
            cr->line_to(x_init,y_final);
            cr->line_to(x_final,y_final);
            cr->line_to(x_final,y_init);
            cr->line_to(x_init,y_init);
            cr->stroke();
        }
    }
};

void img_area::resize_img()
{
    img_scale = (data::content2_img_siz)/100; //1 is 100%, 2 is 200%
    std::cout << img_scale << std::endl;

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
    if (m_image)
    {
        int new_height = (int) round(img_height * img_scale);
        int new_width = (int) round(img_width * img_scale);
        m_image = m_image->scale_simple( new_width, new_height,Gdk::INTERP_BILINEAR);
        set_size_request(new_width, new_height);
    }
    queue_resize();

}

//---------Custom Functions End---------------

//---------Default handler overrides start---------------
bool img_area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if (!coords_init.iszero())
    {

        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        // Draw the image in the middle of the drawing area, or (if the image is
        // larger than the drawing area) draw the middle part of the image.
        Gdk::Cairo::set_source_pixbuf(cr, m_image, (height - m_image->get_height()) / 2,
                                      (width - m_image->get_width()) / 2);

        cr->paint();

        if (data::selections_map.size() !=0){
            draw_all_rect(cr);}
//        cr->save();
        cr->set_line_width(2*img_scale);
        cr->set_source_rgb(0,0,0);
        cr->move_to(coords_init.x,coords_init.y);
        cr->line_to(coords_init.x,coords_current.y);
        cr->line_to(coords_current.x,coords_current.y);
        cr->line_to(coords_current.x,coords_init.y);
        cr->line_to(coords_init.x,coords_init.y);
        cr->stroke();
//        cr->restore();
        return true;
    }
    else {
        if (!m_image)
            return false;

        if(data::selections_map.size()!=0){draw_all_rect(cr);}
        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        // Draw the image in the middle of the drawing area, or (if the image is
        // larger than the drawing area) draw the middle part of the image.
        Gdk::Cairo::set_source_pixbuf(cr, m_image, (height - m_image->get_height()) / 2,
                                      (width - m_image->get_width()) / 2);
        cr->paint();

        if (selection_abs.size() !=0)
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
//    std::cout << "ENTER NOTIFY EVENT:" << std::endl;
//    std::cout << a << std::endl << b << std::endl << "------" << std::endl;
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
        coords_init.x = button_event->x;
        coords_init.y = button_event->y;
//        x_init = (button_event->x);
//        y_init = button_event->y;
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
        coords_final.x = release_event->x;
        coords_final.y = release_event->y;
        if(coords_init.x == coords_final.x && coords_init.y==coords_final.y)
        {
            return false;
        }

//        std::cout << "LEFT MOUSE RELEASED, COORDS IN CURRENT SCALE: " << std::endl;
//
//        time_change = time_final-time_init;
//        std::cout << "X: " << coords_init.x << '\t' << coords_final.x << std::endl;
//        std::cout << "Y: " << coords_init.y << '\t' << coords_final.y << std::endl;
//        std::cout << "Change in time: " << time_change << std::endl;

        if(ps_dialog)
        {
            ps_dialog->set_coords(coords_init, coords_final, img_scale);
            ps_dialog->run();
        }
        else
        {
            ps_dialog = std::make_shared<dialog>();
            Gtk::Window *window = dynamic_cast <Gtk::Window *> (get_toplevel());
            if (window->get_is_toplevel()) {
                ps_dialog->set_transient_for(*window);
            }
            ps_dialog->signal_response().connect(
                    sigc::mem_fun(*this, &img_area::on_dialog_response));
            ps_dialog->set_coords(coords_init, coords_final, img_scale);
            ps_dialog->run();
        }

        coords_init = coords();
        coords_final = coords();
        time_init=0;
    }
    return true;
}


//only cursor motion when left mouse is pressed is detected due to event mask of Gdk::BUTTON1_MOTION_MASK
//change mask at on_realize() function if needed
bool img_area::on_motion_notify_event(GdkEventMotion* motion_event)
{
    coords_current.x = motion_event->x;
    coords_current.y = motion_event->y;
    queue_draw();

    return true;
}
//---------Default handler overrides end---------------

//----Dialog Handlers ---
void img_area::on_dialog_response(int response_id)
{
    std::cout << response_id
              << ", close=" << Gtk::RESPONSE_CLOSE
              << ", cancel=" << Gtk::RESPONSE_CANCEL
              << ", delete_event=" << Gtk::RESPONSE_DELETE_EVENT
              << ", ok_event=" << Gtk::RESPONSE_OK
              << std::endl;

    switch (response_id)
    {
        case Gtk::RESPONSE_CLOSE:
            break;
        case Gtk::RESPONSE_CANCEL:
            ps_dialog->hide();
            break;
        case Gtk::RESPONSE_DELETE_EVENT:
            ps_dialog.reset();
            break;
        case Gtk::RESPONSE_OK:
            on_dialog_ok_clicked();
            break;
        default:
            std::cout << "Unexpected response!" << std::endl;
            break;
    }
};

void img_area::on_dialog_ok_clicked()
{
    //Check if all the parameters are acceptable
    if((ps_dialog->current_set)->text_check_all())
    {
        std::shared_ptr<selection_data> data_ptr = ps_dialog->current_set->save_values();
        p_content2->layer_box->parent_add_row(data_ptr);
        ps_dialog.reset();
        //add coordinates to list
        selection_abs.push_back(rect_coords(coords_init,coords_final)/img_scale);
    }
    //If not all parameters are acceptable, pop up warning dialog
    else
    {
        const int response = ps_dialog->p_warning->run();

        switch (response)
        {
            case Gtk::RESPONSE_OK:
                ps_dialog->p_warning->hide();
                break;
            case Gtk::RESPONSE_DELETE_EVENT:
                ps_dialog->p_warning->hide();
                break;
            default:
                std::cerr << "Unknown button clicked" << std::endl;
                break;
        }
        ps_dialog->grab_focus();
    }
}

