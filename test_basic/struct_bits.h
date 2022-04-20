#ifndef __STRUCT_BITS_H__
#define __STRUCT_BITS_H__

#include <iostream>
#include <cstdint>

struct IPv4Header {
    // 相当于单独定义几个相互独立的字段，每个字段都是std::uint32_t, 但是都有位数限制。
    std::uint32_t version:4,
                  IHL:4,
                  DSCP:6,
                  ECN:2,
                  totalLength:20;
};

void test_struct_bits() {
    IPv4Header header{0b1111, 0b1111, 0b111111, 0b11, 0xfffff};
    std::cout << "version:" << header.version << std::endl;
    std::cout << "IHL:" << header.IHL << std::endl;
    std::cout << "DSCP:" << header.DSCP << std::endl;
    std::cout << "ECN:" << header.ECN << std::endl;
    std::cout << "totalLength:" << header.totalLength << std::endl;

    header.version = 0;
    header.IHL = 0;
    header.DSCP = 0;
    header.ECN = 0;
    header.totalLength = 0;
    std::cout << "final value: " << header.version << "  " << header.IHL << " " << header.DSCP << " " << header.ECN << " " << header.totalLength << std::endl;
}

#endif