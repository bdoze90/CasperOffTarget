//
//  gRNA.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/19/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef gRNA_hpp
#define gRNA_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <thread>

class gRNA {
public:
    gRNA();
    long get_location();
    int get_chromscaff();
    std::string get_comp_seq();
private:
    int 
};

#endif /* gRNA_hpp */
