//
//  main.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/8/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "csprRef.hpp"
#include "RefSequences.hpp"
#include "gRNA.hpp"

/* NOTE:  Connect this to a python overlay in order to run a subprocess.  That way you can call on the CASPER_Seq_Finder for any off-target NAG sequences if needed.
 * The NAG sequences don't have to be stored, just temporarily generated and scanned.  If there are multiple sequences to be checked then it can be stored.
 * Algorithm for NAGs: store them in files for common organisms and endonuclease combinations.  Otherwise just scan the genome for potential off targets irrespective of PAM.
 */

int main(int argc, const char * argv[]) {
    //std::vector<std::string> argv = {"/Users/brianmendoza/Desktop/COFF_QUERY.txt", "True", "/Users/brianmendoza/Dropbox/JGI_CASPER/kfdspCas9.cspr","/Users/brianmendoza/Dropbox/kfd_off.txt","/Users/brianmendoza/Desktop/CASPERinfo"};
    
    //Convert all input into std::string objects:
    std::string query_file = std::string(argv[1]);
    std::string is_query_compressed = std::string(argv[2]);
    std::string cspr_reference = std::string(argv[3]);
    std::string output_file = std::string(argv[4]);
    std::string settings_file = std::string(argv[5]);
    
    std::cout << "Running off-target analysis for: " << cspr_reference << "\n";
    
    // Object for running actual off-target algorithm:
    OnTargets otr;
    std::cout << "Query file compression set to " << is_query_compressed << std::endl;
    if (is_query_compressed.find('T') != std::string::npos || is_query_compressed.find('t') != std::string::npos) {
        otr.compressed(true);
    } else {
        otr.compressed(false);  //set this to whether this should be the compressed or uncompressed sequences for comparison.off
    }
    otr.LoadTargetQuery(query_file);
    otr.loadData(cspr_reference);
    otr.run_off_algorithm(16); // input should be the number of threads you want to generate and the output file
    otr.generateScores(settings_file,output_file);
    return 0;
}


