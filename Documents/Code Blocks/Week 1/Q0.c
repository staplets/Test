/* CS261- Assignment 1 - Q. 0*/
/* Name: Shaun Stapleton
 * Date: 06/30/14
 * Solution description: Declaring and initializing int x
 * and then passing the value by reference to a function
 * fooA where the values pointed to, memory address and values
 * are printed out.
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("\nValue pointed to by iptr: %d \n", *iptr);

     /*Print the address pointed to by iptr*/
     printf("\nAddress pointed to by iptr: %d \n", iptr);

     /*Print the address of iptr itself*/
     printf("\nAddress of iptr: %d \n", &iptr);
}

int main(){

    /*declare an integer x and assigning the value 4*/
    int x = 4;

    /*print the address of x*/
    printf("\nAddress of x: %d \n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*print the value of x*/
    printf("\nValue of x: %d \n", x);

    return 0;
}
