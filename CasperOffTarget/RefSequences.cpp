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
#include "csprRef.hpp"
#include "OffScoring.hpp"

/* CONTAINER AND DATA MANIPULATION FUNCTIONS
 * LoadTargetQuery */

void OnTargets::LoadTargetQuery(std::string query_file) {
    FileOp fileop;
    fileop.open(query_file);
 
/* ALGORITHMIC FUNCTIONS
 * run_off_algorithm
 * findSimilars
 * generateScores */

void OnTargets::run_off_algorithm(int thr) {
    std::vector<gRNA*> base = base_seqs;
    /*for (int i=0;i<base.size();i++) {
        findSimilars(base[i]);
    }*/
    /* Run 16 threads to get through all of the gRNAs in question */
    for (int i=0;i<base.size();i+=thr) {
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
    //See if any subset of the sequence appears in the csprRef.reftargets object:
    // break input sequence into 4 subsequences:
    for (int s=0;s<3;s++) {
        std::string compare = seq->gcs().substr(s,4);
        unsigned long p_hit_loc = ref->RefTargets.find(compare);
        if (p_hit_loc != std::string::npos) {
            long id = p_hit_loc % 9;
            seq->loadPutOff(ref->getLoc(id),ref->getChrScaf(id),ref->getScore(id));
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
    OffScoring oscore;
    for (int i=0;i<preprocessed_seqs.size();i++) {
        oscore.score(preprocessed_seqs[i]);
    }
}

