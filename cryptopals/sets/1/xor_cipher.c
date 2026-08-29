#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decrypt_hex(char *in, int size, char *out, int cipher);
int hex_to_bin(char u, char l);
int hex_nibble(int h);
float score_decrypted_text(char *result, int len);


typedef enum {
    UNDEFINED, // 0
    DIGIT,     // 1
    UPPER,     // 2
    LOWER      // 3
} CHARTYPE;

int main() {

    char hex[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t hex_len = strlen(hex);
    size_t decrypt_len = (hex_len/2)+1;
    // printf("hex size: %d\n", hex_len);
    // printf("decrypted size: %d\n", decrypt_len);

    // allocate once before loop
    char *decrypted = (char *)malloc(decrypt_len);
    memset(decrypted, 0, decrypt_len);

    // allocate once before loop
    char *best_match = (char *)malloc(decrypt_len);
    memset(best_match, 0, decrypt_len);
    

    float score = 0;
    float best_score = FLT_MAX;
    int best_score_cipher;
    for (int i=0; i<256; i++) {

        if (decrypt_hex(hex, hex_len, decrypted, i) != 0) {
            printf("failed to decrypt hex with cipher %d", i);
            free(decrypted);
            free(best_match);
            exit(1);
        }
        // printf("result: %s\n", decrypted);
        score = score_decrypted_text(decrypted, decrypt_len-1);
        if (score < best_score) {
            best_score = score;
            best_score_cipher = i;
            memcpy(best_match, decrypted, decrypt_len);
        }
    }
    printf("highest-scored decrypted text using chi-squared against relative frequencies of letters in english plaintext\n");
    printf("best match: %s\n", best_match);
    printf("cipher: %d\n", best_score_cipher);
    free(decrypted);
    free(best_match);

    return 0;
}

// decrypts a hex string to its text format using an input cipher
int decrypt_hex(char *in, int in_size, char* out, int cipher) {

    for (int i=0; i<in_size-1; i+=2) {

        int bin = hex_to_bin(in[i], in[i+1]);
        int xor = bin ^ cipher;

        out[i/2] = xor;
    }

    out[(in_size/2)] = '\0';

    return 0;
}

// takes two ASCII chars representative of positional
// characters of a hexadeximal and converts to the underlying binary
int hex_to_bin(char u, char l) {

    int ub = (hex_nibble(u) << 4);
    int lb = (hex_nibble(l) & 0x0F);

    return ub | lb;
}

int hex_nibble(int c) {

    CHARTYPE ctype = (c >> 5);
    switch (ctype) {
        case DIGIT:
            return c - '0';
            break;
        case UPPER:
            return c - 55;
            break;
        case LOWER:
            return c - 87;
            break;
        default:
            printf("invalid CHARTYPE: %d", ctype);
            exit(1);
    }
}

// takes a pointer to first element of char array
// use chi-squared to test fit to english text distribution
// return max float if invalid to disqualify score
float score_decrypted_text(char *result, int len) {

    // https://web.archive.org/web/20170918020907/http://www.data-compression.com/english.html
    float expected_char_relative_frequencies[] = {
        0.0651738f,
        0.0124248f,
        0.0217339f,
        0.0349835f,
        0.1041442f,
        0.0197881f,
        0.0158610f,
        0.0492888f,
        0.0558094f,
        0.0009033f,
        0.0050529f,
        0.0331490f,
        0.0202124f,
        0.0564513f,
        0.0596302f,
        0.0137645f,
        0.0008606f,
        0.0497563f,
        0.0515760f,
        0.0729357f,
        0.0225134f,
        0.0082903f,
        0.0171272f,
        0.0013692f,
        0.0145984f,
        0.0007836f,
        0.1918182f,
    };

    int sample_set = 27;
    int sample_bytes = sample_set * sizeof(float);
    float *observed_frequencies = (float *)malloc(sample_bytes);
    memset(observed_frequencies, 0, sample_bytes);
    
    int valid_characters = 0;
    for (int i=0; i<len; i++) {
        char c = result[i];
        if ((c >= 65) && (c <= 90)) {
            c = c - 65;
        }
        else if ((c >= 97) && (c <= 122)) {
            c = c - 97;
        }
        else if (c == 32) {
            c = 26;
        }
        // punctuation characters allowed in text, omitted for scoring
        else if ((c == 39) || (c == 44) || (c == 46)) {
            continue;
        }
        else {
            free(observed_frequencies);
            return FLT_MAX;
        }
        observed_frequencies[c]++;
        valid_characters++;
    }
    
    // printf("%d len for decrypted text %s\n", len, result);
    // printf("%d valid characters for decrypted text %s\n", valid_characters, result);
    float proportion_valid = (float)valid_characters / (float)(len);
    if (proportion_valid < 0.75) {
        free(observed_frequencies);
        return FLT_MAX;
    }

    // chi-squared algorithm
    float score = 0.0;
    for (int j=0; j<sample_set; j++) {
        float diff = ((observed_frequencies[j]/(float)valid_characters) - expected_char_relative_frequencies[j]);
        float diff_2 = diff * diff;
        score += (diff_2/expected_char_relative_frequencies[j]);
    }
    // printf("valid-enough decrypted text %s scored: %f\n", result, score);
    free(observed_frequencies);
    return score;

}