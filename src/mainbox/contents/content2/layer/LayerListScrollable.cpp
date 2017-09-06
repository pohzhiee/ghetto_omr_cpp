//
// Created by poh on 9/3/17.
//

#include <iostream>
#include "LayerListScrollable.h"
#include "CellRenderer_isVisible.h"

LayerListScrollable::LayerListScrollable(LayerBox *layerbox)  :
        list_columns_ (),
        list_store_   (Gtk::ListStore::create(list_columns_)),
        tree_view_    (list_store_),
        parent        (layerbox),
        index(1)

{

    /*
     * TODO: Make reorderable
     * 1) get reorder event
     * 2) arrange database members accordingly
    tree_view_.set_reorderable(true);
     */
    add(tree_view_);
    initialise_list();
    show_all_children();
}

LayerListScrollable::~LayerListScrollable() {

}

//Signal Handlers
/**
 * Signal handler for visibility cell toggle on off
 * For signal origin, look at CellRender_isVisible::activate_vfunc
 * @param path_string
 * indicates which row is toggled, e.g. 0 means 1st row
 */
void LayerListScrollable::on_cell_toggled(const Glib::ustring& path_string)
{
    // Get the model row that has been toggled.
    auto row = *list_store_->get_iter(Gtk::TreeModel::Path(path_string));

    // Invert the 'active' value in the toggled row.
    row[list_columns_.active] = !row[list_columns_.active];
}

//General functions
/**
 * Gets the unique index of the selected row in the treemodel
 * @return
 * Unique index of type int identifying the row of data
 */
int LayerListScrollable::get_row_index()
{

    auto selection = tree_view_.get_selection();
    auto row_iter = selection->get_selected();
    int value = row_iter->get_value(list_columns_.unique_index);
    return value;
}



/**
 * Deletes the row of data based on the given unique index
 * @param index
 * unique index identifying the row of data
 */
void LayerListScrollable::delete_data(int &index)
{
    //TODO: delete database data member as well
    Gtk::TreeModel::Children children = list_store_->children();

    for(auto row : children)
    {
        if(row[list_columns_.unique_index] == index){
            list_store_->erase(row);
        }
    }
}

/**
 * Deletes selected row in the list
 * Calls a confirmation dialog -> Get row unique index -> calls delete_data using the index
 */
void LayerListScrollable::delete_active_row()
{
    int index = get_row_index();
    if(!delete_confirm_dialog)
    {
        initialise_dialog();
    }

    const int response = delete_confirm_dialog->run();
    switch (response){
        case Gtk::RESPONSE_OK:
            delete_data(index);
            delete_confirm_dialog->hide();
            break;
        case Gtk::RESPONSE_CANCEL:
            delete_confirm_dialog->hide();
            break;
        case Gtk::RESPONSE_DELETE_EVENT:
            delete_confirm_dialog->hide();
            break;
        default:
            std::cerr << "ERROR no such button" << std::endl;
            break;
    }
}


//Constructors
/**
 * Function to initialise delete layer confirmation dialog
 * Has to be called after widget is realised inside a window (e.g. outside constructor)
 */
void LayerListScrollable::initialise_dialog()
{

    //Initialise confirmation dialog
    delete_confirm_dialog = std::make_unique<Gtk::MessageDialog>("Confirm delete layer?", false,
                                                                 Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);

    /* Note that get_toplevel() has to be called after the widget has been added to the main window (Gtk::Window)
     * Hence it cannot be done in the constructor because main Gtk::Window has nothing yet
     */
    Gtk::Window *window = dynamic_cast <Gtk::Window*> (get_toplevel());
    if(window && window->get_toplevel())
    {
        delete_confirm_dialog->set_transient_for(*window);
        delete_confirm_dialog->set_title("Delete Layer");
    }
    else
    {
        std::cerr << "get_toplevel() window is not toplevel or dynamic cast to Gtk::Window failed" << std::endl;
    }
}

/**
 * Initialise the relevant objects for a Gtk::TreeView
 */
void LayerListScrollable::initialise_list()
{
    tree_view_.set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_VERTICAL);
    tree_view_.set_enable_tree_lines(true);
    //Append 1st column with custom cell renderer
    {
        auto icon_pixbuf = Gdk::Pixbuf::create_from_file("../icons/alienarena.svg",20,20,true);
        visibility_icon = Gtk::Image(icon_pixbuf);
        CellRenderer_isVisible *const renderer = new CellRenderer_isVisible();
        Gtk::TreeViewColumn  *const column   = new Gtk::TreeViewColumn("Temp title", *Gtk::manage(renderer));
        tree_view_.append_column(*Gtk::manage(column));

        column->set_widget(visibility_icon);
        column->queue_resize();
        visibility_icon.show();
        column->add_attribute(renderer->property_active(), list_columns_.active);

        renderer->signal_toggled().connect(sigc::mem_fun(*this, &LayerListScrollable::on_cell_toggled));

    }
    //Append 2nd column
    tree_view_.append_column("Text", list_columns_.text);

}

/**
 * Main add row function, usually called from parent
 * @param input
 * input to be added to the row
 */
void LayerListScrollable::add_row(Glib::ustring &input)
{

    auto row = *list_store_->append();
    row[list_columns_.text]   = input;
    row[list_columns_.active] = true;
    row[list_columns_.unique_index] = index++;
}
