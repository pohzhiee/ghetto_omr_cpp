//
// Created by poh on 8/16/17.
//

#include "data.h"
#include <iostream>

namespace data {
    int data1 = -1;
    int data2 = -1;
    int data3 = -1;
    int content2_img_siz = 100; //in terms of percent
    std::string str1 = "QWE",str2 = "ASD",str3 = "ZXC";
    std::vector<selection_box> selections,selections_abs;

};


void data::set_val(int a, int b, int c){
    data1 = a;
    data2 = b;
    data3 = c;
}

void data::print_val(){
    std::cout << data1 << std::endl << data2 << std::endl << data3 << std::endl;
}



selection_box::selection_box(gdouble xin, gdouble xfin, gdouble yin, gdouble yfin)
{
    x_init = xin;
    x_final = xfin;
    y_init = yin;
    y_final = yfin;
};


selection_box selection_box:: operator*(gdouble scale)
{
    return selection_box(x_init*scale,x_final*scale,y_init*scale,y_final*scale);
};