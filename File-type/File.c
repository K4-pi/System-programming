#include <limits.h>
#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "signatures.h"

#define BUFF_SIZE 8

// char *sigInfo(unsigned char* buff);
sig_t fileInfo(unsigned char*);

int main(int argc, const char** argv) {
    FILE* file;
    unsigned char *buff = calloc(BUFF_SIZE, sizeof(unsigned char));

    if (argc < 2 || argc > 2) {
        printf("You need to provide filename\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("File not opened\n");
        return 1;
    }
    fread(buff, sizeof(unsigned char), BUFF_SIZE, file);

    printf("Size of sig table: %zu\n\n", sig_table_len());

    sig_t s = fileInfo(buff); 
    if (strcmp(s.name, "NULL") == 0) {
        printf("Unidetified file format...\n");
    }
    else {
        printf("File type: %s\n", s.name);
        printf("File magic number: ");
        for (int x = 0; x < s.len; x++) {
            printf("%02x ", s.sig[x]);
        }
        printf("\nSignature length: %zu\n", s.len);
    }

    fclose(file);
    return 0;
}

sig_t fileInfo(unsigned char *buff) {
    for (int i = 0; i < 5; i++) {
        if (memcmp(sig_table[i].sig, buff, sig_table[i].len) == 0) {
            return sig_table[i];
        }
    }
    return NULL_SIG;
}

