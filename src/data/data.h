//
// Created by poh on 8/16/17.
//

#ifndef GTK_MAIN_DATA_H
#define GTK_MAIN_DATA_H

#include <string>
#include <functional>
#include <glibmm/fileutils.h>
#include <vector>

struct selection_box{

    selection_box(gdouble xin, gdouble xfin, gdouble yin, gdouble yfin);

    gdouble x_init, x_final;
    gdouble y_init, y_final;

    selection_box operator*(gdouble scale);
};

namespace data {
    extern int data1, data2, data3;
    extern std::vector<selection_box> selections,selections_abs;
    extern std::string str1,str2,str3;
    extern double content2_img_siz; // in terms of percent
    void set_val(int a,int b,int c);
    void print_val();
};



#endif //GTK_MAIN_DATA_H
