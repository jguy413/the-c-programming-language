#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hex_to_bin(char hex[], size_t hex_size, unsigned char binary[]);
void bin_to_base64(unsigned char bin[], size_t bin_s, char b64[], size_t b64_s, int p);
void base64_int_to_base64_char(char *c);
void print_bits(char c);

/*
See `hex_to_base_wip.c` for notes/failed approaches
*/
int main() {

    char hex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    size_t hex_size = (size_t)strlen(hex);
    size_t hex_bin_size = hex_size / 2;
    size_t base64_size;
    int padding;
    // base64 processes 24 bits == 3 bytes at a time
    // hex_bin_size corresponds to the number of bytes to map hex chars to base64
    if ((hex_bin_size % 3) == 0) {
        padding = 0;
        base64_size = hex_bin_size * 4 / 3 + 1;
    // if the number of bytes does not align with the base64 expectation
    // determine the padding based on the remainder bytes
    } else {
        padding = 3 - (hex_bin_size % 3);
        base64_size = (int)ceil((double)hex_bin_size * 4 / 3) + padding + 1;
    }
    // raw bytes for hex_bin
    // char array for base64 output
    unsigned char *hex_bin = (unsigned char *)malloc(hex_bin_size);
    char *base64 = (char *)malloc(base64_size);

    hex_to_bin(hex, hex_size, hex_bin);
    bin_to_base64(hex_bin, hex_bin_size, base64, base64_size-1, padding);

    printf("%s\n", base64);
    // SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
}

void hex_to_bin(char h[], size_t s, unsigned char b[]) {

    int b_i = 0;
    for (int i = 0; i < s; i++) {

        int char_type_enum = (h[i] & 0xE0) >> 5;

        // we are assuming valid hex character input
        // https://www.ascii-code.com/
        if (char_type_enum == 1) {
            h[i] = h[i] - '0';
        } else if (char_type_enum == 2) {
            h[i] = h[i] - 55;
        } else if (char_type_enum == 3) {
            h[i] = h[i] - 87;
        }

        // shifting bits into upper/lower nibble
        if ((i % 2) == 0) {
            b[b_i] = h[i] << 4;
        } else {
            b[b_i] |= h[i];
            ++b_i;
        }
    }
}

void bin_to_base64(unsigned char bin[], size_t bin_s, char b64[], size_t b64_s, int p) {
    /*
    sequence of shifts following 6-bit convention outlined in
    https://datatracker.ietf.org/doc/html/rfc4648#section-4

    sequence:
      1 -> first 6
        -> & 0xFC
      2 -> last 2, first 4
        -> & 0x03 
        -> & 0xF0
      3 -> last 4, first 2
        -> & 0x0F
        -> & 0xC0
      0 -> last 6
        -> & 0x3F

    0-pad to form integral number of 6-bit "characters" accounted for
    padding argument informs number of '=' characters appended (memory already allocated)
    */

    int i, j;
    i = 0;
    j = 0;

    int seq = 1;
    while (j < b64_s-p) {
        if (seq == 1) {
            b64[j] = bin[i] >> 2;
        } else if (seq == 2) {
            b64[j] = (bin[i] & 0x03) << 4;
            ++i;
            if (i < bin_s) { // prevent undefined behavior
                b64[j] |= (bin[i] >> 4);
            }
        } else if (seq == 3) {
            b64[j] = (bin[i] & 0x0F) << 2;
            ++i;
            if (i < bin_s) { // prevent undefined behavior
                b64[j] |= (bin[i] >> 6);
            }
            seq = -1;
        } else {
            b64[j] = (bin[i] & 0x3F);
            ++i;
        }
        base64_int_to_base64_char(&(b64[j]));
        ++seq;
        ++j;
    }

    while (j < b64_s) {
        b64[j] = 0x3D;
        ++j;
    }
    b64[j] = '\0';

}

void base64_int_to_base64_char(char* c) {
        int c_val = (int)(*c);
        if (*c < 26) {
            *c += 65;
        } else if (*c < 52) {
            *c += 71;
        } else if (*c < 62) {
            *c -= 4;
        } else if (*c == 62) {
            *c = '+';
        } else if (*c == 63) {
            *c = '/';
        }
}

void print_bits(char c) {
    for (int j = __CHAR_BIT__-1; j >= 0; j--) {
        printf("%d", ((c >> j) & 1));
    }
    printf("\n");
}