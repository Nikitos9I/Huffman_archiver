//
// Created by Nikitos on 10.06.18.
//

#ifndef HUFFMAN_ARCHIVATOR_ARCHIVATOR_H
#define HUFFMAN_ARCHIVATOR_ARCHIVATOR_H


#include "tree.h"
#include "binaryCode.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include "innerHuffman.h"

class huffman_archivator {
    private:
        std::vector<uint64_t> letter_cnt;
        tree tree;
        uint8_t to_uint8_t(char) const;
        char to_char(uint8_t) const;
        std::vector<uint8_t> to_unsigned(const std::vector<char>&) const;
        std::vector<char> to_signed(const std::vector<uint8_t>&) const;

    public:
        huffman_archivator();
        void inc_letter_cnt(char, uint64_t);
        tree_code_t get_tree_code();
        huffman_data encrypt(std::vector<char> const&) const;
        void set_tree_code(tree_code_t&);
        std::vector<char> decrypt(huffman_data&) const;
        ~huffman_archivator();
};


#endif //HUFFMAN_ARCHIVATOR_ARCHIVATOR_H
