#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void interpreter();
void compiler();

int main(int argc, char ** argv) {
    int i_triggered = 0;
    int c_triggered = 0;

    int opt;
    while ((opt = getopt(argc, argv, "ic")) != -1) {
        switch(opt) {
            case 'i':
                i_triggered = 1;
                break;
            case 'c':
                c_triggered = 1;
                break;
        }
    }

    if (i_triggered && c_triggered) {
        fprintf(stderr, "Usage: cannot compile and interpret at the same time.\n");
    } else if (i_triggered) {
        interpreter();
    } else if (c_triggered) {
        compiler();
    }
}

void interpreter() { }

void compiler() { }
