//
//  RefSequences.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/16/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "RefSequences.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include "csprRead.hpp"

OnTargets::OnTargets(bool comp, std::string fl,csprRead &c) {
    if (comp) {
        // ignore the file just pull straight from the csprRead object
        readSequencesFromCspr(c);
    } else {
        readSequencesFromFile(fl);
    }
}

void OnTargets::readSequencesFromCspr(csprRead&) {
    
}

void 
