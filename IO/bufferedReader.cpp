//
// Created by Nikitos on 10.06.18.
//

#include "bufferedReader.h"

my_buffered_reader::my_buffered_reader() {
    buffer = new char[buffer_size];
}

bool my_buffered_reader::get(char& c) {
//    if (fin.eof()) {
//        return false;
//    }

    if (pos == size) {
        if (fin.eof())
            return false;
        pos = 0;
        fin.read(buffer, buffer_size);
        size = (size_t) fin.gcount();

        if (size == 0) {
            return false;
        }
    }

    c = buffer[pos++];
    return true;
}

bool my_buffered_reader::eof() {
    return size == pos && fin.eof();
}

void my_buffered_reader::open(std::string const& filename) {
    fin.open(filename);
}

void my_buffered_reader::close() {
    fin.close();
}

bool operator!(my_buffered_reader const& r) {
    return !r.fin;
}

my_buffered_reader::~my_buffered_reader() {
    delete[] buffer;
}

my_buffered_writer::my_buffered_writer() {
    buffer = new char[buffer_size];
}

void my_buffered_writer::put(char c) {
    fout.put(c);
}

void my_buffered_writer::put(size_t x) {
    fout << x;
}

void my_buffered_writer::put(std::string const& s) {
    fout << s;
}

void my_buffered_writer::open(std::string const& filename) {
    fout.open(filename);
}

void my_buffered_writer::close() {
    fout.close();
}

bool operator!(my_buffered_writer const& w) {
    return !w.fout;
}

my_buffered_writer::~my_buffered_writer() {
    delete [] buffer;
}