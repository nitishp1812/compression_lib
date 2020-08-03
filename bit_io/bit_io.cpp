#include "bit_io.h"

data_compression::BitInputStream::BitInputStream(std::istream &in): input_(in), current_byte_(0), remaining_bits_(0) {}

int data_compression::BitInputStream::read() {
    if (current_byte_ == -1)
        return -1;

    if (remaining_bits_ == 0) {
        current_byte_ = input_.get();

        if (current_byte_ == EOF)
            return -1;
        
        remaining_bits_ = 8;
    }

    remaining_bits_--;
    return (current_byte_ >> remaining_bits_) & 1;
}

data_compression::BitOutputStream::BitOutputStream(std::ostream &out): output_(out), current_byte_(0), filled_bits_(0) {}

void data_compression::BitOutputStream::write(int bit) {
    current_byte_ = (current_byte_ << 1) | bit;
    filled_bits_++;

    if (filled_bits_ == 8) {
        if (std::numeric_limits<char>::is_signed)
            current_byte_ -= (current_byte_ >> 7) << 8;
        output_.put(static_cast<char>(current_byte_));

        current_byte_ = 0;
        filled_bits_ = 0;
    }
}

void data_compression::BitOutputStream::finish() {
    while (filled_bits_ != 0)
        write(0);
}
