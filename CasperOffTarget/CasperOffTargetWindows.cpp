// CasperOffTargetWindows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//  main.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/8/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "csprRef.h"
#include "RefSequences.h"
#include "gRNA.h"

/* NOTE:  Connect this to a python overlay in order to run a subprocess.  That way you can call on the CASPER_Seq_Finder for any off-target NAG sequences if needed.
 * The NAG sequences don't have to be stored, just temporarily generated and scanned.  If there are multiple sequences to be checked then it can be stored.
 * Algorithm for NAGs: store them in files for common organisms and endonuclease combinations.  Otherwise just scan the genome for potential off targets irrespective of PAM.
 */

 //int argc, const char * argv[]
int main(int argc, const char * argv[]) {
	//std::vector<std::string> argv = {"casperofftargetexec","C:\\Users\\Trinh Lab\\Desktop\\cpppch.txt", "True", "C:\\Users\\Trinh Lab\\Desktop\\bsu_spCas9.cspr","C:\\Users\\Trinh Lab\\Desktop\\MYOUPUT.txt","C:\\Users\\Trinh Lab\\Desktop\\CASPERinfo.txt", "4", "0.05", "False", "True" };

	//Convert all input into std::string objects:
	std::string query_file = std::string(argv[1]);
	std::string is_query_compressed = std::string(argv[2]);
	std::string cspr_reference = std::string(argv[3]);
	std::string output_file = std::string(argv[4]);
	std::string settings_file = std::string(argv[5]);
	//Convert settings inputs into appropriate values:
	std::cout << argv[6] << std::endl;
	int NUM_MISMATCHES = std::stoi(std::string(argv[6]));
	double THRESHOLD = std::stod(std::string(argv[7]));
	bool detailed = false;
	bool average = false;
	if (std::string(argv[8]).find('T') != std::string::npos) {
		detailed = true;
	}
	if (std::string(argv[9]).find('T') != std::string::npos) {
		average = true;
	}

	std::cout << "Running off-target analysis for: " << cspr_reference << "\n";

	// Object for running actual off-target algorithm:
	OnTargets otr;
	std::cout << "Query file compression set to " << is_query_compressed << std::endl;
	if (is_query_compressed.find('T') != std::string::npos || is_query_compressed.find('t') != std::string::npos) {
		otr.compressed(true);
	}
	else {
		otr.compressed(false);  //set this to whether this should be the compressed or uncompressed sequences for comparison.off
	}
	otr.LoadTargetQuery(query_file);
	otr.loadData(cspr_reference);
	otr.ScoreSettings(settings_file, output_file, NUM_MISMATCHES, THRESHOLD, detailed, average);

	otr.run_off_algorithm(16); // input should be the number of threads you want to generate and the output file
	std::cout << "All scores generated. Output file located at: " << output_file << std::endl;
	return 0;
}


