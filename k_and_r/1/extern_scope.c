#include <stdio.h>
#include <string.h>

#define MAXLINE 20

void fold_input_lines(void);
void remove_comments(void);

int main() {

    // fold_input_lines();
    remove_comments();

}

// 1-22
void fold_input_lines() {

    int c, ct, maxlined;

    ct = 0;
    maxlined = 0;
    while ((c = getchar()) != EOF) {
        if ( ( c == '\n') || (c == ' ') || (c == '\t') ) {
            if (ct != 0) {
                putchar('\n');
            } 
            maxlined = ct = 0;
        } else {
            if (ct >= MAXLINE) {
                if (maxlined == 0) {
                    printf("...");
                    maxlined = 1;
                } else {
                    continue;
                }
            } else {
                putchar(c);
                ++ct;
            }
        }
    }
}

// 1-23
/*
This function just removes comments.. to additionally remove blank lines we could re-use
some of the work in `char_arrays.c`
*/
void remove_comments(void) {

    FILE *in_file = fopen("char_io.c", "r");
    FILE *out_file = fopen("char_io_no_comments.c", "w");

    char ch, out;
    char prev[2] = {'\0'};
    int skip;

    if (in_file == NULL || out_file == NULL) {
        printf("ERROR: Failure to open file\n");
    }

    /*
    keep track of 2 chars..
        - if ['/', '/'] -> enter skip-flow until '\n'
        - if ['/', '*'] -> enter skip-flow until ['*', '/']

    assume valid comment syntax
    write char as we remove from 2-char array

    enumerate skip:
    - 0: write out
    - 1: '/', '/' comment, looking for '\n'
    - 2: '/', '*' comment, looking for '*', '/'
    
    */

    skip = 0;
    while ((ch = fgetc(in_file)) != EOF) {
        
        out = prev[0];
        prev[0] = prev[1];
        prev[1] = ch;

        // write 'out' prior to updating 'skip'
        if ((skip == 0) && (out != '\0')) {
            // printf("%c", out);
            fprintf(out_file, "%c", out);
        }
        if (skip == 0) {
            if (prev[0] == '/' && prev[1] == '/') {
                skip = 1;
            }
            if (prev[0] == '/' && prev[1] == '*') {
                skip = 2;
            }
        } else if (skip == 1) {
            if (prev[1] == '\n') {
                skip = 0;
                prev[0] = '\0';
                prev[1] = '\n'; // don't lose newline
            }
        } else if (skip == 2) {
            if (prev[0] == '*' && prev[1] == '/') {
                skip == 0;
            }
        } else {
            // TODO: return an exit code
            printf("'skip' is set to an invalid value %d", skip);
        }
    }

    if (skip == 0) {
        // printf("%c%c", prev[0], prev[1]);
        fprintf(out_file, "%c", prev[0]);
        fprintf(out_file, "%c", prev[1]);
    }

    fclose(in_file);
    fclose(out_file);
}