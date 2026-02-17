#include <stdio.h>

int main()
// {
//     int c;
//     int char_is_not_eof;
//     int expression_always_0_or_1;
//     /*
//     CTRL-D => EOF on Debian Linux
//     */
//     expression_always_0_or_1 = 0;
//     do {
//         c = getchar();
//         char_is_not_eof = (c != EOF);
//         if ((char_is_not_eof != 0) && (char_is_not_eof != 1)) {
//             ++expression_always_0_or_1;
//         }
//         if (c != EOF) {
//             putchar(c); // sneaky hidden '\n' from our `getchar()`!
//         }
//     } while (c != EOF);
    
// // 1-7
//     printf("\nEOF evaluates to %d\n", c);


// // 1-6
//     if (expression_always_0_or_1 > 0) {
//         printf("(getchar() != EOF) does not always evaluate to 0 or 1!");
//     }
// }

// 1-8
// {
//     int c, nl;

//     nl = 0;
//     while ((c = getchar()) != EOF)
//         if ((c == ' ') || (c == '\t') || (c == '\n')) 
//             ++nl;
//     printf("total blanks/tabs/newlines: %d\n", nl);
// }

// 1-9
// {
//     int c, last;
//     last = 0;
//     while ((c = getchar()) != EOF) {
//         if ((c == ' ') && (last == ' ')) {
//             ;
//         } else {
//             putchar(c);
//         }
//         last = c;
//     }
// }

// 1-10
{
    int c;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '\t':
                putchar('\\');
                putchar('t');
                break;
            // not actually needed as handled by terminal?
            case '\b':
                putchar('\\');
                putchar('b');
                break;
            case '\\':
                putchar('\\');
                putchar('\\');
                break;
            default:
                putchar(c);
        }
    }
}
