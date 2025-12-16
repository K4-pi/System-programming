#include <limits.h>
#include <stdio.h>
#include <elf.h>

#define BUFF_SIZE 4

void elfFileInfo(FILE* pFile);

int main(int argc, const char** argv) {
    FILE* file;
    unsigned char buff[BUFF_SIZE] = { 0 };

    if (argc < 2 || argc > 2) {
        printf("You need to provide filename\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("File not opened\n");
        return 1;
    }
    fread(buff, 1, sizeof(buff), file);
    printf("File: %s is %s file!\n", argv[1], buff);

    int i = 0;
    if (buff[0] == ELFMAG0 && buff[1] == ELFMAG1 && buff[2] == ELFMAG2 && buff[3] == ELFMAG3) {
        elfFileInfo(file);
    }

    fclose(file);
    return 0;
}

void elfFileInfo(FILE* pFile) {
    Elf64_Ehdr header;
    fseek(pFile, 0, SEEK_SET); //Rewind file pointer 4 bytes back
    fread(&header, 1, sizeof(header), pFile);

    if (header.e_ident[EI_CLASS] == ELFCLASS64) printf("Architecture: 64-bit\n");
    else printf("Architecture: 32-bit\n");

    if (header.e_ident[EI_DATA] == ELFDATA2LSB) printf("Endianess: Little\n");
    else printf("Endianess: Big\n");

    switch (header.e_machine) {
        case 62: printf("Code: x86-64\n"); break;
        case 3: printf("Code: x86\n"); break;
        case 40: printf("Code: ARM\n"); break;
        default:printf("Code: Not registered!");
    }

    switch (header.e_type) {
        case ET_NONE: printf("Type: No file type\n"); break;
        case ET_REL:  printf("Type: Relocatable file\n"); break;
        case ET_EXEC: printf("Type: Executable file\n"); break;
        case ET_DYN:  printf("Type: Shared object\n"); break;
        case ET_CORE: printf("Type: Core dump\n"); break;
        default:      printf("Type: Other (0x%x)\n", header.e_type); break;
    }
}
