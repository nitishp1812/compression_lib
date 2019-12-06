#ifndef PRIORITY_QUEUE_HUFFMAN
#define PRIORITY_QUEUE_HUFFMAN

#include <vector>

#include "huffman_tree_node.h"

namespace data_compression {

    class PriorityQueue {

        std::vector<HuffmanTreeNode*> queue;

        public:

        void push(char value, int frequency);
        HuffmanTreeNode* pop();
        int size();
    };
}

#include "h_priority_queue.hpp"

#endif
