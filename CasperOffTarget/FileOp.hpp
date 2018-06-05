//
//  FileOp.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 6/4/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef FileOp_hpp
#define FileOp_hpp

#include <stdio.h>
#include <string>
#include <vector>

class FileOp {
public:
    FileOp();
    void open(std::string);
    void closeFile();
    bool endFile();
private:
    std::string getLine(int);
    void processMultis();
    void LoadRefTargets();
    std::vector<std::string> Msplit(const std::string &text, char sep);
    
    std::vector<long> hits;
private:  // Private machinery for parsing the file
    FILE* stream;
    std::string filename;
};


#endif /* FileOp_hpp */
