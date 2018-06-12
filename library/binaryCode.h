//
// Created by Nikitos on 10.06.18.
//

#ifndef HUFFMAN_ARCHIVATOR_BINARYCODE_H
#define HUFFMAN_ARCHIVATOR_BINARYCODE_H

#include <vector>
#include <cstdint>


class binary_code {
    private:
        std::vector<bool> data;
        size_t pos;
    public:
        binary_code();
        void insert_symbol(uint8_t);
        void build(std::vector<uint8_t>&);
        std::vector<uint8_t> get_code();
        void start_encoding();
        bool get_next_data();
        void insert_bool(bool);
        size_t get_size() const;
        ~binary_code();

        std::vector<bool> get_data() {
            return data;
        }
};


#endif //HUFFMAN_ARCHIVATOR_BINARYCODE_H
