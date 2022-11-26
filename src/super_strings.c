#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

unsigned char *
make_header(size_t n, size_t *start_ptr) { // returns header, assigns where to start filling chars to start_ptr
    size_t maxvalue_bytes_count = floor((double) n /
                                        UCHAR_MAX); // if less than unsigned char max (assumed 255 from now on), don't add any 255 value maxvalue "blocks", correct value set in last byte

    if (maxvalue_bytes_count > UCHAR_MAX) {
        fputs("String is too large", stderr);
        exit(EXIT_FAILURE);
    }

    unsigned char total_bytes_count = maxvalue_bytes_count + 1; // add 1 for last byte

    size_t last_byte_value = n - (maxvalue_bytes_count * UCHAR_MAX);

    size_t size = (total_bytes_count + 1) * sizeof(unsigned char); // number of blocks + 1 for the count byte itself
    unsigned char *header = malloc(size);

    if (header == NULL) {
        fputs("Memory allocation failed", stderr);
        exit(EXIT_FAILURE);
    }

    header[0] = total_bytes_count; // first byte

    size_t i;
    for (i = 0; i < maxvalue_bytes_count; i++) { // n bytes - 1
        header[i + 1] = UCHAR_MAX;
    }

    header[i +
           1] = last_byte_value; // nth byte

    *start_ptr = i + 2;

    return header;
}

size_t decode_header(const unsigned char *s_string, size_t *start_ptr) {
    unsigned char count_byte = s_string[0];

    size_t length = 0;
    size_t i;
    for (i = 0; i < count_byte; i++) {
        length += s_string[i + 1];
    }

    *start_ptr = i + 1;

    return length;
}

unsigned char *cn_to_s_string(const char *c_string, size_t n) {
    size_t *start_ptr = malloc(sizeof(size_t));
    unsigned char *header = make_header(n, start_ptr);

    unsigned char *s_string = malloc((*start_ptr + n) * sizeof(unsigned char)); // header size + string length + 1

    if (s_string == NULL) {
        fputs("Memory allocation failed", stderr);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n + *start_ptr; i++) { // from first c char to last c char (no null terminator)
        if (i < *start_ptr) {
            s_string[i] = header[i];
        } else {
            s_string[i] = c_string[i - *start_ptr]; // copy c char to p char
        }
    }

    free(header);
    free(start_ptr);

    return s_string;
}

unsigned char *c_to_s_string(const char *c_string) {
    size_t n = strlen(c_string); // take length of c string as n value (this method loses some optimisation)
    return cn_to_s_string(c_string, n);
}

void print_s_string(const unsigned char *s_string) {
    size_t *start_ptr = malloc(sizeof(size_t));
    size_t n = decode_header(s_string, start_ptr);
    for (size_t i = 0; i < n; i++) {
        printf("%c", s_string[i + *start_ptr]); // print p char
    }
}

int main(void) {
    // super strings: byte 1 is dedicated to the number of bytes (n) that follow
    // the addition of the next n "header" bytes are dedicated to the string length
    unsigned char *res = c_to_s_string(
            "pascal strings encode the length of the string as a byte leading before the characters rather than using a null terminator. pascal strings are great but limited to the maximum unsigned char size (assuming 255). super strings fix that! for example: this string is over 255 characters long, yet everything is okay!");
    print_s_string(res);
}