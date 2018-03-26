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
#include <stdlib.h>
#include <stdio.h>
#include "csprRead.hpp"
#include "gRNA.hpp"

class OnTargets {
public:
    void loadRef(csprRead* c) {ref = c;}
    
    void readInFromFile(std::string);
    void set_base_seqs(std::vector<gRNA*> x) {base_seqs = x;}
    
    void run_off_algorithm();
    
private:
    struct gRNA_short {
        gRNA* base;
        std::vector<std::string> hit;
        std::vector<int> chromscaff;
        std::vector<std::string> loc;
    };
    void findSimilars(gRNA*);
    std::vector<gRNA_short> preprocessed_seqs;
    void generateScore();
    
private:
    FILE* stream;
    std::string filename;
    csprRead* ref;
    std::vector<gRNA*> base_seqs;
};

#endif /* RefSequences_hpp */
