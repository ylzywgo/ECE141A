//
//  Bitwise.hpp
//  Bitwise
//
//  Created by rick gessner on 2/9/20.
//

#ifndef Bitwise_h
#define Bitwise_h

namespace ECE141 {

    template<typename T>
    class Bitwise {
    public:

        Bitwise(T aValue = 0) {
            bits = aValue;
            std::cout << "size " << sizeof(bits) << "\n";
        }

        Bitwise(const Bitwise &aCopy) {
            *this = aCopy;
        }

        Bitwise &operator=(const Bitwise &aCopy) {
            bits = aCopy.bits;
            return *this;
        }

        bool operator==(const Bitwise &aCopy) {
            return aCopy.bits == bits;
        }

        Bitwise &setBit(size_t aBitNum, bool aValue) {
            int res = 1;
            int bitNum = aBitNum;
            while (bitNum > 0) {
                res *= 2;
                bitNum--;
            }
            // std::cout << res << std::endl;
            bool curValue = getBit(aBitNum);
            // std::cout << curValue << std::endl;
            if (aValue == true && curValue == false){
                bits += res;
            } 
            if (aValue == false && curValue == true){
                bits -= res;
            }

            // std::cout << bits << std::endl;
            return *this;
        }

        bool getBit(size_t aBitNum) {
            int cur = 0;
            int bitNum = aBitNum + 1;
            int curBit = bits;
            // std::cout << bitNum << std::endl;
            while (bitNum > 0){
                cur = curBit % 2;
                // std::cout << cur << std::endl;
                curBit /= 2;
                // std::cout << curBit << std::endl;
                bitNum--;
            }

            return cur == 1;
        }

        T getValue() {
            return bits;
        }

        //bitwise and
        Bitwise operator&(const Bitwise &another) {
            return Bitwise(bits & another.bits);
        }

        Bitwise &operator&=(const Bitwise &another) {
            bits = bits & another.bits;
            return *this;
        }

        //bitwise or
        Bitwise operator|(const Bitwise &another) {
            return Bitwise(bits | another.bits);
        }

        Bitwise &operator|=(const Bitwise &another) {
            bits |= another.bits;
            return *this;
        }

        //bitwise not
        Bitwise operator~() { return Bitwise(~bits); }

        //bitwise xor
        Bitwise operator^(const Bitwise &another) {
            return Bitwise(bits ^ another.bits);
        }

        Bitwise &operator^=(const Bitwise &another) {
            bits ^= another.bits;
            return *this;
        }

        //left shift
        Bitwise operator<<(size_t aCount) {
            return Bitwise(bits << aCount);
        }

        Bitwise &operator<<=(size_t aCount) {
            bits <<= aCount;
            return *this;
        }

        //right shift
        Bitwise operator>>(size_t aCount) {
            return Bitwise(bits >> aCount);
        }

        Bitwise &operator>>=(size_t aCount) {
            bits >>= aCount;
            return *this;
        }

    protected:
        T bits;
    };


}

#endif /* Bitwise_h */
