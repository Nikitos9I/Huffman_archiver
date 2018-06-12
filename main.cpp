//
// Created by Nikitos on 10.06.18.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include "archivator.h"
#include "bufferedReader.h"
#include <cstring>
#include "binaryCode.h"
#include "tester.h"
#include "constants.h";

uint64_t file_size(std::string name) {
    std::ifstream fin(name, std::ios::binary | std::ios::ate);
    uint64_t ans = (uint64_t) fin.tellg();
    fin.close();
    return ans;
}

void encrypt(char* argv[]) {
    uint64_t old_size = file_size(argv[2]), new_size = 0;

    my_buffered_reader fin;
    fin.open(argv[2]);
    if (!fin)
        throw std::runtime_error("input file open failed");
    my_buffered_writer fout;
    fout.open(argv[3]);
    if (!fout)
        throw std::runtime_error("output file open failed");
    huffman_archivator archivator;

    std::cout << "encrypting...\n";

    char symbol;

    bool wasSymbol = false;
    while (fin.get(symbol)) {
        wasSymbol = true;
        archivator.inc_letter_cnt(symbol, 1);
    }

    fin.close();
    fin.open(argv[2]);

    if (!wasSymbol) {
        std::cout << "done (" << 0 << " blocks total, old file size : "
                  << 1.0 * old_size / 1024.0 << " kbs , new file size :"
                  << 1.0 * new_size / 1024.0 << " kbs, compressing ratio :"
                  << 0 << "%"
                  << ")\ntime : " << (double) clock() / 1000000.0 << " sec.\n"
                  << "(mb per sec : " << 1.0 * old_size / (double) clock() << ")\n";
        fin.close();
        fout.put("");
        fout.close();
        return;
    }

    tree_code_t tree_code = archivator.get_tree_code();
    tree_code.print(fout);
    std::vector<char> symbols_block;
    size_t block_cnt = 0;

    while (!fin.eof()) {
        ++block_cnt;
        symbols_block.clear();
        for (size_t i = 0; i < block_size && fin.get(symbol); ++i)
            symbols_block.push_back(symbol);
        auto code_block = archivator.encrypt(symbols_block);
        code_block.print(fout);
    }

    fin.close();
    fout.close();
    new_size = file_size(argv[3]);
    std::cout << "done (" << block_cnt << " blocks total, old file size : "
              << 1.0 * old_size / 1024.0 << " kbs , new file size :"
              << 1.0 * new_size / 1024.0 << " kbs, compressing ratio :"
              << 100.0 * ((double) old_size - (double) new_size) / (double) old_size << "%"
              << ")\ntime : " << (double) clock() / 1000000.0 << " sec.\n"
              << "(mb per sec : " << 1.0 * old_size / (double) clock() << ")\n";
}

void decrypt(char* argv[]) {
    my_buffered_reader fin;
    uint64_t code_size = file_size(argv[2]);
    fin.open(argv[2]);

    if (!fin)
        throw std::runtime_error("input file open failed");
    my_buffered_writer fout;
    fout.open(argv[3]);
    if (!fout)
        throw std::runtime_error("output file open failed");
    huffman_archivator archivator;

    std::cout << "decrypting...\n";
    tree_code_t tree_code;

    if (!tree_code.read(fin)) {
        fout.put("");
        std::cout << "done.\ntime : " << (double) clock() / 1000000.0 << " sec.\n"
                  << "(mb per sec : " << 1.0 * code_size / (double) clock() << ")\n";
        fin.close();
        fout.close();
        return;
    }

    archivator.set_tree_code(tree_code);
    huffman_data data_block;
    size_t block_nmb = 0;
    while (!fin.eof()) {
        ++block_nmb;
        data_block.read(fin);
        std::vector<char> symbols = archivator.decrypt(data_block);
        for (char c : symbols)
            fout.put(c);
    }

    std::cout << "done.\ntime : " << (double) clock() / 1000000.0 << " sec.\n"
              << "(mb per sec : " << 1.0 * code_size / (double) clock() << ")\n";
    fin.close();
    fout.close();
}

void solve(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "illegal number of arguments" << std::endl;
    }

    if (!strcmp(argv[1], "-encrypt")) {
        encrypt(argv);
    } else if (!strcmp(argv[1], "-decrypt")) {
        decrypt(argv);
    } else {
        std::cout << "illegal argument: press '-encrypt' or '-decrypt'";
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(nullptr);

    if (argc == 2 && !strcmp(argv[1], "-test")) {
        huffman_tester tester;
        tester.test();
        return 0;
    }

    try {
        solve(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}