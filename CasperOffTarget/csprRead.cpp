//
//  csprRead.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/8/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "csprRead.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <iterator>

void csprRead::openFile()
{
    stream = fopen( filename.c_str(), "r");
    assert(stream);
}

bool csprRead::newLine()
{
    if (feof(stream) == 0) return true;
    return false;
}

/* Grabs a line from the file.  You can specify how long the character stream with the passed through
   integer. */
std::string csprRead::getLine(int l)
{
    char nts[l];
    fscanf( stream, "%[^\n]\n", nts);
    return std::string(nts);
}

/* Closes the file stream */
void csprRead::closeFile()
{
    if(stream) fclose( stream);
}

/* Iterates through the entire .cspr file and downloads all the targets */
void csprRead::loadTargets() {
    openFile();
    std::string junkfirst = getLine(50); // skips the first chromosome indicator
    std::vector<gRNA*> curset;
    while (true) {
        std::string line = getLine(100);  //No line should be longer than 100 characters
        
        //Determine if we have moved to the repeats section of the file:
        if (line.find("REPEATS") != std::string::npos) {
            Targets.push_back(curset);
            curset.clear();
            std::cout << "Reached Repeats section. Moving on to process repeat structure.\n";
            processMultis();
            break;
        //Determine whether the new line sets the start of a new Chromosome/Scaffold:
        } else if (line.find("CHROMOSOME") != std::string::npos) {
            Targets.push_back(curset);
            curset.clear();
        } else {
            gRNA* target = new gRNA;
            target->set_multiflag(false);
            //Get the position and add it to the target
            int pos_end = line.find(",");
            std::string pos = line.substr(0,pos_end);
            target->set_location(pos);
            //Get the sequence and add it to the target
            int seq_end = line.substr(pos_end+1).find(",");
            target->set_seq(line.substr(pos_end+1,seq_end));
            //Get the score and add it to the target
            target->set_score(line.substr(seq_end));
            //Adding the created target struct to the vector for that chromosome/scaffold
            curset.push_back(target);
        }
    }
    closeFile();
}

/* Code for processing the Repeats section which requires different processing of the locations and sequences */
void csprRead::processMultis() {
    while (true) {
        std::string line = getLine(15); //This line is just the seed sequence
        if (line.find("END_OF") != std::string::npos) {
            std::cout << "Reached the end of the file. \n";
            break;
        }
        // Save the seed
        std::string seedseq = line;
        // Get all tails and locations/scores associated with the seed
        std::string line2 = getLine(10000); // Much longer line to accomodate all the tails.
        //Split with tokenizer
        std::vector<std::string> tails = Msplit(line2,'\t');
        for (int i=0; i<tails.size()-1; i++) { // -1 takes into account that there is an extra tab produced making a blank vector location in tails
            //Split with tokenizer here as well
            std::vector<std::string> locs = Msplit(tails[i], ',');
            gRNA* target = new gRNA;
            target->set_location(locs[1]);
            target->set_seq(seedseq+locs[2]);
            target->set_score(locs[3]);
            target->set_multiflag(true);
            int chr = atoi(locs[0].c_str())-1;
            Targets[chr].push_back(target);
        }
    }
}

/* A method for splitting the repeats section. */
std::vector<std::string> csprRead::Msplit(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}
