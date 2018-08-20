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

/* Class contains the operators for manipulating both generic files and the .cspr and target query file specific operations,
 * which are the two main types of files that are processed in this program. */
class FileOp {
public:
    FileOp();
    void open(std::string);
    bool newLine();
    void closeFile();
    bool endFile();
public:
    
/* Functions for manipulating .cspr files */
private:
    std::string getLine(int);
    void processMultis();
    std::vector<std::string> Msplit(const std::string &text, char sep);
    std::vector<long> hits;

/* Functions for manipulating target query file */
private:
    void LoadRefTargets();
private:  // Private machinery for parsing the file
    FILE* stream;
    std::string filename;
};


#endif /* FileOp_hpp */
