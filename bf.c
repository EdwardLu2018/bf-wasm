#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

#include "bf_mem.h"

#define DEBUG
#define MAXLEN 1024

int eval(char *program) {
    char *c, closed_braces, open_braces;
    bf_memory *memory;

    if ((memory = bf_memory_create()) == NULL) {
        return -1;
    }

    for(int i = 0; program[i] != 0; ++i) {
        switch (program[i]) {
            case '+':
                bf_memory_incr(memory);
                break;
            case '-':
                bf_memory_decr(memory);
                break;
            case '<':
                bf_memory_move_left(memory);
                break;
            case '>':
                bf_memory_move_right(memory);
                break;
            case ',':
                bf_memory_put(memory, getchar());
                break;
            case '.':
                putchar(bf_memory_get(memory));
                break;
            case '[':
                if (bf_memory_get(memory) == 0) {
                    open_braces = 1;
                    // goto matching closing brace
                    while (open_braces > 0) {
                        ++i;
                        if (program[i] == '[') {
                            open_braces++;
                        }
                        else if (program[i] == ']') {
                            open_braces--;
                        }
                    }
                }
                break;
            case ']':
                closed_braces = 1;
                // goto matching open brace
                while (closed_braces > 0) {
                    --i;
                    if (program[i] == '[') {
                        closed_braces--;
                    }
                    else if (program[i] == ']') {
                        closed_braces++;
                    }
                }
                --i;
                break;
            default:
                break;
        }
    }

#ifdef DEBUG
        bf_memory_print(memory);
#endif

    bf_memory_free(memory);

    return 0;
}

int main(int argc, char* argv[]) {
    char *filename = NULL;
    char *usg = "Usage: ./bf -f <file.bf>\n";

    // parse arguments
    int opt;
    while ((opt = getopt(argc, argv, "hf:")) > 0) {
        switch (opt) {
        case 'f':
            filename = optarg;
            break;
        case 'h':
        default:
            fprintf(stderr, "%s", usg);
            exit(1);
        }
    }

    FILE *fileptr;
    char program[MAXLEN];
    fileptr = fopen(filename, "r");
    if (fileptr == NULL){
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    char *buffer = 0;
    long length;
    fseek(fileptr, 0, SEEK_END);
    length = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
        fread(buffer, 1, length, fileptr);
    }

    eval(buffer);

    free(buffer);
    fclose(fileptr);

    return 0;
}
