#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <vector>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <bitset>

#include "../bit_io/bit_io.h"
#include "huffman_tree_node.hpp"

namespace data_compression {

    class HuffmanCode {
        private:
        int num_chars_;
        HuffmanTreeNode *root_;
        std::vector<size_t> frequencies_;
        std::vector<unsigned> lengths_;
        std::unordered_map<unsigned, std::string> character_codes_;
        void clear(HuffmanTreeNode* node);
        void generateCodeLengths(HuffmanTreeNode* node, unsigned curr_length);
        void generateCharacterCodes(HuffmanTreeNode* node, std::string code);

        public:
        HuffmanCode(unsigned num_chars);
        ~HuffmanCode();
        void getFrequencies(std::string target_filename);
        void generateTree();
        void generateCodeLengths();
        void getCanonicalTree();
        void generateCharacterCodes();
        void writeToFile(std::string in_filename, std::string out_filename, BitOutputStream& out_stream);
        void readCodeLengths(BitInputStream& in_stream);
        unsigned readNextCharacter(BitInputStream& in_stream);
    };

    void huffman_encode(std::string in_filename, std::string out_filename);
    void huffman_decode(std::string in_filename, std::string out_filename);
}

#endif
