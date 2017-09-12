//
// Created by poh on 9/3/17.
//

#ifndef GTK_TREEVIEW1_LAYERTOOLS_H
#define GTK_TREEVIEW1_LAYERTOOLS_H


#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <memory>
#include "LayerBox.h"

class LayerTools : public Gtk::ButtonBox {
public:
    LayerTools(LayerBox *parent);
    virtual ~LayerTools();

protected:
    LayerBox *parent;

    const int tool_button_size;

    std::vector<std::shared_ptr<Gtk::Button> > tool_button_list;
    std::vector<Gtk::Image> tool_image_list2;

    void on_button1_clicked();
    void on_button2_clicked();
};


#endif //GTK_TREEVIEW1_LAYERTOOLS_H
