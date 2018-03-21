//
//  OffScoring.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 3/16/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef OffScoring_hpp
#define OffScoring_hpp

#include <stdio.h>
#include <string>
#include <vector>

class OffScoring {
public:
    OffScoring();
    void run(std::string);
    
    void output_off_target_data();
private:
    double generateScore();
private:
    // Structure that stores all the off-target information ready for printing
    struct ScoreInfo {
        std::string ref_sequence;
        std::vector<std::string> off_sequences;
        std::vector<double> scores;
    };
private:
    FILE *stream;
    
    
};

#endif /* OffScoring_hpp */
