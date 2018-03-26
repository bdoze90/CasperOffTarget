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

class gRNA {
public:
    // setting information:
    void set_location(std::string s) { compressed_location = s;}
    void set_score(std::string s) { compressed_score = s;}
    void set_seq(std::string s) {compressed_seq = s;}
    void set_multiflag(bool b) {multiflag = b;}
    // retrieving information:
    std::string get_location();
    int get_score();
    std::string get_sequence();
    std::string gcs() {return compressed_seq;}
    bool get_multiflag() {return multiflag;}
    
private:
    std::string compressed_location;
    std::string compressed_score;
    std::string compressed_seq;
    bool multiflag;
};

#endif /* gRNA_hpp */
