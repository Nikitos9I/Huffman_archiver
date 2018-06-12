//
// Created by Nikitos on 10.06.18.
//

#include "archivator.h"
#include <iostream>
#include <string>

uint8_t huffman_archivator::to_uint8_t(char c) const {
    return (uint8_t) (((int) c) + 128);
}

char huffman_archivator::to_char(uint8_t c) const {
    return (char) (((int) c) - 128);
}

std::vector<uint8_t> huffman_archivator::to_unsigned(const std::vector<char>& chars) const {
    std::vector<uint8_t> unsigned_chars;
    for (char c : chars) {
        unsigned_chars.emplace_back(to_uint8_t(c));
    }

    return unsigned_chars;
}

std::vector<char> huffman_archivator::to_signed(const std::vector<uint8_t>& unsigned_chars) const {
    std::vector<char> chars;
    for (uint8_t uc : unsigned_chars) {
        chars.emplace_back(to_char(uc));
    }

    return chars;
}

huffman_archivator::huffman_archivator()
        : letter_cnt(std::vector<uint64_t>(256, 0))
        , tree(letter_cnt) {}

void huffman_archivator::inc_letter_cnt(char c, uint64_t delta) {
    letter_cnt[to_uint8_t(c)] += delta;
}

tree_code_t huffman_archivator::get_tree_code() {
    tree.build();
    return tree.get_code();
}

huffman_data huffman_archivator::encrypt(std::vector<char> const& data) const {
    return tree.encode(to_unsigned(data));
}

void huffman_archivator::set_tree_code(tree_code_t& tree_code) {
    tree.build_from_code(tree_code);
}

std::vector<char> huffman_archivator::decrypt(huffman_data& code) const {
    return to_signed(tree.decode(code));
}

huffman_archivator::~huffman_archivator() {
    letter_cnt.clear();
}