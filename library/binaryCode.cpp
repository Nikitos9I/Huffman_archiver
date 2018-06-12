//
// Created by Nikitos on 10.06.18.
//

#include <iostream>
#include "binaryCode.h"
#include <cstdlib>

binary_code::binary_code()
        : data(std::vector<bool>())
        , pos(0) {}

void binary_code::insert_symbol(uint8_t c){
    for (int i = 7; i >= 0; --i){
        data.push_back((c & (1 << i)) != 0);
    }
}

void binary_code::build(std::vector<uint8_t>& symbols) {
    data.clear();
    for (unsigned char symbol : symbols)
        insert_symbol(symbol);
}

std::vector<uint8_t> binary_code::get_code() {
    std::vector <uint8_t> code;
    uint8_t cur = 0;
    int deg = 7;
    for (bool bit : data){
        cur += (((int) bit) << deg);
        --deg;
        if (deg < 0)
            deg = 7, code.push_back(cur), cur = 0;
    }

    if (deg != 7)
        code.push_back(cur);

//    for (int i = 0; i < code.size(); i ++) {
//        std::cout << code[i];
//    }
//    std::cout << std::endl;

    return code;
}

void binary_code::start_encoding() {
    pos = 0;
}

bool binary_code::get_next_data() {
    if (pos == data.size()){
        std::string explanation = "real size = " + std::to_string(data.size()) + "\n";
        explanation += "chars : ";
        std::vector<uint8_t> ttt = get_code();
        for (uint8_t tt : ttt)
            explanation.push_back((char) ((int) tt - 128));
        explanation += "\nbit sequence : ";
        for (bool bit : data)
            explanation += (bit ? "1 " : "0 ");
    }

    return data[pos++];
}

void binary_code::insert_bool(bool bit) {
    data.push_back(bit);
}

size_t binary_code::get_size() const {
    return data.size();
}

binary_code::~binary_code() {
    data.clear();
}