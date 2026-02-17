#include <stdio.h>

#define IN   1   /* inside a word */
#define OUT  0   /* outside a word */

/* count lines, words, and characters in input */
int main()
// {
//     int c, nl, nw, nc, state;

//     state = OUT;
//     nl = nw = nc = 0;
//     while ((c = getchar()) != EOF) {
//         ++nc;
//         if (c == '\n')
//             ++nl;
//         if (c == ' ' || c == '\n' || c == '\t')
//             state = OUT;
//         else if (state == OUT) {
//             state = IN;
//             ++nw;
//         }
//     }
//     printf("%d %d %d\n", nl, nw, nc);
// }
// 1-11
// Test Cases
// asd as asd\n         => 1 3 11 ✓
// sdf\t \tasd\n        => 1 2 10 ✓
// \n                   => 0 0 0  ✓
// d\nd\nasdf           => 3 3 9  ✓
//           \n         => 1 0 11 ✓
// ^[s                  => 1 1 3  ✗ (CTRL-S, ambiguous on how it should be interpreted by the program)
// "non-standard" input could reveal bugs potentially

// 1-12
{
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF) {
        // 43-47 resolves extra line when input ends in ' ' or '\t'... not very pretty
        if ((c == '\n') && (state == OUT)) {
            continue;
        }
        else if (c == ' ' || c == '\t') {
            if (state == IN) {
                // hmm this created an extra line of separation when the input ends in ' ' or '\t'
                putchar('\n');
            }
            state = OUT;
            continue;
        }
        else if (state == OUT) {
            state = IN;
        }
        putchar(c);
    }
}