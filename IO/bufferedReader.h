//
// Created by Nikitos on 10.06.18.
//

#ifndef HUFFMAN_ARCHIVATOR_BUFFEREDREADER_H
#define HUFFMAN_ARCHIVATOR_BUFFEREDREADER_H


#include <fstream>
#include <iostream>
#include <string>
#include "constants.h"

class my_buffered_reader  {
    private:
        std::ifstream fin;
        char* buffer;
        size_t pos = 0;
        size_t size = 0;
    public:
        my_buffered_reader();
        bool get(char& c);
        bool eof();
        void open(std::string const& filename);
        void close();
        friend bool operator !(my_buffered_reader const&);
        ~my_buffered_reader();
    };

class my_buffered_writer  {
    private:
        std::ofstream fout;
        char* buffer;
    public:
        my_buffered_writer();
        void put(char c);
        void put(size_t x);
        void put(std::string const& s);
        void open(std::string const& filename);
        void close();
        friend bool operator !(my_buffered_writer const&);
        ~my_buffered_writer();
    };



#endif //HUFFMAN_ARCHIVATOR_BUFFEREDREADER_H
