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

//int argc, const char * argv[]
int main() {
    std::vector<std::string> argv = {"/Users/brianmendoza/Desktop/OFF_QUERY.txt","/Users/brianmendoza/Desktop/ecospCas9.cspr","/Users/brianmendoza/Desktop/eco_off.txt",""};
    // insert code here...
    std::cout << "Running off-target analysis for: " << argv[1] << "\n";
    
    //Open the file and load all the targets from the unique and repeats sections
    csprRef ref_ghost;
    ref_ghost.LoadcsprFile(argv[1]); //change the argv to string when ready for deployment
    
    // Object for running actual off-target algorithm:
    OnTargets otr;
    otr.LoadTargetQuery(argv[0]);
    otr.loadData(&ref_ghost);
    otr.compressed(true);  //set this to whether this should be the compressed or uncompressed sequences for comparison.off
    otr.run_off_algorithm(16); // input should be the number of threads you want to generate
    return 0;
}


