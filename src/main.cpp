#include <iostream>
#include "data.h"
#include <gtkmm/application.h>
#include "gui_main.h"


int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    gui_main helloworld;

    //Shows the window and returns when it is closed.
    return app->run(helloworld);
}
