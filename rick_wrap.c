#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/personality.h>
#include <assert.h>

int main(int argc, char ** argv) {
    // Set UID to 0 (root)
    assert(setresuid(0, 0, 0) == 0);
    // Disable ASLR
    if (personality(ADDR_NO_RANDOMIZE) == -1) {
        perror("personality");
        return EXIT_FAILURE;
    }
    // Execute rick
    char * cmd = "/home/ubuntu/rick_real";
    argv[0] = cmd;
    execvp(cmd, argv);
    return 0;
}
