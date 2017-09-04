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

#include <memory>

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    Gtk::TreeModelColumn<Glib::ustring> text;
    Gtk::TreeModelColumn<bool>          active;
    Gtk::TreeModelColumn<int>           unique_index;

    ModelColumns() { add(active);add(text);add(unique_index);  }
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

    //Getters
    int get_row_index();

    //Deletion functions
    void delete_data(int &index);
    void delete_active_row();

    //Add row
    void add_row(Glib::ustring &input);

    //Creation functions
    void initialise_dialog();
    void initialise_list();

friend class LayerBox;

private:
    int index;
};


#endif //GTK_TREEVIEW1_LAYERLISTSCROLLABLE_H
