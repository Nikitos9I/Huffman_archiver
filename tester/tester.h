//
// Created by Nikitos on 10.06.18.
//

#ifndef HUFFMAN_ARCHIVatorOR_TESTER_H
#define HUFFMAN_ARCHIVatorOR_TESTER_H

#include "archivator.h"
#include <iostream>
#include <fstream>
#include <functional>

class huffman_tester {
    private:
        huffman_archivator archivator;
        size_t block_size = 4 * 1024;
        void encrypt(std::string const& name1, std::string const& name2);
        void decrypt(std::string const& name1, std::string const& name2);
        int test_item(bool should_encrypt);
    public:
        void test();
};


#endif //HUFFMAN_ARCHIVatorOR_TESTER_H
