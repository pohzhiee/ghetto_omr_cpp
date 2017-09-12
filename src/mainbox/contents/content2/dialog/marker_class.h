//
// Created by poh on 8/23/17.
//

#ifndef GTK_MAIN_MARKER_H
#define GTK_MAIN_MARKER_H

#include "_dialog_qn.h"
#include "../../../../data/marker_data.h"


class marker_class : public dialog_qn {
public:
    marker_class(std::shared_ptr<selection_data> p_data = nullptr);
    std::shared_ptr<selection_data> save_values() override;

protected:
    std::shared_ptr<selection_data> p_data;
};


#endif //GTK_MAIN_MARKER_H
