//
//  gRNA.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/19/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "gRNA.hpp"


std::string gRNA::get_Clocation() {
    // need to uncompress location into long object
    return compressed_location;
}

//returns whether or not any putative hits were found somewhere on the genome.
bool gRNA::hasHits() {
    if (putative_off_seq_ids.size() > 0) {
        return true;
    } else { return false; }
}
