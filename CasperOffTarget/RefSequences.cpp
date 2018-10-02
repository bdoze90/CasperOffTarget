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
 * loadData
 * LoadTargetQuery */

void OnTargets::loadData(std::string f_name) {
    //Open the file and load all the targets from the unique and repeats sections
    ref.LoadcsprFile(f_name);
}

/* This function generates off target scores for all of the sequences that were identifed in the inital searching function: FindSimilars */
void OnTargets::ScoreSettings(std::string settings_filename,std::string output_filename,int mismatches,double thres,bool det, bool avg) {
    FileOp sfile;
    sfile.open(settings_filename);
    scoreGenerator.settings(mismatches,thres,det,avg);
    scoreGenerator.loadCspr(&ref);
    scoreGenerator.setOutputFile(output_filename);
    
}

/* Grab the ontargets from the OFF_QUERY file */
void OnTargets::LoadTargetQuery(std::string query_file) {
    FileOp fileop;
    fileop.open(query_file);
    while (fileop.endFile()) {
        gRNA *query = new gRNA;
        std::vector<std::string> gcs = fileop.getSepLine(50, ',');
        std::string sequence;
        if (is_compressed) {
            //find the end of the sequence with the strand marker:
            if (gcs[1].find('+') != std::string::npos) {
                sequence = gcs[1].substr(0,gcs[1].find('+'));
            } else if (gcs[1].find('-') != std::string::npos) {
                sequence = gcs[1].substr(0,gcs[1].find('-'));
            }
            //set the gRNA object values
            query->set_location(gcs[0]);
            query->set_seq(sequence);
            query->set_score(gcs[2]);
        } else {
            query->set_location(S.compress(std::stol(gcs[0])));
            query->set_seq(S.compress(gcs[1]));
            query->set_score(S.compress(std::stol(gcs[3]))); // index 2 is the PAM, skip this and go to the score
        }
        base_seqs.push_back(query);
    }
    fileop.closeFile();
}
 
/* ALGORITHMIC FUNCTIONS: run_off_algorithm calls instances of findSimilars which searches and calls the scoring function from OffScoring */

void OnTargets::run_off_algorithm(int thr) {
    std::cout << "Running Off Target Algorithm for " << base_seqs.size() << " sequences..." << std::endl;
    std::vector<gRNA*> base = base_seqs;
    /* Run 16 threads to get through all of the gRNAs in question */
    int i = 0;
    while ((base.size()-i)/thr > 0) {
        std::cout << "Percentage of sequences scored: " << (double(i)/double(base.size()))*100 << "%            \r";
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
        i+=thr;
    }
    for (int k=i;k<base.size();k++) {
        findSimilars(base[k]);
    }
    std::cout << "Done searching for putative matches. Beginning scoring process.                 " << std::endl; //spaces are to delete random numbers
}

// This is the target of the thread function
void OnTargets::findSimilars(gRNA* seq) {
    //See if any subset of the sequence appears in the csprRef.reftargets object:
    // break input sequence into 4 subsequences:
    for (int s=0;s<6;s++) {
        std::string compare = seq->get_Csequence().substr(s,3);
        // Need to find all instances of the 3 character seed in the RefString:
        size_t p_hit_loc = ref.AccessRefString()->find(compare,0);
        while(p_hit_loc != std::string::npos) {
            long id = p_hit_loc / 8;
            seq->addMatch(id);
            p_hit_loc = ref.AccessRefString()->find(compare,p_hit_loc+1);
        }
    }
    // check to see if this particular query has any putative off sequence hits:
    if (seq->hasHits()) {
        //now run the scoring algorithm by getting all the information
        scoreGenerator.score(seq);
    }
    delete seq;
}


