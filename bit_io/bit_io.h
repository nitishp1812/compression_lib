/* 
 * The bit io stream files were drawn from
 * https://github.com/nayuki/Reference-Huffman-coding/blob/master/cpp/BitIoStream.hpp
 */

#ifndef BIT_IO_H
#define BIT_IO_H

#include <istream>
#include <ostream>
#include <limits>

namespace data_compression {
class BitInputStream {
    private:
    std::istream &input_;
    int current_byte_, remaining_bits_;

    public:
    BitInputStream(std::istream &in);
    int read();
};

class BitOutputStream {
    private:
    std::ostream &output_;
    int current_byte_, filled_bits_;

    public:
    BitOutputStream(std::ostream &out);
    void write(int bit);
    void finish();
};
}

#endif