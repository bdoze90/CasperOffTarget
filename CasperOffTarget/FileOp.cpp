//
//  FileOp.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 6/4/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "FileOp.hpp"

FileOp::FileOp() {
    LoadRefTargets();
}

void FileOp::open(std::string filename)
{
    stream = fopen( filename.c_str(), "r");
    assert(stream);
}

bool FileOp::endFile()
{
    if (feof(stream) == 0) return true;
    return false;
}

/* Grabs a line from the file.  You can specify how long the character stream with the passed through
 integer. */
std::string FileOp::getLine(int l)
{
    char nts[l];
    fscanf( stream, "%[^\n]\n", nts);
    return std::string(nts);
}

/* Closes the file stream */
void FileOp::closeFile()
{
    if(stream) fclose( stream);
}


/* Code for processing the Repeats section which requires different processing of the locations and sequences */
void csprRef::processMultis() {
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
std::vector<std::string> FileOp::Msplit(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}
