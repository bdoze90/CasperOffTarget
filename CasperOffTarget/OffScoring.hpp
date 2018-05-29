//
//  OffScoring.hpp
//  CasperOffTarget
//
//  Created by Brian Mendoza on 5/29/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef OffScoring_hpp
#define OffScoring_hpp

#include <stdio.h>
#include <vector>
#include <string>

class OffScoring {
public:
    OffScoring();
    
private:
    void initializeMatrix(std::string matrix_file);
    void initializeScores();
};

#endif /* OffScoring_hpp */
