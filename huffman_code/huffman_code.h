#ifndef HUFFMAN_COMPRESS
#define HUFFMAN_COMPRESS

#include <map>
#include <vector>
#include <fstream>

#include "huffman_tree_node.h";
#include "h_priority_queue.h";

namespace data_compression {

    class HuffmanCode {
        
        HuffmanTreeNode *root_;
        std::map<char, size_t> frequencies_;
        std::map<char, std::vector<bool>> character_codes_;

        //methods to encode contents of file
        void getFrequencies(std::string target_filename);
        void generateTree();
        void generateCharacterCodes(HuffmanTreeNode *current, std::vector<bool> path);

        public:
        
        std::string encodeFile(std::string target_filename);
        std::string decodeFile(std::string encoded_filename);
    };

}

#endif
