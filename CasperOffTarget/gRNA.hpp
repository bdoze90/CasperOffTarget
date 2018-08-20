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
#include "Compression.h"

class gRNA {
public:
    // setting information:
    void set_location(std::string s) { compressed_location = s;}
    void set_score(std::string s) { score = decompress(s);}
    void set_seq(std::string s) {compressed_seq = s;}
    // retrieving information:
    std::string get_Clocation();
    int get_score();
    std::string get_Csequence();
    std::string gcs() {return compressed_seq;}
    // setting off target information
    void loadPutOff(std::string, std::string);
    
private:
    //Class containing decompression algorithms
    Compression Compressor;
    
private:
    std::string compressed_location;
    int score;
    std::string compressed_seq;
    long decompress(std::string comp);
    
// Off Target Identities
private:
    std::vector<std::string> hits;
    std::vector<int> chromscaff;
    std::vector<std::string> loc;

};

#endif /* gRNA_hpp */
