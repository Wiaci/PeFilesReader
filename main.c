#include <stdio.h>
#include <inttypes.h>

struct __attribute__((packed)) file_header {
    uint16_t machine;
    uint16_t numOfSections;
    uint32_t time_date_stamp;
    uint32_t pointer_to_symbol_table;
    uint32_t number_of_symbols;
    uint16_t size_of_optional_header;
    uint16_t characteristics;
};

struct __attribute__((packed)) optional_header {

};

struct __attribute__((packed)) pe_header {
    uint32_t signature;
    struct file_header fileHeader;
    struct optional_header optionalHeader;
};

struct __attribute__((packed)) header {
     uint64_t dos_header[8];
     uint64_t dos_stub[25];
     struct pe_header peHeader;

};

int main() {
    return 0;
}
