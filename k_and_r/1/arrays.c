#include <stdio.h>

#define IN   1   /* inside a word */
#define OUT  0   /* outside a word */
#define ASCII_LOWERCASE_OFFSET 97

/* count digits, white space, others */
int main()
// {
//     int c, i, nwhite, nother;
//     int ndigit[10];

//     nwhite = nother = 0;
//     for (i = 0; i < 10; ++i)
//         ndigit[i] = 0;

//     while ((c = getchar()) != EOF)
//         if (c >= '0' && c <= '9')
//             ++ndigit[c-'0'];
//         else if (c == ' ' || c == '\n' || c == '\t')
//             ++nwhite;
//         else
//             ++nother;

//     printf("digits =");
//     for (i = 0; i < 10; ++i)
//         printf(" %d", ndigit[i]);
//     printf(", white space = %d, other = %d\n",
//         nwhite, nother);
// }

// 1-13
// {
//     int c, i, j, wl, state;
//     int ndigit[10];

//     for (i = 1; i < 10; ++i)
//         ndigit[i] = 0;


//     state = OUT;
//     wl = 0;
//     while ((c = getchar()) != EOF) {
//         ++wl;
//         if (c == ' ' || c == '\n' || c == '\t') {
//             // omit 0-length "words"
//             if (state == IN) {
//                 ++ndigit[wl-1];
//             }
//             state = OUT;
//             wl = 0;
//         }
//         else if (state == OUT) {
//             state = IN;
//         }
//     }
//     printf("Word Length Histogram\n");
//     for (i = 1; i < 10; ++i) {
//         printf("%d|", i);
//         for (j = 0; j < ndigit[i]; j++) {
//             printf("@");
//         }
//         printf("\n");
//     }
// }

// 1-14
// only considering lowercase letters for simplicity
{
    int c, i, j, wl, state;
    int nletter[26];

    for (i = 0; i < 26; ++i)
        nletter[i] = 0;
    
    while ((c = getchar()) != EOF) {
        
        if (((c - ASCII_LOWERCASE_OFFSET) >= 0) && ((c - ASCII_LOWERCASE_OFFSET) <= 26)) {
            ++nletter[c-ASCII_LOWERCASE_OFFSET];
        }
    }
    printf("Lowercase Letter Frequency Histogram\n");
    for (i = 0; i < 26; ++i) {
        printf("%c|", i+ASCII_LOWERCASE_OFFSET);
        for (j = 0; j < nletter[i]; j++) {
            printf("@");
        }
        printf("\n");
    }
}