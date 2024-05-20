#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void never_gonna_let_you_down() {
    printf("Never gonna let you down!\n");
}

void never_gonna_run_around() {
    execl("/bin/sh", "sh", NULL);
}

void (*print_message)() = never_gonna_let_you_down;

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    char buffer[strlen(argv[1]) + 1];
    strcpy(buffer, argv[1]);
    char * message = calloc(strlen(argv[1]) + 1337, sizeof(char));
    if (!message) {
        printf("Memory allocation failed\n");
        return 1;
    }
    sprintf(message, "Never gonna give you up %s!\n", argv[1]);
    printf(message);
    // I think I should remove the line below and will be safe. Will I?
    print_message();
    free(message);
    return 0;
}