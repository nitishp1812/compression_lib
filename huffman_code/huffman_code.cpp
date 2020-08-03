#include "huffman_code.h"

data_compression::HuffmanCode::HuffmanCode(unsigned num_chars) {
    num_chars_ = num_chars;
    root_ = nullptr;
    frequencies_ = std::vector<size_t>(num_chars, 0);
    lengths_ = std::vector<unsigned>(num_chars, 0);
    character_codes_ = std::unordered_map<unsigned, std::string>();
}

data_compression::HuffmanCode::~HuffmanCode() {
    clear(root_);
}

void data_compression::HuffmanCode::clear(HuffmanTreeNode* node) {
    if (node) {
        clear(node->left_);
        node->left_ = nullptr;
        clear(node->right_);
        node->right_ = nullptr;
        delete node;
        node = nullptr;
    }
}

void data_compression::HuffmanCode::getFrequencies(std::string target_filename) {
    std::ifstream target_file(target_filename, std::ios::binary);

    while(true) {
        int c = target_file.get();
        if (c == EOF)
            break;

        frequencies_[c]++;
    }
    frequencies_[num_chars_ - 1] = 1;
}

void data_compression::HuffmanCode::generateTree() {
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, HuffmanNodeCompare> queue;
    for (int i = 0; i < num_chars_; ++i) {
        if (frequencies_[i] != 0)
            queue.push(new HuffmanTreeNode(i, frequencies_[i], false));
    }

    while (queue.size() != 1) {
        HuffmanTreeNode *first_node, *second_node;

        first_node = queue.top();
        queue.pop();
        second_node = queue.top();
        queue.pop();

        unsigned combined_weight = first_node->weight_ + second_node->weight_;
        
        HuffmanTreeNode* combined_node = new HuffmanTreeNode(num_chars_, combined_weight, true);
        combined_node->left_ = first_node;
        combined_node->right_ = second_node;
            
        queue.push(combined_node);
    }

    root_ = queue.top();
    queue.pop();
}

void data_compression::HuffmanCode::generateCodeLengths(HuffmanTreeNode* node, unsigned curr_length) {
    if (!node->internal_) {
        lengths_[node->element_] = curr_length;
        return;
    }

    generateCodeLengths(node->left_, curr_length + 1);
    generateCodeLengths(node->right_, curr_length + 1);
}

void data_compression::HuffmanCode::generateCodeLengths() {
    if (root_) 
        generateCodeLengths(root_, 0);
}

void data_compression::HuffmanCode::getCanonicalTree() {
    clear(root_);

    std::deque<HuffmanTreeNode*> nodes;
    unsigned max_len = *std::max_element(lengths_.begin(), lengths_.end());

    for (unsigned i = max_len + 1; i > 0; i--) {
        unsigned curr_len = i - 1;
        std::deque<HuffmanTreeNode*> temp;

        if (curr_len > 0) {
            for (size_t j = 0; j < lengths_.size(); j++) {
                if (lengths_[j] == curr_len)
                    temp.push_back(new HuffmanTreeNode(j, 0, false));
            }
        }

        for (size_t j = 0; j < nodes.size();) {
            HuffmanTreeNode *first_node, *second_node;

            first_node = nodes[0];
            second_node = nodes[1];
            nodes.pop_front();
            nodes.pop_front();

            HuffmanTreeNode* combined = new HuffmanTreeNode(257, 0, true);
            combined->left_ = first_node;
            combined->right_ = second_node;

            temp.push_back(combined);
        }

        nodes = temp;
    }

    root_ = nodes[0];
    nodes.pop_front();
}

void data_compression::HuffmanCode::generateCharacterCodes(HuffmanTreeNode* node, std::string code) {
    if (!node->internal_) {
        character_codes_[node->element_] = code;
        return;
    }

    generateCharacterCodes(node->left_, code + "0");
    generateCharacterCodes(node->right_, code + "1");
}

void data_compression::HuffmanCode::generateCharacterCodes() {
    if (root_)
        generateCharacterCodes(root_, "");
}

void data_compression::HuffmanCode::writeToFile(std::string in_filename, std::string out_filename, 
    BitOutputStream& out_stream) {
    for (unsigned len : lengths_) {
        std::string length_string = std::bitset<8>(len).to_string();
        for (char bit : length_string) {
            int b = (bit == '0') ? 0 : 1;
            out_stream.write(b);
        }
    }
    
    std::ifstream in_file(in_filename, std::ios::binary);

    while (true) {
        int c = in_file.get();
        if (c == EOF)
            break;
        
        for (char bit : character_codes_[c]) {
            int b = (bit == '0') ? 0 : 1;
            out_stream.write(b);
        }
    }

    for (char bit : character_codes_[256]) {
        int b = (bit == '0') ? 0 : 1;
        out_stream.write(b);
    }
    
    out_stream.finish();
}

void data_compression::HuffmanCode::readCodeLengths(BitInputStream& in_stream) {
    for (int i = 0; i < num_chars_; i++) {
        int curr_len = 0;
        std::string curr_bit_string = "";
        for (int i = 0; i < 8; i ++) {
            curr_bit_string += std::to_string(in_stream.read());
        }

        lengths_[i] = std::bitset<8>(std::string(curr_bit_string)).to_ulong();
    }
}

unsigned data_compression::HuffmanCode::readNextCharacter(BitInputStream& in_stream) {
    HuffmanTreeNode* node = root_;

    while (node->internal_) {
        int next_bit = in_stream.read();
        node = (next_bit) ? node->right_ : node->left_;
    }

    return node->element_;
}

void data_compression::huffman_encode(std::string in_filename, std::string out_filename) {
    HuffmanCode *code = new HuffmanCode(257);

    // calculate the frequencies of input characters and generate greedy huffman tree
    code->getFrequencies(in_filename);
    code->generateTree();

    // calculate bit lengths and generate canonical huffman tree
    code->generateCodeLengths();
    code->getCanonicalTree();

    // calculate the character codes according to the canonical huffman tree
    code->generateCharacterCodes();

    // Initialize file writer and write the tree and input file contents to output file
    std::ofstream out(out_filename, std::ios::binary);
    BitOutputStream out_stream(out);
    code->writeToFile(in_filename, out_filename, out_stream);

    // free allocated memory
    delete code;
}

void data_compression::huffman_decode(std::string in_filename, std::string out_filename) {
    // Read input file
    std::ifstream in(in_filename, std::ios::binary);
    BitInputStream in_stream(in);

    // Build code tree from file contents
    HuffmanCode *code = new HuffmanCode(257);
    code->readCodeLengths(in_stream);
    code->getCanonicalTree();

    // decompress input file
    std::ofstream out(out_filename, std::ios::binary);
    while (true) {
        unsigned next_elem = code->readNextCharacter(in_stream);
        if (next_elem == 256)
            break;

        int elem = static_cast<int>(next_elem);
        if (std::numeric_limits<char>::is_signed)
			elem -= (elem >> 7) << 8;

        out.put((char)elem);
    }

    // free allocated memory
    delete code;
}
