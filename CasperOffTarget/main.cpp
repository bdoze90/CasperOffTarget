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
#include "csprRead.hpp"
#include "RefSequences.hpp"
#include "gRNA.hpp"

/* NOTE:  Connect this to a python overlay in order to run a subprocess.  That way you can call on the CASPER_Seq_Finder for any off-target NAG sequences if needed.
 * The NAG sequences don't have to be stored, just temporarily generated and scanned.  If there are multiple sequences to be checked then it can be stored.
 * Algorithm for NAGs: store them in files for common organisms and endonuclease combinations.  Otherwise just scan the genome for potential off targets irrespective of PAM.
 */

//int argc, const char * argv[]
int main() {
    std::vector<std::string> argv = {"True","/Users/brianmendoza/Dropbox/ecospCas9.cspr","/Users/brianmendoza/Desktop/eco_off.txt",""};
    // insert code here...
    std::cout << "Hello, World!\n";
    //Open the file and load all the targets from the unique and repeats sections
    csprRead ref_ghost;
    ref_ghost.setFile(argv[1]); //change the argv to string
    ref_ghost.loadTargets();
    //Load all the desired sequences to check for off targets.  If this is comprehensive (a complete index) then will need to run a loop of loops
    std::string a = argv[0];
    OnTargets otr;
    otr.loadRef(&ref_ghost);
    if (a == "False") {
        otr.readInFromFile(argv[2]);
        otr.run_off_algorithm();
    } else { // This is a comphrehensive off target analysis
        for (int i=0;i<ref_ghost.Targets.size();i++) {
            otr.set_base_seqs(ref_ghost.Targets[i]);
            std::cout << "Scaffold/Chromosome # " + std::to_string(i+1) + " off target analysis: \n";
            otr.run_off_algorithm();
        }
    }
    return 0;
}


