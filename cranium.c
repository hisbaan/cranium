#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node {
    int value;
    struct node * next;
    struct node * prev;
};

void interpreter();
void compiler();

int main(int argc, char ** argv) {
    int i_flag = 0;
    int c_flag = 0;

    // Handle command line flags.
    int opt;
    while ((opt = getopt(argc, argv, "ic")) != -1) {
        switch(opt) {
            case 'i':
                i_flag = 1;
                break;
            case 'c':
                c_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: cranium [-i | -c] file_name.bf\n");
                exit(1);
                break;
        }
    }

    // Either interpret or compile based on flags.
    if (i_flag && c_flag) {
        fprintf(stderr, "Usage: cranium [-i | -c] file_name.bf\n");
        fprintf(stderr, "Error: cannot interpret and compile at the same time.\n");
        exit(1);
    } else if (i_flag) {
        interpreter(argv[2]);
    } else if (c_flag) {
        compiler(argv[2]);
    }
}

void interpreter(char * file_name) {
    FILE * fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    struct node curr;
    curr.next = NULL;
    curr.prev = NULL;
    curr.value = 0;

    int op;
    while ((op = fgetc(fp)) != EOF) {
        switch(op) {
            case '>': { // Go one block to the right.
                if (curr.next == NULL) {
                    struct node next;
                    next.next = NULL;
                    next.prev = &curr;
                    next.value = 0;

                    curr.next = &next;
                }
                curr = *curr.next;
                break;
            }
            case '<': { // Go one block to the left.
                if (curr.prev == NULL) {
                    struct node prev;
                    prev.prev = NULL;
                    prev.next = &curr;
                    prev.value = 0;

                    curr.prev = &prev;
                }
                curr = *curr.prev;
                break;
            }
            case '+': { // Increment the value in the current block.
                curr.value++;
                break;
            }
            case '-': { // Decrement the value in the current block.
                curr.value--;
                break;
            }
            case '.': { // Print the value of the current block to stdout.
                printf("%c", curr.value);
                break;
            }
            case ',': { // Read the value of the currnt block from stdin.
                scanf("%c", (char *) &curr.value);
                break;
            }
            case '[': {
                break;
            }
            case ']': {
            }
        }
    }
    printf("\n");

    if (fclose(fp) != 0) {
        perror("fclose");
        exit(1);
    }
}

void compiler(char ** file_name) { }
