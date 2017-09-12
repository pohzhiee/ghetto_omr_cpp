//
// Created by poh on 9/3/17.
//

#ifndef GTK_TREEVIEW1_LAYERBOX_H
#define GTK_TREEVIEW1_LAYERBOX_H


#include <gtkmm/box.h>
#include <gtkmm/messagedialog.h>
#include "../../content2.h"

class LayerTools;
class LayerListScrollable;

class LayerBox : public Gtk::Box {
public:
    LayerBox(content2 *parent);
    virtual ~LayerBox();


    void parent_add_row(std::shared_ptr<selection_data> data_ptr);

protected:
    content2 *p_content2;

    std::shared_ptr<LayerTools> tools;
    std::shared_ptr<LayerListScrollable> list;



    void parent_delete_active_row();
    void parent_edit_active_row();



friend class LayerTools;
friend class LayerListScrollable;

};


#endif //GTK_TREEVIEW1_LAYERBOX_H
