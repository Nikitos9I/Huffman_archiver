//
// Created by Nikitos on 10.06.18.
//

#include "innerHuffman.h"
#include "constants.h"

huffman_data::huffman_data()
        : huffman_data::huffman_data(binary_code())  {}

huffman_data::huffman_data(size_t size, const binary_code& bin)
        : size(size)
        , bin(bin)  {}

huffman_data::huffman_data(const binary_code& bin)
        : huffman_data::huffman_data(bin.get_size(), bin)  {}

size_t huffman_data::get_size(my_buffered_reader& fin)  {
    size = 0;
    char c;
    while (fin.get(c)) {
        if (c == ' ')
            break;
        size = 10 * size + (c - '0');
    }
    return size;
}

bool huffman_data::read(my_buffered_reader& fin)  {
    size = 0;
    bin = binary_code();
    get_size(fin);

    if (size == 0) {
        return false;
    }

    size_t rest = (size & 7);
    char c;
    while (bin.get_size() < size - rest && fin.get(c)) {
        bin.insert_symbol((uint8_t) (((int)c) + 128));
    }

    if (rest && fin.get(c)) {
        uint8_t uc = (uint8_t)(((int) c) + 128);
        for (size_t i = 7; i > 7 - rest; --i)
            bin.insert_bool((uc & (1 << i)) != 0);
    }

    return true;
}

void huffman_data::print(my_buffered_writer& fout) const  {
    huffman_data code = *this;
    fout.put(code.size);
    fout.put(' ');
    auto uint8_code = code.bin.get_code();
    std::string string_code;
    for (uint8_t c : uint8_code) {
        string_code.push_back((char) (((int) c) - 128));
    }

    fout.put(string_code);
}

tree_code_t::tree_code_t()
        : tree_code_t::tree_code_t(huffman_data(), huffman_data())  {}

tree_code_t::tree_code_t(huffman_data const& f, huffman_data const& s)
        : first(f)
        , second(s)  {}

bool tree_code_t::read(my_buffered_reader& fin)  {
    if (first.read(fin) && second.read(fin)) {
        return true;
    }

    return false;
}

void tree_code_t::print(my_buffered_writer& fout) const  {
    first.print(fout);
    second.print(fout);
}