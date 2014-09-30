/* CS261- Assignment 1 - Q.2*/
/* Name: Shaun Stapleton
 * Date: 06/30/14
 * Solution description: I will initialize three variables and then pass two by reference
 * through the foo function and return the value. I will then print out the three variables
 * again to show which ones have been altered.
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = (*a * 2);

    /*Set b to half its original value*/
    *b = (*b/2);

    /*Assign a+b to c*/
    c = (*a + *b);

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;

    /*Print the values of x, y and z*/
    printf("\nInt x: %d\t Int y: %d\t Int z: %d\n", x, y, z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
    int returnValue = foo(&x, &y, z);

    /*Print the value returned by foo*/
    printf("\nValue Returned from foo: %d\n", returnValue);

    /*Print the values of x, y and z again*/
    printf("\nValues again: int x: %d\t int y: %d\t int z: %d\n", x, y ,z);

    /*Is the return value different than the value of z?  Why?*/
    return 0;
}

///// Answer: Yes the value returned is 13 whereas the value of z is still 7. This is due to the fact
///// that z was not returned by reference by but value in the function. Therefore the value remained
///// unchanged. Pointers ensure passing by reference when alterations are desired.
