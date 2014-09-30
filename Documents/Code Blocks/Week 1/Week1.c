//First C program to say Hello

#include <stdio.h>

int main()
{
    int x;
    int y;

    printf("\nHello, \n\nPlease enter an integer and I will tell you if it's even or odd.\n\n");

    scanf ("%d", &x);

    y = x % 2;

    if (y == 0)
    {
        printf("\n%d is even.\n\n", x);
    }
    else if (y == 1)
    {
        printf("\n%d is odd.\n\n", x);
    }
    else
    {
        printf("\nMy program doesn't work : ( \n\n");
    }

    return 0;

}
