#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>

#include "gui_window.h"


int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    gui_window helloworld;
    auto css = Gtk::CssProvider::create();
    const char path[256] = "../style1.css";
    if(not css->load_from_path(path)) {
        std::cerr << "Failed to load css\n";
        std::exit(1);
    }
    auto screen = Gdk::Screen::get_default();
    auto ctx = helloworld.get_style_context();
    ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    //Shows the window and returns when it is closed.
    return app->run(helloworld);
}
