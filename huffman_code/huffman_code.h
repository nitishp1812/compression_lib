#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <map>
#include <vector>
#include <fstream>
#include <queue>

#include "huffman_tree_node.hpp"

namespace data_compression {

    class HuffmanCode {
        
        HuffmanTreeNode *root_;
        std::map<char, size_t> frequencies_;
        std::map<char, std::vector<bool>> character_codes_;

        void generateCharacterCodes(HuffmanTreeNode *current, std::vector<bool> path);

        public:
        //methods to encode contents of file
        void getFrequencies(std::string target_filename);
        void generateTree();
        void generateCharacterCodes();
    };


    void huffman_encode(std::string in_filename, std::string out_filename);
    void huffman_decode(std::string in_filename, std::string out_filename);

}

#endif
