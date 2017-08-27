//
// Created by poh on 8/20/17.
//

#ifndef GHETTO_OMR_LAYERBOX_H
#define GHETTO_OMR_LAYERBOX_H

#include "../../content2.h"
#include <gtkmm/box.h>


class layerbox : public Gtk::Box{
public:
    layerbox(content2 *contbox);
protected:
    content2 *p_content2;
};


#endif //GHETTO_OMR_LAYERBOX_H
