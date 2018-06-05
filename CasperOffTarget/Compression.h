//
//  Compression.h
//  CasperOffTarget
//
//  Created by Brian Mendoza on 5/29/18.
//  Copyright © 2018 University of Tennessee. All rights reserved.
//

#ifndef Compression_h
#define Compression_h

class Compression {
public:
    /* Function for converting number to base64 */
    std::string compress_sequence( long number, int base) {
        std::string base64set = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789=/"; //base64 modification so +- can be used for strand direction
        int rem;
        std::string newNum;
        while(number>=base) {
            rem = number%base;
            number = number/base;
            newNum = base64set[rem] + newNum;
        }
        newNum = base64set[number] + newNum;
        return newNum; //this returns the string in reverse...
    }
    /* END compress_sequence */
    
    /* Function for decompressing base64 into base 10 */
    long decompress(std::string cseq) {
        long base10seq;
        
    }
    
    /* Function for decompressing into a sequence from base64 */
    std::string decompress_sequence(std::string cseq, bool seq) {
        std::string uncompressed;
        //do the reverse binary transition from base-10 to base-4
        while (cseq >= 4) {
            int rem = cseq%4;
            cseq = cseq/4;
            uncompressed += convertBase4toChar(rem);
        }
        uncompressed += convertBase4toChar(cseq);
        for (int i=uncompressed.size(); i<exp_len; i++) {
            uncompressed += 'A';
        }
        return uncompressed;
    }
    /* END decompress sequence function */
};

#endif /* Compression_h */
