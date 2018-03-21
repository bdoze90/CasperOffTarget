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
#include "OffScoring.hpp"
#include "gRNA.hpp"

void my_thread_fn (std::string pass, OffScoring ofs) {
    ofs.run(pass);
}

//int argc, const char * argv[]
int main() {
    std::vector<std::string> argv = {"False","/Users/brianmendoza/Dropbox/ecospCas9.cspr","/Users/brianmendoza/Desktop/eco_off.txt",""};
    // insert code here...
    std::cout << "Hello, World!\n";
    //Open the file and load all the targets from the unique and repeats sections
    csprRead ref_ghost;
    ref_ghost.setFile(argv[1]); //change the argv to string
    ref_ghost.loadTargets();
    //Load all the desired sequences to check for off targets.  If this is comprehensive (a complete index) then will need to run a loop of loops
    bool comp_off;
    std::string a = argv[0];
    if (a == "False") {
        comp_off = false;
    }
    OnTargets otr(comp_off, argv[3]);
    OffScoring off;

    
    //Run through all off targets.  This is where the threading comes in by generating a new thread for each of the off targets you desire.  Break this up into max 100 threads so that you don't overgenerate threads especially if you are running a complete target index.
    std::vector<std::thread> running_threads; //store all the threads that are currently running
    for (std::vector<std::vector<std::string>>::iterator it = otr.ref_seq_buckets.begin() ; it != otr.ref_seq_buckets.end(); ++it) {
        std::vector<std::string> cur_set = *it;
        for (int j=0;j<cur_set.size();j++) {
            std::thread t1 (my_thread_fn,cur_set.at(j),off);
            running_threads.push_back(t1);
        }
        for (int k=0;k<100;k++) {
            running_threads[k].join();
        }
        cur_set.clear();
    }
    
    //In each thread need to first seed to generate the subset of targets to then run iterative scoring over.
    
    return 0;
}


