#include "huffman_code.h"

using namespace data_compression;

void HuffmanCode::getFrequencies(std::string target_filename) {
    std::ifstream target_file(target_filename);

    while(!target_file) {
        std::string line;
        std::getline(target_file, line);

        for (char c: line) {
            if (c == '\u0000') {
                continue;
            }
            this->frequencies_[c]++;
        }
    }
}

void HuffmanCode::generateTree() {
    PriorityQueue queue;
    for (auto it = this->frequencies_.begin(); it != this->frequencies_.end(); ++it) {
        queue.push(it->first, it->second);
    }

    while (queue.size() != 1) {
        HuffmanTreeNode *first_node, *second_node;

        first_node = queue.pop();
        second_node = queue.pop();

        int combined_weight = first_node->weight_ + second_node->weight_;

        queue.push('\u0000', combined_weight);
    }

    this->root_ = queue.pop();
}

void HuffmanCode::generateCharacterCodes(HuffmanTreeNode *current, std::vector<bool> path) {
    if (current->element_ != '\u0000') {
        this->character_codes_[current->element_] = path;
        return;
    }

    std::vector<bool> left_path(path);
    left_path.push_back(false);

    std::vector<bool> right_path(path);
    right_path.push_back(true);

    delete &path;

    generateCharacterCodes(current->left_, left_path);
    generateCharacterCodes(current->right_, right_path);
}

std::string HuffmanCode::encodeFile(std::string target_filename) {
    this->getFrequencies(target_filename);
    this->generateTree();

    HuffmanTreeNode *current = this->root_;
    this->generateCharacterCodes(current, std::vector<bool>());
}
