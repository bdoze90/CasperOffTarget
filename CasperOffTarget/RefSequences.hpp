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
#include "csprRef.hpp"
#include "FileOp.hpp"
#include "gRNA.hpp"
#include "OffScoring.hpp"

class OnTargets {
public:
    void loadData(csprRef* c) {ref = c;}  //obtain information from csprRef object
    void compressed(bool) {is_compressed = true;}
    
    void LoadTargetQuery(std::string);
    
    void set_base_seqs(std::vector<gRNA*> x) {base_seqs = x;}
    
    //generic algorithm that loops through all targets calling findSimilars. Initiates threads. Iterates through base_seqs
    void run_off_algorithm(int);
    
private:
    void findSimilars(gRNA*);  //runs algorithm on individual target
    std::vector<gRNA*> putative_off_seqs;  //storage for
    void generateScores(); // calls the scoring algorithm iterating through putative_off_seqs
    
private:
    bool is_compressed = true;
    csprRef* ref;
    OffScoring scoreGenerator;
    std::vector<gRNA*> base_seqs;
};

#endif /* RefSequences_hpp */
