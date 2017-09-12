//
// Created by poh on 9/3/17.
//

#include <iostream>
#include <memory>
#include <gtkmm/stock.h>
#include "LayerListScrollable.h"
#include "CellRenderer_isVisible.h"
#include "../image/img_area.h"

LayerListScrollable::LayerListScrollable(LayerBox *layerbox)  :
        list_columns_ (),
        list_store_   (Gtk::ListStore::create(list_columns_)),
        tree_view_    (list_store_),
        parent        (layerbox)

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
    long index = row[list_columns_.unique_index];
    data::selections_map[index]->isVisible=row[list_columns_.active];
    parent->p_content2->imgarea->queue_draw();
}

void LayerListScrollable::on_edit_dialog_response(int response_id, std::shared_ptr<dialog> &p_dialog
                                                        , Gtk::TreeModel::Row &row)
{
    switch (response_id)
    {
        case Gtk::RESPONSE_CLOSE:
            break;
        case Gtk::RESPONSE_CANCEL:
            p_dialog->hide();
            break;
        case Gtk::RESPONSE_DELETE_EVENT:
            p_dialog.reset();
            break;
        case Gtk::RESPONSE_OK:
            on_edit_dialog_ok_clicked(p_dialog,row);
            p_dialog.reset();
            break;
        default:
            std::cout << "Unexpected response!" << std::endl;
            break;
    }
};

void LayerListScrollable::on_edit_dialog_ok_clicked(std::shared_ptr<dialog> &ps_dialog,
                                                    Gtk::TreeModel::Row &row)
{
    //Check if all the parameters are acceptable
    if((ps_dialog->current_set)->text_check_all())
    {
        long ori_index = row[list_columns_.unique_index];
        std::shared_ptr<selection_data> ori_ptr = data::selections_map[ori_index];
        std::pair<coords,coords> coords_ori = ori_ptr->get_coords();
        if(coords_ori.first.iszero() || coords_ori.second.iszero())
        {
            std::cerr << "ORIGINAL COORDINATES ZERO!?!?" << std::endl;
        }

        std::shared_ptr<selection_data> p_data = ps_dialog->current_set->save_values();
        p_data->set_coords(coords_ori.first,coords_ori.second);
        row[list_columns_.text]   = p_data->get_value_by_key("layer_name");
        row[list_columns_.active] = p_data->isVisible;
        long new_index = p_data->get_index();

        std::cout << "ADDING NEW INDEX: " << new_index << std::endl;

        row[list_columns_.unique_index] = new_index;

        data::selections_map[new_index] = p_data;
        std::cout << "DELETING OLD INDEX: " << ori_index << std::endl;
        data::selections_map.erase(ori_index);
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

//General functions
/**
 * Gets the unique index of the selected row in the treemodel
 * @return
 * Unique index of type int identifying the row of data
 */
long LayerListScrollable::get_row_index()
{

    auto selection = tree_view_.get_selection();
    auto row_iter = selection->get_selected();
    long value = row_iter->get_value(list_columns_.unique_index);
    return value;
}

/**
 * Deletes the row of data based on the given unique index
 * @param index
 * unique index identifying the row of data
 */
void LayerListScrollable::delete_data(long &index)
{
    //TODO: delete database data member as well
    Gtk::TreeModel::Children children = list_store_->children();


    for(auto row : children)
    {
        if(row[list_columns_.unique_index] == index){
            list_store_->erase(row);
        }
    }
    data::selections_map.erase(index);
}

/**
 * Deletes selected row in the list
 * Calls a confirmation dialog -> Get row unique index -> calls delete_data using the index
 */
void LayerListScrollable::delete_active_row()
{
    long index = get_row_index();
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

void LayerListScrollable::edit_active_row()
{
    auto selection = tree_view_.get_selection();
    auto row_iter = selection->get_selected();
    Gtk::TreeModel::Row row = *row_iter;
    long index = row.get_value(list_columns_.unique_index);
    std::shared_ptr<selection_data> &p_data = data::selections_map[index];
    std::shared_ptr<dialog> dialog_ptr = row.get_value(list_columns_.dialog_ptr);
    if(dialog_ptr)
    {
        const int response_id = dialog_ptr->run();
        on_edit_dialog_response(response_id,dialog_ptr,row);
    }
    else
    {
        dialog_ptr = std::make_shared<dialog>(p_data);
        Gtk::Window *window = dynamic_cast <Gtk::Window *> (get_toplevel());
        if (window->get_is_toplevel()) {
            dialog_ptr->set_transient_for(*window);
        }
        const int response_id = dialog_ptr->run();
        on_edit_dialog_response(response_id,dialog_ptr,row);

        row[list_columns_.dialog_ptr] = dialog_ptr;
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
        auto icon_pixbuf = Gdk::Pixbuf::create_from_file("../icons/eye.svg",20,20,true);
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
    tree_view_.append_column("Index", list_columns_.unique_index);

}

/**
 * Main add row function, usually called from parent
 * Also adds the data into the global database, therefore creating 2 owners of the shared pointer (global database and treeview database)
 * @param input
 * input to be added to the row
 */
void LayerListScrollable::add_row(std::shared_ptr<selection_data> data_ptr)
{

    auto row = *list_store_->prepend();
    row[list_columns_.text]   = data_ptr->get_value_by_key("layer_name");
    row[list_columns_.active] = data_ptr->isVisible;
    auto index = data_ptr->get_index();
    row[list_columns_.unique_index] = index;
    data::selections_map[index] = data_ptr;
}
