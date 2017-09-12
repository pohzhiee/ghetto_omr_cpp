//
// Created by poh on 8/16/17.
//

#ifndef GTK_MAIN_DATA_H
#define GTK_MAIN_DATA_H

#include <string>
#include <glibmm/fileutils.h>
#include <vector>
#include <memory>
#include "selection_data.h"




namespace data {
    extern int data1, data2, data3;
    extern std::string str1,str2,str3;
    extern double content2_img_siz; // in terms of percent
    extern std::vector<std::shared_ptr<selection_data>> selections;
    extern std::unordered_map<long,std::shared_ptr<selection_data>> selections_map;
    void set_val(int a,int b,int c);
    void print_val();


};



#endif //GTK_MAIN_DATA_H
