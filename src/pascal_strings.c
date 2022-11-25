#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *cn_to_p_string(const char *c_string, size_t n) {
    unsigned char *p_string = malloc(n * sizeof(unsigned char));
    if (p_string == NULL) {
        fputs("Memory allocation failed", stderr);
        exit(EXIT_FAILURE);
    }
    p_string[0] = n; // first byte is the length of the string
    for (size_t i = 0; i < n; i++) { // from first c char to last c char (no null terminator)
        p_string[i + 1] = c_string[i]; // copy c char to p char + 1 (length byte at start)
    }
    return p_string;
}

unsigned char *c_to_p_string(const char *c_string) {
    size_t n = strlen(c_string); // take length of c string as n value (this method loses some optimisation)
    return cn_to_p_string(c_string, n);
}

void print_p_string(const unsigned char *p_string) {
    size_t n = p_string[0];
    for (size_t i = 0; i < n; i++) {
        printf("%c", p_string[i + 1]); // print p char + 1 (length byte at start)
    }
}

int main() {
    const char *c_string = "Hello, world!";
    unsigned char *p_string = c_to_p_string(c_string); // convert c string to p string

    print_p_string(p_string);
    free(p_string);

    puts("\n");

    print_p_string((unsigned char*) "\005Test!"); // or encode length in first byte for extra speed
    return 0;
}
