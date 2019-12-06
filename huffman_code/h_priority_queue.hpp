#include "h_priority_queue.h";

void data_compression::PriorityQueue::push(char data, int frequency) {
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

data_compression::HuffmanTreeNode* data_compression::PriorityQueue::pop() {
    HuffmanTreeNode* removed_node = this->queue[0];

    this->queue.erase(this->queue.begin());

    return removed_node;
}

int data_compression::PriorityQueue::size() {
    return this->queue.size();
}
