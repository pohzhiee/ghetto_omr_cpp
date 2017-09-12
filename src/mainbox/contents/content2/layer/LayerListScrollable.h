//
// Created by poh on 9/3/17.
//

#ifndef GTK_TREEVIEW1_LAYERLISTSCROLLABLE_H
#define GTK_TREEVIEW1_LAYERLISTSCROLLABLE_H

#include <gtkmm/box.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include "LayerBox.h"
#include "../../../../data/selection_data.h"
#include "../dialog/dialog.h"

#include <memory>

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    Gtk::TreeModelColumn<Glib::ustring> text;
    Gtk::TreeModelColumn<bool>          active;
    Gtk::TreeModelColumn<long>          unique_index;
    Gtk::TreeModelColumn<std::shared_ptr<dialog>> dialog_ptr;

    ModelColumns() { add(active);add(text);add(unique_index);add(dialog_ptr);  }
};

class LayerListScrollable : public Gtk::ScrolledWindow
{
public:
    LayerListScrollable(LayerBox *layerbox);
    virtual ~LayerListScrollable();

protected:
    LayerBox *parent;

    ModelColumns                  list_columns_;
    Glib::RefPtr<Gtk::ListStore>  list_store_;
    Gtk::TreeView                 tree_view_;

    Gtk::Image visibility_icon;

    std::unique_ptr<Gtk::MessageDialog> delete_confirm_dialog;

    //Signal handlers
    void on_cell_toggled(const Glib::ustring& path_string);
    void on_edit_dialog_response(int response_id, std::shared_ptr<dialog> &p_dialog,
                                 Gtk::TreeModel::Row &row);

    void on_edit_dialog_ok_clicked(std::shared_ptr<dialog> &ps_dialog,
                                   Gtk::TreeModel::Row &row);

    //Getters
    long get_row_index();

    //Deletion functions
    void delete_data(long &index);

    void delete_active_row();
    void edit_active_row();


    //Add row
    void add_row(std::shared_ptr<selection_data> data_ptr);

    //Creation functions
    void initialise_dialog();
    void initialise_list();

friend class LayerBox;

};


#endif //GTK_TREEVIEW1_LAYERLISTSCROLLABLE_H
