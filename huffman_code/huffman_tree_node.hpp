#ifndef HUFFMAN_TREE_NODE
#define HUFFMAN_TREE_NODE

namespace data_compression {
    struct HuffmanTreeNode {
        unsigned element_;
        HuffmanTreeNode *left_, *right_;
        unsigned weight_;
        bool internal_;

        HuffmanTreeNode(unsigned data, unsigned frequency, bool internal): 
            element_(data), weight_(frequency), left_(nullptr), right_(nullptr), internal_(internal) {};
    };

    struct HuffmanNodeCompare {
        bool operator()(HuffmanTreeNode* p1, HuffmanTreeNode* p2) {
            return p1->weight_ > p2->weight_;
        }
    };
}

#endif