#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000    /* maximum input line size */

// int getline(char line[], int maxline);
int readline(char *s[], size_t *ss);
int grow(char *s[], size_t *ss);
void reverse(char s[], size_t ss);
void copy(char to[], char from[]);

/* print longest input line */
// int main()
// {
//     int len;            /* current line length */
//     int max;            /* maximum length seen so far */
//     char line[MAXLINE];     /* current input line */
//     char longest[MAXLINE];  /* longest line saved here */

//     max = 0;
//     while ((len = getline(line, MAXLINE)) > 0)
//         if (len > max) {
//             max = len;
//             copy(longest, line);
//         }
//     if (max > 0)    /* there was a line */
//         printf("%s", longest);
//     return 0;
// }
// 1-16
/* print longest line of arbitrary length */
int main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    size_t cap = 8;
    char *line = (char *)malloc(cap);
    char *longest = (char *)malloc(cap);

    max = 0;
    while ((len = readline(&line, &cap)) > 0) {
        if (len == -1) {
            return EXIT_FAILURE;
        }
        // if (len > max) {
        //     max = len;
        //     copy(longest, line);
        // }
        // // 1-17
        // if (len > 80) {
        //     printf("%d > 80 for input: %s\n", len, line);
        // }
        // 1-18
        if ((len == 1) && ((line[0] == '\n') || (line[0] == '\t') || (line[0] == ' ')))  {
            continue;
        }
        printf("%s\n", line);
        // 1-19
        reverse(line, len);
        printf("%s\n", line);
    }
    // if (max > 0)    /* there was a line */
    //     printf("Longest Line: %s", longest);
    return EXIT_SUCCESS;
}

/* 
readline:  read a line into s, return length 
we pass char **s, i.e. *s[], because we are not just modifying the contents of the buffer
but with reallocation may update the address of the buffer.. else it would be sufficient to pass *s, i.e. s[]
*/
int readline(char *s[], size_t *ss)
{
    int c, i, nb;
    nb=0;
    for (i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
        // `>=` instead of `==` "defensive"...
        if (i+1 >= *ss) { 
            if (grow(s, ss) == -1) {
                return -1;
            }
        }

        if (!((c == '\t') || (c == ' '))) {
            nb = i;
        }

        (*s)[i] = c;
    }
    if (c == '\n') {
        if (i+1 >= *ss) { 
            if (grow(s, ss) == -1) {
                return -1;
            }
        }
        (*s)[i] = c;
        ++i;
    }
    // (*s)[i] = '\0';
    // return i;

    // 1-18
    /*
    two approaches... 
    - can iterate in reverse after reading all input characters, removing blanks/tabs until a valid character is found
    - can create a non-blank-tracking variable 'nb' to mark the index of last non-blank character... after reading string, move '\0' to nb+1 
    */ 
    (*s)[nb+1] = '\0';
    // printf("index of last non-blank character: %d\n", nb);
    if (c == EOF) {
        return 0;
    } else {
        return nb+1;
    }
}


// 1-19
// /* reverse:  copy 'from' into 'to' in reverse order; assume to is big enough */
void reverse(char s[], size_t ss)
{
    int i, j;
    char temp;

    i = 0;
    j = ss - 1;
    while (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        ++i;
        --j;
    }
}

/* 
Resize character array for dynamic inputs
free(*s) -> cleanup on failure instead of leaving buffer usable
*/
int grow(char *s[], size_t *ss) {
    printf("Resizing buffer...\n");
    size_t cap = *ss * 2;
    char *tmp = (char *)realloc(*s, cap);
    if (tmp == NULL) {
        perror("Reallocation failed");
        free(*s);
        return -1;
    }
    else {
        *s = tmp;
        *ss = cap;
    }
    return 0;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}