//
//  csprRead.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/8/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "pch.h"
#include "csprRef.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

/* This function loads the reference targets. This is the import function for the .cspr file that is used as a reference
 * Function: This file takes in all the lines of the files and first stores it in a basic string vector.  Then the function
 * parses this string into appropriate containers for easier access in the OnTargets class. */
void csprRef::LoadcsprFile(std::string cspr) 
{
	std::ifstream myfile;
	myfile.open(cspr,std::ifstream::in);
	if (myfile.is_open())
	{
		cout << "File Opened" << endl;
	}
	else
	{
		cout << "Error: Could not open CSPR file." << endl;
	}
	long chromCounter = 0;
	bool first = true;
	while (true) 
	{
		std::string line;
		if (first == true)
		{
			for (int i = 0; i < 3; i++)
			{
				std::getline(myfile, line);
			}
			first = false;
		}

		std::getline(myfile,line);  //No line should be longer than 100 characters
		//Determine if we have moved to the repeats section of the file:
		if (line.find("REPEATS") != std::string::npos) 
		{
			// consolidate the id of the last unique by getting the length of the Locs vector:
			multistart = Locs.size();
			std::cout << "Reached Repeats section. Moving on to process repeat structure." << std::endl;
			Chrpos.push_back(chromCounter); // end of Chrpos tells you the start of the Repeats section.
			processMultis(myfile);
			break;
			//Determine whether the new line sets the start of a new Chromosome/Scaffold:
		}
		else if (line.find('>') != std::string::npos)
		{
			Chrpos.push_back(chromCounter);
			std::cout << "Sequences from beginning to end of this Chromosome/Scaffold: " << chromCounter + 1 << std::endl;
		//Passes all tests that it is truly a unique sequence line
		}
		else 
		{
			std::vector<std::string> target = Msplit(line, ',');  //Split up the line
			Locs.push_back(S.decompress_location(target[0]));  //Add compressed location to Locs vector
			Scores.push_back(S.decompress_location(target[2]));  //Add decompressed score to Scores vector
			RefTargets += target[1].substr(0, 8);  //Add the sequence to the long sequence string
			chromCounter++; //keeps track of how many targets are in the chromosome/scaffold
		}
	}
	myfile.close();
}

/* Code for processing the Repeats section which requires different processing of the locations and sequences */

void csprRef::processMultis(std::ifstream& myfile) {
	while (true) {
		std::string line;
		std::getline(myfile, line); //This line is just the seed sequence
		if (line.find("END_OF_FILE") != std::string::npos) {
			std::cout << "Reached the end of the file. \n";
			break;
		}
		// Add the marker that differentiates the seed from the filler:
		line = '!' + line;
		// Add remaining filler to the seed:
		for (int i = line.size();i < 8;i++) {
			line = '|' + line;
		}
		// Save the seed
		RefTargets += line;
		// Get all tails and locations/scores associated with the seed.  Much longer line to accomodate all the tails.
		//char tailarray[500000000];
		//myfile.getline(tailarray, 500000000);
		std::getline(myfile, line);
		std::vector<std::string> tails = Msplit(std::string(line), '\t');
		tails.pop_back(); // there is an extra \t in the .cspr file, this fixes this problem.
		multiLocs.push_back(tails);
	}
}


/* getChromScaf: Returns which chromosome/scaffold based on the index of the location */
int csprRef::getChrScaf(long id) {
	int i = 0;
	while (id > Chrpos[i]) {
		i++;
	}
	return i;
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
