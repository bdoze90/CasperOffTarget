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
    fscanf( stream, "%s\n", nts);
    return std::string(nts);
}

/* Closes the file stream */
void csprRead::closeFile()
{
    if(stream) fclose( stream);
}

/* Iterates through the entire .cspr file and downloads all the targets */
void csprRead::loadTargets() {
    while (newLine()) {
        std::string line = getLine(100);  //No line should be longer than 100 characters
        std::vector<grna_shorts*> curset;
        
        //Determine if we have moved to the repeats section of the file:
        if (line.find("REPEATS") != std::string::npos) {
            std::cout << "Reached Repeats section. Moving on to process repeat structure.\n";
            processMultis();
        //Determine whether the new line sets the start of a new Chromosome/Scaffold:
        } else if (line.find("#") == std::string::npos) {
            grna_shorts *target = new grna_shorts;
            //Get the position and add it to the target
            int pos_end = line.find(",");
            std::string pos = line.substr(0,pos_end);
            target->position = pos;
            //Get the sequence and add it to the target
            int seq_end = line.substr(pos_end).find(",");
            std::string seq = line.substr(pos_end,seq_end-pos_end);
            target->sequence = seq;
            //Get the score and add it to the target
            std::string scr = line.substr(seq_end);
            target->score = scr;
            
            //Adding the created target struct to the vector for that chromosome/scaffold
            curset.push_back(target);
        } else {
            Targets.push_back(curset);
            curset.clear();
            
        
        }
    }
}

/* Code for processing the Repeats section which requires different processing of the locations and sequences */
void csprRead::processMultis() {
    while (newLine()) {
        std::string line = getLine(10); //This line is just the seed sequence
        // Save the seed
        std::string seedseq = line;
        // Get all tails and locations/scores associated with the seed
        std::string line2 = getLine(10000); // Much longer line to accomodate all the tails.
        //Split with tokenizer
        std::vector<std::string> tails = Msplit(line2,'\t');
        for (int i=0; i<tails.size(); i++) {
            //Split with tokenizer here as well
            std::vector<std::string> locs = Msplit(tails[i], ',');
            grna_shorts *target = new grna_shorts;
            target->position = locs[1];
            target->sequence = seedseq + locs[2];
            target->score = locs[3];
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
