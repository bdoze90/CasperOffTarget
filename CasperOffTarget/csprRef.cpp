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


/* This function loads the reference targets. This is the import function for the .cspr file that is used as a reference
 * Function: This file takes in all the lines of the files and first stores it in a basic string vector.  Then the function
 * parses this string into appropriate containers for easier access in the OnTargets class. */
void csprRef::LoadcsprFile(std::string cspr) {
    FileOp myfile;
    myfile.open(cspr);
    long chromCounter = 0;
    while (true) {
        std::string line = myfile.getLine(100);  //No line should be longer than 100 characters
    
        //Determine if we have moved to the repeats section of the file:
        if (line.find("REPEATS") != std::string::npos) {
            std::cout << "Reached Repeats section. Moving on to process repeat structure.\n";
            Chrpos.push_back(chromCounter); // end of Chrpos tells you the start of the Repeats section.
            processMultis(myfile);
            break;
    
        //Determine whether the new line sets the start of a new Chromosome/Scaffold:
        } else if (line.find('>') != std::string::npos) {
            Chrpos.push_back(chromCounter);
            chromCounter = 0;
            
        //Passes all tests that it is truly a unique sequence line
        } else {
            std::vector<std::string> target = Msplit(line, ',');  //Split up the line
            Locs.push_back(S.decompress_location(target[0]));  //Add compressed location to Locs vector
            Scores.push_back(S.decompress_location(target[2]));  //Add decompressed score to Scores vector
            RefTargets += target[1].substr(0,8);  //Add the sequence to the long sequence string
            chromCounter ++; //keeps track of how many targets are in the chromosome/scaffold
        }
    }
    myfile.closeFile();
}

/* Code for processing the Repeats section which requires different processing of the locations and sequences */
void csprRef::processMultis(FileOp myfile) {
    while (true) {
        std::string line = myfile.getLine(15); //This line is just the seed sequence
        std::cout << line << std::endl;
        if (line.find("END_OF") != std::string::npos) {
            std::cout << "Reached the end of the file. \n";
            break;
        }
        // Add filler to the seed:
        for (int i=line.size()-1;i<8;i++) {
            line = '|' + line;
        }
        // Save the seed
        RefTargets += line;
        // Get all tails and locations/scores associated with the seed.  Much longer line to accomodate all the tails.
        std::vector<std::string> tails = myfile.getSepLine(50000,'\t');
        multiLocs.push_back(tails);
    }
}


/* getChromScaf: Returns which chromosome/scaffold based on the index of the location */
int csprRef::getChrScaf(long id) {
    long t_index = id/8;
    int i = 0;
    while (t_index < Chrpos[i]) {
        i++;
    }
    return Chrpos[i];
}

/* A method for splitting the repeats section. */
std::vector<std::string> csprRef::Msplit(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}
