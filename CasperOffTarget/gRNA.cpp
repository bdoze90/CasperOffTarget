//
//  gRNA.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/19/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "gRNA.hpp"


std::string gRNA::get_location() {
    // need to uncompress location into long object
    return compressed_location;
}

std::string gRNA::get_sequence() {
    // need to uncompress sequence
    return "sequence";
}

int gRNA::get_score() {
    // need to uncompress score
    return 50;
}
