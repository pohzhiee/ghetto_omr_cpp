//
// Created by poh on 9/6/17.
//

#include "functions.h"

bool functions::isInteger(const std::string &s) {

    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0) ;

}
