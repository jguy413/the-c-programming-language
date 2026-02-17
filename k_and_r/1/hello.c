#include <stdio.h>

/*
Modern compilers require explicit return type.

hello.c:3:1: error: return type defaults to ‘int’ [-Wimplicit-int]
    3 | main()
      | ^~~~
*/
int main()
{
    printf("hello world\b");
}
//----------------------------------------------------------------------//
/*
\n : newline
\t : tab
\b : backspace
\" : double quote
\\ : backslash
*/
//----------------------------------------------------------------------//
/* 1-1
; required at EOF

hello.c: In function ‘main’:
hello.c:12:28: error: expected ‘;’ before ‘}’ token
   12 |     printf("hello world\n")
      |                            ^
      |                            ;
   13 | }
      | ~   
*/
//----------------------------------------------------------------------//
/* 1-2
hello.c: In function ‘main’:
hello.c:12:27: warning: unknown escape sequence: '\l'
   12 |     printf("hello world\l");
      |   
*/


