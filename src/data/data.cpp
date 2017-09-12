//
// Created by poh on 8/16/17.
//

#include "data.h"
#include <iostream>

namespace data {
    int data1 = -1;
    int data2 = -1;
    int data3 = -1;
    double content2_img_siz = 100; //in terms of percent
    std::string str1 = "QWE",str2 = "ASD",str3 = "ZXC";
    std::vector<std::shared_ptr<selection_data>> selections;
    std::unordered_map<long,std::shared_ptr<selection_data>> selections_map;

};


void data::set_val(int a, int b, int c){
    data1 = a;
    data2 = b;
    data3 = c;
}

void data::print_val(){
    std::cout << data1 << std::endl << data2 << std::endl << data3 << std::endl;
}




