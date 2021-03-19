#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

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
    uint16_t magic;
    uint8_t major_linker_version;
    uint8_t minor_linker_version;
    uint32_t size_of_code;
    uint32_t size_of_initialized_data;
    uint32_t size_of_uninitialized_data;
    uint32_t address_of_entry_point;
    uint32_t base_of_code;
    uint32_t base_of_data;
    uint32_t image_base;
    uint32_t section_alignment;
    uint32_t file_alignment;
    uint16_t major_operating_system_version;
    uint16_t minor_operating_system_version;
    uint16_t major_image_version;
    uint16_t minor_image_version;
    uint16_t major_subsystem_version;
    uint16_t minor_subsystem_version;
    uint32_t win32_version_value;
    uint32_t size_of_image;
    uint32_t size_of_headers;
    uint32_t check_sum;
    uint16_t subsystem;
    uint16_t dll_chars;
    uint32_t size_of_stack_reserve;
    uint32_t size_of_stack_commit;
    uint32_t size_of_heap_reserve;
    uint32_t size_of_heap_commit;
    uint32_t loader_flags;
    uint32_t number_of_rva_and_sizes;
    uint64_t data_directories[15];
};

struct __attribute__((packed)) pe_header {
    uint32_t signature;
    struct file_header fileHeader;
    struct optional_header optionalHeader;
};

struct __attribute__((packed)) section_table {
    char name[8];
    uint32_t virtual_size;
    uint32_t virtual_address;
    uint32_t size_of_raw_data;
    uint32_t pointer_to_raw_data;
    uint32_t pointer_to_relocations;
    uint32_t pointer_to_line_numbers;
    uint16_t number_of_relocations;
    uint16_t number_of_line_numbers;
    uint32_t characteristics;
};

struct __attribute__((packed)) header {
    uint64_t dos_header[8];
    uint64_t dos_stub[25];
    struct pe_header peHeader;
    struct section_table* sectionTable;
};

bool get_header(FILE* file, struct header* header) {
    return fread(header, sizeof(struct header), 1, file);
}

int main() {
    FILE* file = fopen("example.exe", "rb");
    struct header file_header = { 0 };
    get_header(file, &file_header);
    fclose(file);

    return 0;
}
