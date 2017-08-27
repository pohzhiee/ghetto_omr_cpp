//
// Created by poh on 8/24/17.
//

#include "coords_data.h"

coords::coords()
{
    x = 0;
    y = 0;
}

coords::coords(gdouble x_input, gdouble y_input)
{
    x = x_input;
    y = y_input;
}

coords coords::operator*(gdouble scale)
{
    return coords(x * scale, y * scale);
}

coords coords::operator/(gdouble scale)
{
    return coords(x / scale, y / scale);
}

bool coords::iszero()
{
    return (x == 0 && y == 0);
}

rect_coords::rect_coords()
{
    rect.first = coords();
    rect.second = coords();
}

rect_coords::rect_coords(coords init, coords final)
{
    rect.first = init;
    rect.second = final;
}

rect_coords rect_coords::operator*(gdouble scale)
{
    return rect_coords(rect.first * scale, rect.second * scale);
}

rect_coords rect_coords::operator/(gdouble scale)
{
    return rect_coords(rect.first / scale, rect.second / scale);
}