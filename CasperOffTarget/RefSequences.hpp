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
#include "CSeqTranslate.hpp"

class OnTargets {
public:
    //OnTargets();
    void loadData(std::string); //pass filename of .cspr file for reference
    void compressed(bool t) {is_compressed = t;}
    
    void LoadTargetQuery(std::string);  // pass OFF_QUERY file to the class
    void set_base_seqs(std::vector<gRNA*> x) {base_seqs = x;}
    
    //generic algorithm that loops through all targets calling findSimilars. Initiates threads. Iterates through base_seqs
    void run_off_algorithm(int);
    void generateScores(std::string,std::string,int,double,bool,bool); // calls the scoring algorithm iterating through putative_off_seqs (passed object is settings file)
    
private:
    void findSimilars(gRNA*);  //runs algorithm on individual target
    std::vector<gRNA*> base_seqs;  //stores all queries loaded by the public function set_base_seqs
    
private:
    bool is_compressed;
    csprRef ref;
    OffScoring scoreGenerator;
    SeqTranslate S;
};

#endif /* RefSequences_hpp */
