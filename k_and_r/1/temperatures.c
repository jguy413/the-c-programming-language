#include <stdio.h>

/*
declare function to avoid implicit declaration, expects `int` return value (1-15)

temperatures.c:21:19: error: implicit declaration of function ‘convert_farenheit_to_celsius’ [-Wimplicit-function-declaration]
   21 |         celsius = convert_farenheit_to_celsius(fahr);
      |   
*/
float convert_celsius_to_farenheit(float celsius);
float convert_farenheit_to_celsius(float celsius);


/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300; floating-point version */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

// 1-3
    printf("%3s %6s\n", "F", "C");

    fahr = lower;
    while (fahr <= upper) {
        // celsius = (5.0/9.0) * (fahr-32.0);
        // 1-15
        celsius = convert_farenheit_to_celsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

// 1-4
// int main()
// {
//     float celsius, fahr;
//     int lower, upper, step;

//     lower = -40;      /* lower limit of temperature table */
//     upper = 260;    /* upper limit */
//     step = 20;      /* step size */

//     // 1-3
//     printf("%3s %6s\n", "C", "F");

//     celsius = lower;
//     while (celsius <= upper) {
//         fahr = ((celsius*5.0) / 9.0) + 32.0;
//         printf("%3.0f %6.1f\n", celsius, fahr);
//         celsius = celsius + step;
//     }
// }

// 1-5
// int main()
// {
//     int fahr;

//     for (fahr = 300; fahr >= 0; fahr = fahr - 20)
//         printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
// }

// 1-15
float convert_celsius_to_farenheit(float celsius) {
    float fahr;
    fahr = ((celsius*5.0) / 9.0) + 32.0;
    return fahr;
}

float convert_farenheit_to_celsius (float fahr) {
    float celsius;
    celsius = (5.0/9.0) * (fahr-32.0);
    return celsius;
}