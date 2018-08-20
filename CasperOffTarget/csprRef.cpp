//
//  csprRead.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/8/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "csprRef.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <iterator>

csprRef::csprRef() {
}

/* This function loads the reference targets. This is the import function for the .cspr file that is used as a reference
 * Function: This file takes in all the lines of the files and first stores it in a basic string vector.  Then the function
 * parses this string into appropriate containers for easier access in the OnTargets class. */
void csprRef::LoadcsprFile(std::string cspr) {
    FileOp myfile;
    myfile.open(cspr);
    int chromCounter = 0;
    std::string junkfirst = getLine(50); // skips the first chromosome indicator
    while (true) {
        std::string line = getLine(100);  //No line should be longer than 100 characters
        
        //Determine if we have moved to the repeats section of the file:
        if (line.find("REPEATS") != std::string::npos) {
            std::cout << "Reached Repeats section. Moving on to process repeat structure.\n";
            processMultis();
            break;
            //Determine whether the new line sets the start of a new Chromosome/Scaffold:
        } else if (line.find("CHROMOSOME") != std::string::npos) {
            chromCounter++;
        } else {
            //Get the position/location and add it to the location
            int pos_end = line.find(",");
            Locs[chromCounter].push_back(line.substr(0,pos_end));
            //Get the sequence and add it to the target
            int seq_end = line.substr(pos_end+1).find(",");
            RefTargets += line.substr(pos_end+1,seq_end);
            //Get the score and add it to the target
            Scores.push_back(line.substr(seq_end));
        }
    }
    closeFile();
}

/* getChromScaf: Returns which chromosome/scaffold based on the index of the location */
int csprRef::getChrScaf(long id) {
    
}
