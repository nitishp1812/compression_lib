#include <fstream>
#include <string>

#include "cxxopts.hpp"

#include "huffman_code/huffman_code.h"
#include "arithmetic_code/arith_model.h"

enum Methods {
    huffman, arithmetic
};

Methods convert(std::string method) {
    if (method == "huffman")
        return huffman;
    else
        return arithmetic;
}

int main(int argc, char **argv) {
    cxxopts::Options options("Compression CLI",
        "Compression engine to compress and decompress files using either Huffman coding or Arithmetic coding");

    options.add_options()
        ("c, compress", "Included when input file needs to be compressed")
        ("d, decompress", "Included when input file needs to be decompressed")
        ("f, file", "Path to input file", cxxopts::value<std::string>())
        ("m, method", "Method to use for compression / decompression", cxxopts::value<std::string>()->default_value("huffman"))
        ("o, out", "Path to output file", cxxopts::value<std::string>()->default_value("out.txt"))
        ("h, help", "Help");

    cxxopts::ParseResult result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    std::string in_filename = "";
    try {
        in_filename = result["file"].as<std::string>();
    } catch(...) {
        std::cerr << "Filename must be entered\n";
        exit(1);
    }

    std::string method = result["method"].as<std::string>();
    std::string out_filename = result["out"].as<std::string>();

    Methods m = convert(method);

    bool compress = result.count("compress");
    bool decompress = result.count("decompress");
    char action;

    if (compress && decompress) {
        std::cerr << "Both compression and decompression cannot be chosen\n";
        exit(1);
    } else if (!compress && !decompress) {
        std::cerr << "One of compression or decompression must be chosen\n";
        exit (1);
    } else {
        action = (compress) ? 'c' : 'd';
    }

    switch (m) {
        case huffman:
            if (action == 'c')
                data_compression::huffman_encode(in_filename, out_filename);
            else
                data_compression::huffman_decode(in_filename, out_filename);
            break;
        case arithmetic:
            if (action == 'c')
                data_compression::arithmetic_encode(in_filename, out_filename);
            else
                data_compression::arithmetic_decode(in_filename, out_filename);
            break;
    }
}
