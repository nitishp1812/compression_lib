#include "huffman_code.h"

void data_compression::HuffmanCode::getFrequencies(std::string target_filename) {
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

void data_compression::HuffmanCode::generateTree() {
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, HuffmanNodeCompare> queue;
    for (auto it = this->frequencies_.begin(); it != this->frequencies_.end(); ++it)
        queue.push(new HuffmanTreeNode(it->first, it->second));

    while (queue.size() != 1) {
        HuffmanTreeNode *first_node, *second_node;

        first_node = queue.top();
        queue.pop();
        second_node = queue.top();
        queue.pop();

        int combined_weight = first_node->weight_ + second_node->weight_;

        queue.push(new HuffmanTreeNode('\u0000', combined_weight));
    }

    this->root_ = queue.top();
    queue.pop();
}

void data_compression::HuffmanCode::generateCharacterCodes(HuffmanTreeNode *current, std::vector<bool> path) {
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

void data_compression::HuffmanCode::generateCharacterCodes() {
    HuffmanTreeNode *current = this->root_;
    this->generateCharacterCodes(current, std::vector<bool>());
}

void data_compression::huffman_encode(std::string in_filename, std::string out_filename) {
    HuffmanCode *code = new HuffmanCode();
    code->getFrequencies(in_filename);
    code->generateTree();
    code->generateCharacterCodes();

    // TODO: Compress file contents

    // TODO: Write file contents and tree to output file
}

void data_compression::huffman_decode(std::string in_filename, std::string out_filename) {
    // TODO: Read file and build tree

    // TODO: Decompress file contents and write to output file
}
