//
// Created by poh on 8/18/17.
//

#include "img_border_box.h"

//credits to
//https://developer.gnome.org/gtkmm-tutorial/stable/sec-custom-containers.html.en

img_border_box::img_border_box() : child(nullptr)
{
    set_name("content2_image_border");
    set_has_window(FALSE);
    set_redraw_on_allocate(FALSE);
//    set_child_visible(TRUE);
};

img_border_box::~img_border_box()
{
    if(child)
        child->unparent();
}

void img_border_box::set_child_widget(Gtk::Widget &child_one)
{
    child = &child_one;
    child->set_parent(*this);
}


Gtk::SizeRequestMode img_border_box::get_request_mode_vfunc() const
{
    return Gtk::SIZE_REQUEST_WIDTH_FOR_HEIGHT;
}


void img_border_box::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
    int child_minimum_width = 0;
    int child_natural_width = 0;

    if(child && child->get_visible())
        child->get_preferred_width(child_minimum_width, child_natural_width);

    //Request a width equal to the width of the widest visible child.
    minimum_width = child_minimum_width;
    natural_width = child_natural_width;
}


void img_border_box::get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const
{
    int child_minimum_height = 0;
    int child_natural_height = 0;
    int nvis_children = 0;

    if(child && child->get_visible())
    {
        ++nvis_children;
        child->get_preferred_height_for_width(width, child_minimum_height,child_natural_height);
    }

    //The allocated height will be divided equally among the visible children.
    //Request a height equal to the number of visible children times the height
    //of the highest child.
    minimum_height = nvis_children * child_minimum_height;
    natural_height = nvis_children * child_natural_height;
}


void img_border_box::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
    int child_minimum_height = 0;
    int child_natural_height = 0;
    int nvis_children = 0;

    if(child && child->get_visible())
    {
        ++nvis_children;
        child->get_preferred_height(child_minimum_height, child_natural_height);
    }
    //The allocated height will be divided equally among the visible children.
    //Request a height equal to the number of visible children times the height
    //of the highest child.
    minimum_height = nvis_children * child_minimum_height;
    natural_height = nvis_children * child_natural_height;
}

void img_border_box::get_preferred_width_for_height_vfunc(int height,
                                                       int& minimum_width, int& natural_width) const
{
    int child_minimum_width = 0;
    int child_natural_width = 0;
    int nvis_children = 0;

    //Get number of visible children.
    if(child && child->get_visible())
        ++nvis_children;
    if(nvis_children > 0)
    {
        //Divide the height equally among the visible children.
        const int height_per_child = height / nvis_children;

        if(child && child->get_visible())
            child->get_preferred_width_for_height(height_per_child,
                                                        child_minimum_width, child_natural_width);
    }

    //Request a width equal to the width of the widest child.
    minimum_width = child_minimum_width;
    natural_width = child_natural_width;
}

void img_border_box::on_size_allocate(Gtk::Allocation& allocation)
{
    //Do something with the space that we have actually been given:
    //(We will not be given heights or widths less than we have requested, though
    //we might get more.)

    //change allocation
    int x = allocation.get_x();
    int y = allocation.get_y();
    int wid = allocation.get_width();
    int hei = allocation.get_height();


    int newx = x-border_width;
    int newy = y-border_width;
    int newwid = wid+2*border_width;
    int newhei = hei+2*border_width;


    allocation.set_x(newx);
    allocation.set_y(newy);
    allocation.set_width(newwid);
    allocation.set_height(newhei);

    set_allocation(allocation);


    queue_draw_area(newx,newy,newwid,newhei);
    //Get number of visible children.
    int nvis_children = 0;
    if(child && child->get_visible())
        ++nvis_children;

    if(nvis_children <= 0)
        return;

    //Assign space to the children:
    Gtk::Allocation child_allocation_one;

    //Place the first child at original assigned location
    child_allocation_one.set_x( x );
    child_allocation_one.set_y( y );

    //Make it take up the original width:
    child_allocation_one.set_width( wid );

    if(child && child->get_visible())
    {
        //Make it take up original height
        child_allocation_one.set_height( hei);
        child->size_allocate(child_allocation_one);
    }
    else
        child_allocation_one.set_height(0);
}

void img_border_box::forall_vfunc(gboolean, GtkCallback callback, gpointer callback_data)
{
    if(child)
        callback(child->gobj(), callback_data);

}

void img_border_box::on_add(Gtk::Widget* inp_child)
{
    if(!inp_child)
    {
        child = inp_child;
        child->set_parent(*this);
    }
}

void img_border_box::on_remove(Gtk::Widget* inp_child)
{
    if(inp_child)
    {
        const bool visible = child->get_visible();
        bool found = false;

        if(inp_child == child)
        {
            child = nullptr;
            found = true;
        }

        if(found)
        {
            child->unparent();

            if(visible)
                queue_resize();
        }
    }
}

GType img_border_box::child_type_vfunc() const
{
    //If there is still space for one widget, then report the type of widget that
    //may be added.
    if(!child)
        return Gtk::Widget::get_type();
    else
    {
        //No more widgets may be added.
        return G_TYPE_NONE;
    }
}


/*  Old code
void content2_img_box::on_realize()
{
    set_realized();
    if(!refGdkWindow)
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

        attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK | Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;

        refGdkWindow = Gdk::Window::create(get_parent_window(), &attributes,
                                             GDK_WA_X | GDK_WA_Y);
        set_window(refGdkWindow);

        //make the widget receive events
        refGdkWindow->set_user_data(gobj());
    }


}

void content2_img_box::on_size_allocate(Gtk::Allocation& allocation)
{

    set_allocation(allocation);
    std::cout << "Box width" << allocation.get_width() << std::endl;
    std::cout << "Box height" << allocation.get_height() << std::endl;

    show_all_children();
    queue_draw();
//    refGdkWindow = get_window();
    if(refGdkWindow)
    {
        refGdkWindow->move_resize( allocation.get_x(), allocation.get_y(),
                                   allocation.get_width(), allocation.get_height() );
    }
//}

 */