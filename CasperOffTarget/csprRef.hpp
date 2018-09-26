//
//  csprRead.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/8/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef csprRead_hpp
#define csprRead_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "FileOp.hpp"
#include "CSeqTranslate.hpp"

class csprRef {
public:
    void LoadcsprFile(std::string name);
    
    std::string *AccessRefString() {return &RefTargets;}
    /*Obtaining information from the private containers.  These ask for the index of the target you are searching for,
     which means that the index of the RefTargets match is the input.  All of these divide by 9 to first get the id
     of the RefTargets target and then proceed to return the appropriate value. */
    long getLoc(long l) {return Locs[l/8];}
    int getChrScaf(long);
    int getScore(long x) {return Scores[x/8];}
    
    // returns the last id of the last chromosome before the multis so that anything greater is in the multis
    long multiStart() {return multistart;}
    std::vector<std::string> getMultis(long ind) {return multiLocs[ind];}
    
    int chromCount() {return Chrpos.size();}
    

private:
    //Base info from the .cspr file. This is a long string that has every target in succession.
    std::string RefTargets;
    //Also base info from .cspr file has the location and scores at the vector index of the Reftarget position
    std::vector<long> Locs; //all decompressed locations in succession
    std::vector<int> Scores; //all decompressed scores in succession
    
    // Vector below stores the locations where the chromosome/scaffolds stop in RefTargets (number represents how many targets are in each)
    std::vector<long> Chrpos;
    
    //Stores the vectors of multi tails and their positions separated by commas
    std::vector<std::vector<std::string>> multiLocs;
    long multistart;
    
private:
    void processMultis(FileOp);
    std::vector<std::string> Msplit(const std::string &text, char sep);
    
    SeqTranslate S;
    
};

#endif /* csprRead_hpp */
