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
#include "gRNA.hpp"

class csprRef {
public:
    csprRef();
    void LoadcsprFile(std::string name) {filename = name;}
    void LoadTargetQuery(std::string);
    //Accessible storage container for all the targets in the genome/assembly by chromosome/scaffold
    std::vector<std::vector<gRNA*>> TargetQuery;
    
    //Base info from the .cspr file. This is a long string that has every target in succession
    std::string RefTargets;
    
    //Also base info from .cspr file has the location and scores at the vector index of the Reftarget position
    std::vector<std::string> Locs; //first index is chromosome/scaffold the rest are for locations
    std::vector<int> Scores;
    // Vector below stores the locations where the chromosome/scaffolds start and stop in RefTargets
    std::vector<long> Chrpos;
    
private:
    void openFile();
    bool newLine();
    std::string getLine(int);
    void closeFile();
    void processMultis();
    void LoadRefTargets();
    std::vector<std::string> Msplit(const std::string &text, char sep);
    
    std::vector<long> hits;
private:  // Private machinery for parsing the file
    FILE* stream;
    std::string filename;
};

#endif /* csprRead_hpp */
