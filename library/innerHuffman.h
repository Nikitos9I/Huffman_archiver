//
// Created by Nikitos on 7.06.18.
//

#ifndef HUFFMAN_ARCHIVATOR_INNERHUFFMAN_H
#define HUFFMAN_ARCHIVATOR_INNERHUFFMAN_H


#include <cstdio>
#include <iostream>
#include <fstream>
#include "binaryCode.h"
#include "bufferedReader.h"

class huffman_data {

    private:
        size_t get_size(my_buffered_reader&);
    public:
        size_t size;
        binary_code bin;
        huffman_data();
        huffman_data(size_t, const binary_code&);
        huffman_data(const binary_code&);

        bool read(my_buffered_reader&);
        void print(my_buffered_writer&) const;
    };

    struct tree_code_t {
        huffman_data first;
        huffman_data second;
        tree_code_t();
        tree_code_t(huffman_data const&, huffman_data const&);

        bool read(my_buffered_reader&);
        void print(my_buffered_writer&) const;
    };


#endif //HUFFMAN_ARCHIVATOR_INNERHUFFMAN_H
