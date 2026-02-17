#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BITGROUP 24 

void hex_to_base64(char h[], char b[]);
void hex_to_bin(char hex[], size_t hex_size, unsigned char binary[]);
void bin_to_base64(unsigned char binary[], size_t hex_bin_size, int padding, char base64[]);
void base64_bin_to_base64_char(char *c);
int hex_to_int(char c);

void print_bits(char c);

int main() {

    // char hex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    // char hex[] = "49";
    // char hex[] = "4927";
    char hex[] = "1234567890";
    // char hex[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // char hex[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_";
    size_t hex_size = (size_t)strlen(hex);
    size_t hex_bin_size = hex_size / 2;
    size_t base64_size;
    int padding;
    // base64 processes 24 bits == 3 bytes at a time
    // hex_bin_size corresponds to the number of bytes to map hex chars to base64
    if ((hex_bin_size % 3) == 0) {
        padding = 0;
        base64_size = hex_bin_size * 4 / 3;
    // if the number of bytes does not align with the base64 expectation
    // determine the padding based on the remainder bytes
    } else {
        padding = 3 - (hex_bin_size % 3);
        base64_size = (int)ceil((double)hex_bin_size * 4 / 3) + padding;
    }
    // raw bytes for hex_bin
    // char array for base64 output
    unsigned char *hex_bin = (unsigned char *)malloc(hex_bin_size);
    char *base64 = (char *)malloc(base64_size);

    hex_to_bin(hex, hex_size, hex_bin);
    printf("HEX BINARY:\n");
    for (int i = 0; i < hex_bin_size; i++) {
    print_bits(hex_bin[i]);
    }
    // print_bits(hex_bin[1]);
    // print_bits(hex_bin[2]);
    bin_to_base64(hex_bin, base64_size, padding, base64);
    printf("B64 BINARY:\n");
    for (int i = 0; i < base64_size; i++) {
        print_bits(base64[i]);
    }
    printf("%s\n", base64);
    // print_bits(base64[1]);
    // print_bits(base64[2]);
}

void hex_to_bin(char h[], size_t s, unsigned char b[]) {

    // printf("%d\n", s);

    int b_i = 0;
    for (int i = 0; i < s; i++) {

        int char_type_enum = (h[i] & 0xE0) >> 5;
        // printf("%d\n", ('1' & 0xE0) >> 5);
        // printf("%d\n", ('A' & 0xE0) >> 5);
        // printf("%d\n", ('a' & 0xE0) >> 5);

        // we are assuming valid hex character input
        // https://www.ascii-code.com/
        if (char_type_enum == 1) {
            h[i] = h[i] - '0';
        } else if (char_type_enum == 2) {
            h[i] = h[i] - 55;
        } else if (char_type_enum == 3) {
            h[i] = h[i] - 87;
        }
        // printf("%d\n", h[i]);
        // print_bits(h[i]);

        // shifting bits into upper/lower nibble
        if ((i % 2) == 0) {
            b[b_i] = h[i] << 4;
            // print_bits(b[b_i]);
        } else {
            b[b_i] |= h[i];
            // print_bits(b[b_i]);
            ++b_i;
        }
        
        // if (i == 3) {
        //     // print_bits(b[b_i]);
        //     break;
        // }
    }
}

void bin_to_base64(unsigned char bin[], size_t s, int p, char b64[]) {
    /*
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

    when we reach size_t - padding:
      - add 0 on right to form intergral number of 6 bit groups 
      - add special character N=padding times to b64
    */

    int start, end, ct;
    int i, j;
    i = 0;
    j = 0;
    start = 7;
    end = 2;
    ct = (start - end) + 1;

    int seq = 1;
    while (j < s-p) {
        if (seq == 1) {
            b64[j] = bin[i] >> 2;
        } else if (seq == 2) {
            b64[j] = (bin[i] & 0x03) << 4;
            ++i;
            b64[j] |= (bin[i] >> 4); // reaching out of bounds?
        } else if (seq == 3) {
            b64[j] = (bin[i] & 0x0F) << 2;
            ++i;
            b64[j] |= (bin[i] >> 6); // reaching out of bounds?
            seq = -1;
        } else {
            b64[j] = (bin[i] & 0x3F);
            ++i;
            // seq = 0;
        }
        base64_bin_to_base64_char(&(b64[j]));
        ++seq;
        ++j;
    }

    while (j < s) {
        b64[j] = 0x3D;
        ++j;
    }

}

