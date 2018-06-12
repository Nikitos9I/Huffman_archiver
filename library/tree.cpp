//
// Created by Nikitos on 10.06.18.
//

#include <vector>
#include <iostream>
#include "tree.h"

tree::node::node(uint64_t cnt, node* left, node* right)
        : cnt(cnt)
        , letter(0)
        , left(left)
        , right(right)  {}

tree::node::node(uint64_t cnt, uint8_t c)
        : cnt(cnt)
        , letter(c)
        , left(nullptr)
        , right(nullptr)  {}

bool compareNodes(tree::node* l, tree::node* r)  {
    std::make_integer_sequence<int, 5>();
    return std::pair<size_t, void*>(l->cnt, l) < std::pair<size_t, void*>(r->cnt, r);
}

bool tree::node::isLeaf() const  {
    return left == nullptr && right == nullptr;
}

void tree::node::dfs(std::vector<std::vector<bool>>& codes, std::vector<bool>& code)  {
    if (isLeaf())
        codes[letter] = code;
    code.push_back(LEFT_CODE);
    if (left)
        left->dfs(codes, code);
    code.pop_back();
    code.push_back(RIGHT_CODE);
    if (right)
        right->dfs(codes, code);
    code.pop_back();
}

void tree::to_tree_code(node* v, binary_code& bin) const  {
    if (v->left) {
        bin.insert_bool(DOWN_CODE);
        to_tree_code(v->left, bin);
    }
    if (v->right) {
        bin.insert_bool(DOWN_CODE);
        to_tree_code(v->right, bin);
    }
    bin.insert_bool(UP_CODE);
}

void tree::to_letters_in_dfs_order(node* v, std::vector<uint8_t>& answer) const  {
    if (v->left)
        to_letters_in_dfs_order(v->left, answer);
    if (v->right)
        to_letters_in_dfs_order(v->right, answer);
    if (v->isLeaf()) {
        answer.push_back(v->letter);
    }
}

void tree::from_letters_in_dfs_order(node* v, std::vector<uint8_t> const& answer, size_t& pos)  {
    if (v->left)
        from_letters_in_dfs_order(v->left, answer, pos);
    if (v->right)
        from_letters_in_dfs_order(v->right, answer, pos);
    if (v->isLeaf()) {
        v->letter = answer[pos++];
    }
}

void tree::from_tree_code(node* v, binary_code& bin)  {
    while (bin.get_next_data() == DOWN_CODE)  {
        if (!v->left) {
            v->left = new node();
            from_tree_code(v->left, bin);
        } else  {
            v->right = new node();
            from_tree_code(v->right, bin);
        }
    }
}

void tree::destruct_dfs(node* v)  {
    if (!v)
        return;
    destruct_dfs(v->left);
    destruct_dfs(v->right);
    delete(v);
}

tree::tree(std::vector<uint64_t>& letter_cnt)
        : root(nullptr)
        , letter_cnt(letter_cnt)
        , letter_code(std::vector<std::vector<bool>> (256, std::vector<bool>()))
        , letter_exists(std::vector<bool> (256, false))  {}

void tree::build()  {
    std::set<node*, bool (*)(node*, node*)> nodes(compareNodes);
    for (uint8_t c = 0; ; ++c)  {
        if (!letter_cnt[c])  {
            letter_exists[c] = false;
            if (c == 255)
                break;
            continue;
        }

        letter_exists[c] = true;
        nodes.insert(new node(letter_cnt[c], c));
        if (c == 255)
            break;
    }

    while (nodes.size() != 1)  {
        node* first = *nodes.begin();
        nodes.erase(first);
        node* second = *nodes.begin();
        nodes.erase(second);
        nodes.insert(new node(first->cnt + second->cnt, first, second));
    }

    if (nodes.size() == 1 && (*nodes.begin())->isLeaf()) {
        root = new node();
        root->left = *nodes.begin();
    } else {
        root = *nodes.begin();
    }

    std::vector<bool> code;
    root->dfs(letter_code, code);
}

void tree::build_from_code(tree_code_t& code)  {
    code.first.bin.start_encoding();
    delete (root);
    root = new node();
    from_tree_code(root, code.first.bin);
    size_t pos = 0;
    from_letters_in_dfs_order(root, code.second.bin.get_code(), pos);
}

tree_code_t tree::get_code() const  {
    binary_code bin;
    to_tree_code(root, bin);
    std::vector<uint8_t> answer;
    to_letters_in_dfs_order(root, answer);
    binary_code letters_code;
    letters_code.build(answer);

    return {
        huffman_data(bin), huffman_data(letters_code)
    };
}

huffman_data tree::encode(std::vector<uint8_t> const& data) const  {
    binary_code code_bin;
    for (uint8_t c : data)
        for (bool bit : letter_code[c])
            code_bin.insert_bool(bit);

    return huffman_data(code_bin);
}

std::vector<uint8_t> tree::decode(huffman_data& code) const  {
    std::vector<uint8_t> data;
    node* v = root;
    for (size_t i = 0; i < code.size; ++i) {
        if (code.bin.get_next_data() == LEFT_CODE) {
            v = v->left;
        } else  {
            v = v->right;
        }

        if (v->isLeaf())
            data.push_back(v->letter), v = root;
    }

    return data;
}

tree::~tree()  {
    destruct_dfs(root);
    letter_cnt.clear();
    letter_code.clear();
    letter_exists.clear();
}
