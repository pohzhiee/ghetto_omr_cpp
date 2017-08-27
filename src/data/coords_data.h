//
// Created by poh on 8/24/17.
//

#ifndef GTK_MAIN_COORDS_DATA_H
#define GTK_MAIN_COORDS_DATA_H

#include <glibmm/fileutils.h>

struct coords
{
    coords();
    coords(gdouble x, gdouble y);
    coords operator *(gdouble scale);
    coords operator /(gdouble scale);
    gdouble x;
    gdouble y;

    bool iszero();
};

struct rect_coords
{
    rect_coords();
    rect_coords(coords init, coords final);
    rect_coords operator *(gdouble scale);
    rect_coords operator /(gdouble scale);
    std::pair <coords,coords> rect;
};

#endif //GTK_MAIN_COORDS_DATA_H
