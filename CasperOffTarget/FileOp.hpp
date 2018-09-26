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
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

/* Class contains the operators for manipulating both generic files and the .cspr and target query file specific operations,
 * which are the two main types of files that are processed in this program. */
class FileOp {
/* General functions for reading a file */
public:
    //FileOp();
    void open(std::string);
    std::string getLine(int);
    std::vector<std::string> getSepLine(int, char);
    bool newLine();
    void closeFile();
    bool endFile();
    
/* Functions for manipulating .cspr files */
private:
    std::vector<std::string> Msplit(const std::string &text, char sep);

/* Functions for manipulating target query file */
private:
    void LoadRefTargets();
private:  // Private machinery for parsing the file
    FILE* stream;
    std::string filename;
};

class WriteFile {
    /* General functions for writing to a file */
public:
    void openWrite(std::string);
    void write(std::string);
    void write(long);
    void write(double);
    void writeLine(std::string);
    void close();
private:
    std::ofstream outputfile;
};

#endif /* FileOp_hpp */
