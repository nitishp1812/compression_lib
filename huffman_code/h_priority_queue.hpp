#include "h_priority_queue.h";

void huffman_code::PriorityQueue::push(char data, int frequency) {
    HuffmanTreeNode *new_node = new HuffmanTreeNode(data, frequency);

    if (this->queue.size() == 0) {
        this->queue.push_back(new_node);
        return;
    }

    for (auto it = this->queue.begin(); it != this->queue.end(); ++it) {
        if ((*it)->weight_ > frequency) {
            this->queue.insert(it, new_node);
            break;
        }
    }
}

huffman_code::HuffmanTreeNode* huffman_code::PriorityQueue::pop() {
    HuffmanTreeNode* removed_node = this->queue[0];

    this->queue.erase(this->queue.begin());

    return removed_node;
}

int huffman_code::PriorityQueue::size() {
    return this->queue.size();
}
