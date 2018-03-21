//
//  RefSequences.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/16/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef RefSequences_hpp
#define RefSequences_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <thread>
#include "csprRead.hpp"

class OnTargets {
public:
    OnTargets(bool, std::string, csprRead&);
    
    std::vector<std::vector<std::string>> ref_seq_buckets;
private:
    void parseSequences();
    void readSequencesFromCspr(csprRead&);
    void readSequencesFromFile(std::string);
private:
    FILE* stream;
    std::string filename;
};

#endif /* RefSequences_hpp */
