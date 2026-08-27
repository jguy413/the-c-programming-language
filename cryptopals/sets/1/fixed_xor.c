#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void produce_fixed_xor(char *h1, char *h2, char *f);
int hex_to_bin(char u, char l);
int hex_nibble(char c);
void bin_to_hex(int i, char *f, int index);
char nibble_to_hex(int i);
int validate_input(char *arr);

void print_8_bits(int num);

typedef enum {
    UNDEFINED, // 0
    DIGIT,     // 1
    UPPER,     // 2
    LOWER      // 3
} CHARTYPE;

#define LENGTH 36
int main() {


    char hex1[LENGTH] = "1c0111001f010100061a024b53535009181c";
    char hex2[LENGTH] = "686974207468652062756c6c277320657965";

    // size_t fixed_xor_size = (size_t)strlen(hex1);
    // char fixed_xor[LENGTH];
    char *fixed_xor = (char *)malloc(LENGTH);
    memset(fixed_xor, 0, sizeof(fixed_xor));

    if (validate_input(hex1) != 0) {
        printf("input not valid!");
        return 1;
    }
    if (validate_input(hex2) != 0) {
        printf("input not valid!");
        return 1;
    }

    produce_fixed_xor(hex1, hex2, fixed_xor);

    printf("xor: %s\n", fixed_xor);

    free(fixed_xor);

}

int validate_input(char *arr) {
    for (int i=0; i<sizeof(arr); i++) {
        int e = arr[i];
        int valid = ((e >= 48) & (e <= 57)) || ((e >= 65) & (e <= 90)) || ((e >= 97) & (e <= 122));
        if (!valid) {
            printf("%c is not a valid hexadecimal character", e);
            return 1;
        }
    }
    return 0;
}

void produce_fixed_xor(char *h1, char *h2, char *f) {

    printf("h1: %s\n", h1);
    printf("h2: %s\n", h2);

    for (int i=0; i < LENGTH; i+=2) {

        // printf("h1[%d] = %c\n", i, h1[i]);

        int j = i + 1;
        int h1_bin = hex_to_bin(h1[i], h1[j]);
        int h2_bin = hex_to_bin(h2[i], h2[j]);

        int xor_bin = h1_bin ^ h2_bin;

        // printf("xor: %d\n", xor_bin);

        // char *xor = nibble_to_hex(xor_bin);

        bin_to_hex(xor_bin, f, i);

        // break;
    }
}

// takes two ASCII chars representative of positional
// characters of a hexadeximal and converts to the underlying binary
int hex_to_bin(char u, char l) {
    
    // int r = 0xFF;

    // printf("u = %c, d = %c\n", u, l);

    int ub = (hex_nibble(u) << 4);
    int lb = (hex_nibble(l) & 0x0F);

    // print_8_bits(ub);
    // print_8_bits(lb);

    int r = ub | lb;
    // print_8_bits(r);

    return r;
}

// utility function for viewing bits
// void print_8_bits(int num) {
//     for (int i = 7; i >= 0; i--) {
//         // Shift right, isolate the bit with mask 1, and print
//         printf("%d", (num >> i) & 1);
//     }
//     printf("\n");
// }

// convert a hex character to its nibble binary
int hex_nibble(char c) {
    char ccopy = c; 
    CHARTYPE char_type = (c & 0xE0) >> 5;

    // we are assuming valid hex character input
    // hex characters are not case sensitive so we resolve
    // them to the same decimal value; could alternatively cast non-digits to upper
    // https://www.ascii-code.com/
    switch (char_type) {
        case DIGIT:
            c = c - '0';
            break;
        case UPPER:
            c = c - 55; // equivalent to - 'A' + 10
            break;
        case LOWER:
            c = c - 87; // equivalent to - 'a' + 10
            break;
        default:
    }
    // printf("input: %c, output: %d\n", ccopy, c);
    return c;
}

// convert a binary hexadeximal to its ASCII-char representation
void bin_to_hex(int xor, char* f, int index) {

    f[index] = nibble_to_hex((xor & 0xF0) >> 4);
    f[index+1] = nibble_to_hex((xor & 0x0F));
}

// inverse of hex_nibble; take a byte and convert to its ASCII char decimal
char nibble_to_hex(int i) {
    if (i <= 9) {
        return i + '0';
    } else {
        return i + 87;
    }
}