void base64_bin_to_base64_char(char* c) {
        int c_val = (int)(*c);
        if (*c < 26) {
            *c += 65;
        } else if (*c < 52) {
            *c += 71;
        } else if (*c < 62) {
            *c += '0';
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

// ok... no string/char shenanigans... we can use "2 pointer", one to index start of byte and other to index bit place?
// convert to bytes
// convert to decimal representation
// bit shift to get first 4 
// if first hex char:
//     bit shift to move chars to place 4-7
// else:
//     bitwise 'or' with first 4 of 2nd character
// pass to base64 encoder? 
// base64 encoder(byte, flag) can receive 1 byte at a time, once 4 reached or flag to terminate
// flag to terminate to inform padding
// can re-use hex_to_base64 for byte -> base64 character mapping?



/*
I understand that we can use bit-wise operations against 0x0F to reduce a single character to its hex representation.
However, that treats individual characters as a hex character in and of itself. For example 0x31 & 0x0F => 0x01.
We don't want to derive 0x01, 0x02 when the first 2 characters of the char array are "12".
We want to operate on 00010010. *need to figure this out* 
 -> copy 2 bytes into 2, 1 byte value (unsigned int?) 
 -> bitwise operation from char to int
 -> copy desired section into corresponding section of hex_bin,

Following RFC 4648 we first expand to 000100100000
then break this into
- 000100 => 4 => "E"
- 100000 => 32 => "g"
- 24 bits - 8 bit (final quantum) = 16 => "=="
*/

//---------------------------------------------------
//-- ALL WRONG THIS EXPLICITY BREAKS THE RULES! :/ --
//---------------------------------------------------
// void hex_to_base64(char s[], char b[]) {

//     int hex_len = strlen(s);
//     int input_bits = __CHAR_BIT__ * hex_len;
//     int remainder = input_bits % BITGROUP;

//     char j;
//     char hex_bin;

//     for (int i = 0; i <= hex_len; i++) {

//         j = hex_to_int(s[i]);

//         char base64;
//         if (j < 26) {
//             base64 = (char)(j + 65);
//         } else if (j < 52) {
//             base64 = (char)(j + 71);
//         } else if (j < 62) {
//             base64 = (char)(j - 52 + '0');
//         } else if (j == 62) {
//             base64 = '+';
//         } else if (j == 63) {
//             base64 = '/';
//         }
//         b[i] = base64;
//     }
// }

// // hex char to binary
// // HEX & 0x0F
// // if pos 6 == 1: (letter chars)
// // binary = binary + 9

// // remainder = modulo 24 to determine padding
// // - 0  --> ""
// // - 8  --> "=="
// // - 16 --> "="

// // how to map 8 bit characters to 6 bit representation? (need to know number of chars ahead of time to know padding?)
// // process in 24 bit chunks per RFC-4648?
// // - bit shift to 6 chars
// // - map to base64 char
// // - repeat until we've shifted 24 - (remainder) times

// int hex_to_int(char c) {
//     if (c == '-') {
//         return 62;
//     }
//     if (c == '_') {
//         return 63;
//     }

//     int b = c & 0x0F;
//     if (((c >> 6) & 1) == 1) {
//         b = b + 9;

//         if (((c >> 5) & 1) == 1) {
//             b = b + 26;
//         }
//         if (((c >> 4) & 1) == 1) {
//             b = b + 16;
//         }
//     }
//     printf("->%d\n", b);
//     return b;
//     // printf("%d", (c >> 7) & 1);
//     // printf("%d", (c >> 6) & 1);
//     // printf("%d", (c >> 5) & 1);
//     // printf("%d", (c >> 4) & 1);
//     // printf("%d", (c >> 3) & 1);
//     // printf("%d", (c >> 2) & 1);
//     // printf("%d", (c >> 1) & 1);
//     // printf("%d", (c >> 0) & 1);
// }
