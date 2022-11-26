#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

unsigned char *make_header(size_t n) {
    size_t first_byte_value = floor((double) n / UCHAR_MAX); // the amount to multiply UCHAR_MAX by

    if (first_byte_value > UCHAR_MAX) {
        fputs("String is too large", stderr);
        exit(EXIT_FAILURE);
    }

    size_t last_byte_value = n - (first_byte_value * UCHAR_MAX); // the amount to add to the first byte to get the full length

    unsigned char *header = malloc(2 * sizeof(unsigned char));

    if (header == NULL) {
        fputs("Memory allocation failed", stderr);
        exit(EXIT_FAILURE);
    }

    header[0] = first_byte_value; // first byte (* UCHAR_MAX)
    header[1] = last_byte_value; // second byte

    return header;
}

size_t decode_header(const unsigned char *s_string) {
    return (s_string[0] * UCHAR_MAX) + s_string[1];
}

unsigned char *cn_to_s_string(const char *c_string, size_t n) {
    unsigned char *header = make_header(n);
    unsigned char *s_string = malloc((n + 2) * sizeof(unsigned char));

    if (s_string == NULL) {
        fputs("Memory allocation failed", stderr);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n + 2; i++) { // from first c char to last c char (no null terminator)
        if (i < 2) {
            s_string[i] = header[i];
        } else {
            s_string[i] = c_string[i - 2]; // copy c char to p char
        }
    }

    free(header);

    return s_string;
}

unsigned char *c_to_s_string(const char *c_string) {
    size_t n = strlen(c_string); // take length of c string as n value (this method loses some optimisation)
    return cn_to_s_string(c_string, n);
}

void print_s_string(const unsigned char *s_string) {
    size_t n = decode_header(s_string);

    for (size_t i = 0; i < n; i++) {
        printf("%c", s_string[i + 2]); // print p char
    }
}

int main(void) {
    // OLD:
    // super strings: byte 1 is dedicated to the number of bytes (n) that follow
    // the addition of the next n "header" bytes are dedicated to the string length
    // NEW:
    // byte 1 of the header is multiplied by UCHAR_MAX (255) and added to the next byte
    // now the header is only 2 bytes and needs no iteration to encode/decode, nor a start_ptr
    unsigned char *res = c_to_s_string(
            "pascal strings encode the length of the string as a byte leading before the characters rather than using a null terminator. pascal strings are great but limited to the maximum unsigned char size (assuming 255). super strings fix that! for example: this string is over 255 characters long, yet everything is okay!");
    print_s_string(res);
}