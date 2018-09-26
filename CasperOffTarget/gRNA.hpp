//
//  gRNA.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/19/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef gRNA_hpp
#define gRNA_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <thread>
#include "CSeqTranslate.hpp"

class gRNA {
public:
    // setting information:
    void set_location(std::string s) { compressed_location = s;}
    void set_score(std::string s) { score = S.decompress_location(s);}
    void set_seq(std::string s) {compressed_seq = s;}
    // retrieving information:
    std::string get_Clocation();
    int get_score() {return double(score);} // Convert to double so that the return value can be a fraction.
    std::string get_Csequence() {return compressed_seq;}
    std::string get_sequence() {return S.decompress(compressed_seq,20);}
    long get_location() {return S.decompress_location(compressed_location);}
    // setting off target information
    void addMatch(long id) {putative_off_seq_ids.push_back(id);}
    std::vector<long> returnPutativeMatches() {return putative_off_seq_ids;}
    
    //Tells you whether there were any putative hits found:
    bool hasHits();
    int numHits() {return putative_off_seq_ids.size();}
    
    long get10seq() {return S.decompress_location(compressed_seq);}
    
private:
    //Class containing decompression algorithms
    SeqTranslate S;
    
    struct offtargetwithscore {
        int chromscaff;
        long position;
        std::string sequence;
        double off_score;
    };
    
    std::vector<offtargetwithscore> offhits;  // Stores all the offtarget scores for the putative off_sequences
    
private:
    std::string compressed_location;
    int score;
    std::string compressed_seq;
    
    // Below is the container that keeps track of all the matches that the algorithm finds for this target
    std::vector<long> putative_off_seq_ids;
    
public:
    // Adding to off target vector offscores:
    void addOffScore(double, int, long, std::string);
    std::string offtargetscores();

};

#endif /* gRNA_hpp */
