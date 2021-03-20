#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <malloc.h>

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
    uint64_t data_directories[16];
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

void save_section_info(struct section_table* section, int section_index, FILE* file) {
    fprintf(file, "%d\n", section_index);
    fprintf(file,"name: %s\n", section->name);
    fprintf(file,"virtual_size: %" PRIu32 "\n", section->virtual_size);
    fprintf(file,"virtual_address: %" PRIu32 "\n", section->virtual_address);
    fprintf(file,"size_of_raw_data: %" PRIu32 "\n", section->size_of_raw_data);
    fprintf(file,"pointer_to_raw_data: %" PRIu32 "\n", section->pointer_to_raw_data);
    fprintf(file,"pointer_to_relocations: %" PRIu32 "\n", section->pointer_to_relocations);
    fprintf(file,"pointer_to_line_numbers: %" PRIu32 "\n", section->pointer_to_line_numbers);
    fprintf(file,"number_of_relocations: %" PRIu32 "\n", section->number_of_relocations);
    fprintf(file,"number_of_line_numbers: %" PRIu32 "\n", section->number_of_line_numbers);
    fprintf(file,"characteristics: %" PRIu32 "\n\n", section->characteristics);
}

int main() {
    char filename[20];
    scanf("%s", filename);
    printf("\n");

    FILE* file = fopen(filename, "rb");
    FILE* text_file = fopen("sections.txt", "wt");
    FILE* bin_file = fopen("program.bin", "wb");

    uint64_t dos_start[16];
    fread(dos_start, sizeof(uint64_t) * 16, 1, file);

    struct pe_header peHeader = { 0 };
    fread(&peHeader, sizeof(struct pe_header), 1, file);

    struct section_table* sections = malloc(sizeof(struct section_table) * peHeader.fileHeader.numOfSections);

    for (uint16_t i = 0; i < peHeader.fileHeader.numOfSections; i++) {
        fread(sections + i, sizeof(struct section_table), 1, file);
        save_section_info(sections + i, i, text_file);
    }
    fseek(file, peHeader.optionalHeader.base_of_code, SEEK_SET);
    uint8_t* code = malloc(sizeof(uint8_t) * peHeader.optionalHeader.size_of_code);
    fread(code, peHeader.optionalHeader.size_of_code, 1, file);
    fwrite(code, peHeader.optionalHeader.size_of_code, 1, bin_file);

    free(code);
    free(sections);


    fclose(file);
    fclose(text_file);
    fclose(bin_file);
    return 0;
}
