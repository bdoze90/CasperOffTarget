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

//int argc, const char * argv[]
int main() {
    std::vector<std::string> argv = {"False","/Users/brianmendoza/Dropbox/eco.fna","",""};
    // insert code here...
    std::cout << "Hello, World!\n";
    //Open the file and load all the targets from the unique and repeats sections
    csprRead ref_ghost;
    ref_ghost.setFile(argv[1]);
    ref_ghost.loadTargets();
    //Load all the desired sequences to check for off targets.  If this is comprehensive (a complete index) then will need to run a loop of loops
    bool comp_off;
    std::string a = argv[0];
    if (a == "False") {
        comp_off = false;
    }
    
    //Run through all off targets.  This is where the threading comes in by generating a new thread for each of the off targets you desire.  Break this up into max 100 threads so that you don't overgenerate threads especially if you are running a complete target index.
    
    //In each thread need to first seed to generate the subset of targets to then run iterative scoring over.
    
    return 0;
}
