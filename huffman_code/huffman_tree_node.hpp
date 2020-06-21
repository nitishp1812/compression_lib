#ifndef HUFFMAN_TREE_NODE
#define HUFFMAN_TREE_NODE

namespace data_compression {
    struct HuffmanTreeNode {
        char element_;
        HuffmanTreeNode *left_, *right_;
        int weight_;

        HuffmanTreeNode(char data, int frequency): 
            element_(data), weight_(frequency), left_(nullptr), right_(nullptr) {};
    };

    struct HuffmanNodeCompare {
        bool operator()(HuffmanTreeNode* p1, HuffmanTreeNode* p2) {
            return p1->weight_ < p2->weight_;
        }
    };
}

#endif