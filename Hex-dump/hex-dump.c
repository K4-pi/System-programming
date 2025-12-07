#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGHT 11

unsigned int addres = 0xb2;

int main(int argc, char** argv) {
    if (argc < 1 && argc > 1){
        perror("No file provied or privded too many!\n");
        return EXIT_FAILURE;
    }

    printf("File: %s\n", argv[1]);

    FILE* DUMP_FILE = fopen(argv[1], "r");
    if (DUMP_FILE == NULL) {
        perror("Faild to open file!\n");
        return EXIT_FAILURE;
    }
    rewind(DUMP_FILE);

    char buffer[LINE_LENGHT];
    while (fgets(buffer, sizeof(buffer)/sizeof(char), DUMP_FILE) != NULL) {
        for (int i = 0; i < LINE_LENGHT; i++) {
            if (buffer[i] != '\0')
                printf("%.2x", buffer[i]);
            if (i % 2 == 1) 
                printf(" ");
        }
        printf(" | %s\n", buffer);
    }
    // while ((c = fgetc(DUMP_FILE)) != EOF) {
    //     printf("%02x", c);

    //     if (++count % 2 == 1) printf(" ");
    //     if (count >= LINE_LENGHT) {
    //         printf("\n");
    //         count = 1;
    //     } 
    // }

    fclose(DUMP_FILE);
    return EXIT_SUCCESS;
}
