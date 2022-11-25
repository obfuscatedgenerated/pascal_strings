#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *make_header(size_t n) {

}

unsigned char *cn_to_s_string(const char *c_string, size_t n) {
    unsigned char *s_string = malloc(n * sizeof(unsigned char)); // how to we figure out how many bytes we need? already have string length + 1
    // use some division of 255 aka sizeof unsigned char
    // malloc ((n - 1) / sizeof(unsigned char)) + 1 + ((n - 1) * sizeof(unsigned char))
    //      number of the n "header" bytes    first byte    literal character bytes
    if (s_string == NULL) {
        fputs("Memory allocation failed", stderr);
        exit(EXIT_FAILURE);
    }
    //s_string[0] = n; // first byte is the length of the string // untrue: check format in main
    //for (size_t i = 0; i < n; i++) { // from first c char to last c char (no null terminator)
    //    s_string[i + 1] = c_string[i]; // copy c char to p char + 1 (length byte at start)
    //}
    return s_string;
}

unsigned char *c_to_s_string(const char *c_string) {
    size_t n = strlen(c_string); // take length of c string as n value (this method loses some optimisation)
    return cn_to_s_string(c_string, n);
}

void print_s_string(const unsigned char *s_string) {
    size_t n = s_string[0];
    for (size_t i = 0; i < n; i++) {
        printf("%c", s_string[i + 1]); // print p char + 1 (length byte at start)
    }
}

int main(void) {
    // super strings: byte 1 is dedicated to the number of bytes (n) that follow
    // the addition of the next n "header" bytes are dedicated to the string length
}