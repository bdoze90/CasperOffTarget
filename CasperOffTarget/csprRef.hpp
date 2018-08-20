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

class csprRef {
public:
    csprRef();
    void LoadcsprFile(std::string name);
    
    std::string getRefString() {return RefTargets;}
    //Obtaining information from the private containers:
    std::string getLoc(long l) {return Locs[l];}
    int getChrScaf(long);
    int getScore(long x) {return Scores[x];}
    
    
    
private:
    //Base info from the .cspr file. This is a long string that has every target in succession.
    std::string RefTargets;
    //Also base info from .cspr file has the location and scores at the vector index of the Reftarget position
    std::vector<std::string> Locs; //all compressed locations in succession
    std::vector<int> Scores; //all compressed scores in succession
    // Vector below stores the locations where the chromosome/scaffolds stop in RefTargets
    std::vector<long> Chrpos;
    
    
private:
    bool newLine();
    std::string getLine(int);
    void closeFile();
    void processMultis();
    std::vector<std::string> Msplit(const std::string &text, char sep);
    
};

#endif /* csprRead_hpp */
