//
//  RefSequences.cpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/16/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#include "RefSequences.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <assert.h>
#include "csprRead.hpp"

void OnTargets::readInFromFile(std::string fl) {
    filename = fl;
}

void OnTargets::run_off_algorithm() {
    std::vector<gRNA*> base = base_seqs;
    /*for (int i=0;i<base.size();i++) {
        findSimilars(base[i]);
    }*/
    /* Run 12 threads to get through all of the gRNAs in question */
    for (int i=0;i<base.size();i+=4) {
        std::vector<std::thread*> running_threads;
        std::thread t0([this,&base,&i]() {
            findSimilars(base[i]);
        });
        std::thread t1([this,&base,&i]() {
            findSimilars(base[i+1]);
        });
        std::thread t2([this,&base,&i]() {
            findSimilars(base[i+2]);
        });
        std::thread t3([this,&base,&i]() {
            findSimilars(base[i+3]);
        });
        std::thread t4([this,&base,&i]() {
            findSimilars(base[i+4]);
        });
        std::thread t5([this,&base,&i]() {
            findSimilars(base[i+5]);
        });
        std::thread t6([this,&base,&i]() {
            findSimilars(base[i+6]);
        });
        std::thread t7([this,&base,&i]() {
            findSimilars(base[i+7]);
        });
        std::thread t8([this,&base,&i]() {
            findSimilars(base[i+8]);
        });
        std::thread t9([this,&base,&i]() {
            findSimilars(base[i+9]);
        });
        std::thread t10([this,&base,&i]() {
            findSimilars(base[i+10]);
        });
        std::thread t11([this,&base,&i]() {
            findSimilars(base[i+11]);
        });
        std::thread t12([this,&base,&i]() {
            findSimilars(base[i+12]);
        });
        std::thread t13([this,&base,&i]() {
            findSimilars(base[i+13]);
        });
        std::thread t14([this,&base,&i]() {
            findSimilars(base[i+14]);
        });
        std::thread t15([this,&base,&i]() {
            findSimilars(base[i+15]);
        });
        running_threads.push_back(&t0);
        running_threads.push_back(&t1);
        running_threads.push_back(&t2);
        running_threads.push_back(&t3);
        running_threads.push_back(&t4);
        running_threads.push_back(&t5);
        running_threads.push_back(&t6);
        running_threads.push_back(&t7);
        running_threads.push_back(&t8);
        running_threads.push_back(&t9);
        running_threads.push_back(&t10);
        running_threads.push_back(&t11);
        running_threads.push_back(&t12);
        running_threads.push_back(&t13);
        running_threads.push_back(&t14);
        running_threads.push_back(&t15);
        // Join all the running threads before continuing into the next iteration of the loop
        for (int j=0;j<running_threads.size();j++) {
            running_threads[j]->join();
        }
    }
}

// This is the target of the thread function
void OnTargets::findSimilars(gRNA* seq) {
    // set the grna short object
    if (seq->get_multiflag()) {
        // do nothing
    } else {
        gRNA_short shr;
        shr.base = seq;
        // got to iterate through both vectors
        for (int i=0;i<ref->Targets.size();i++) {
            for (int j=0;j<ref->Targets[i].size();j++) {
                std::string p_hit = ref->Targets[i][j]->gcs();
                // make sure that its not self-matching:
                if (seq->gcs() == p_hit) {
                    continue;
                }
                // break input sequence into 4 subsequences up until the +/-
                for (int s=0;s<3;s++) {
                    std::string compare = seq->gcs().substr(s,4);
                    if (p_hit.find(compare) != std::string::npos) {
                        // add to the preprocessed seq vectors
                        std::string loca = ref->Targets[i][j]->get_location();
                        shr.loc.push_back(loca);
                        shr.chromscaff.push_back(i);
                        shr.hit.push_back(p_hit);
                    }
                }
            }
        }
        // code for just grabbing from output:
        std::string outline = seq->gcs() + " off targets:\n";
        for (int i=0;i<shr.loc.size();i++) {
            outline += (std::to_string(shr.chromscaff[i]) + "," + shr.loc[i] + "," + shr.hit[i] + "\n");
        }
        std::cout << outline;
        preprocessed_seqs.push_back(shr);
    }
}

void OnTargets::generateScore() {
    // Run the full scoring algorithm on all of the preprocessed sequences
    for (int i=0;i<preprocessed_seqs.size();i++) {
        // generate the score here probably faster to run this in the already generated python code
    }
}

