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

class csprRead {
public:
    csprRead();
    void setFile(std::string name) {filename = name;}
    void loadTargets();
    // Method of storage for individual targets
    struct grna_shorts {
        std::string position;
        std::string sequence;
        std::string score;
    };
    //Accessible storage container for all the targets in the genome/assembly by chromosome/scaffold
    std::vector<std::vector<grna_shorts*>> Targets;
private:
    void openFile();
    bool newLine();
    std::string getLine(int);
    void closeFile();
    void processMultis();
    std::vector<std::string> Msplit(const std::string &text, char sep);
private:  // Private machinery for parsing the file
    FILE* stream;
    std::string filename;
};

#endif /* csprRead_hpp */
