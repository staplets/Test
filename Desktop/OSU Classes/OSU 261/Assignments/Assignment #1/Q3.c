/* CS261- Assignment 1 - Q.3*/
/* Name: Shaun Stapleton
 * Date: 06/30/14
 * Solution description: Allocate memory for and fill an array with random numbers.
 *  Then sort the numbers and print out.
 */

#include <stdio.h>
#include <assert.h>
#include<stdlib.h>
#include<math.h>


//Sort Function for random numbers in array.
//Precondition: Array holding random numbers is entered into
//sort call.
//Postcondition: Numbers are sorted in ascending order.
void sort(int* number, int n){
     /*Sort the given array number , of length n*/
      int s;
      int nextSmallest;
      int tempArray[n];


    for(s = 0; s < n - 1; s++)
    {
       nextSmallest = indexOfSmallest(number, s, n);
       //swapValues(number[s], number[nextSmallest]);

       int temp;
       temp = number[s];
       number[s] = number[nextSmallest];
       number [nextSmallest] = temp;

    }
}



//Function for sort function to find the smallest number each iteration.
//Precondition: Sort Function called
//Postcondition: Smaller number assigned to smallest index.
int indexOfSmallest(int *number, int startIndex, int n)
{

    int min = number[startIndex];
    int indexOfMin = startIndex;
    int k;

    //Find smallest number each time.
    for(k = startIndex + 1; k < n; k++ )
    {
        if (number[k] < min)
        {

            //Assigns smallest number accordingly.
            min = number[k];
            indexOfMin = k;

        }

    }

    return indexOfMin;
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    //Random number generator.
     srand(time(0));

    /*Allocate memory for an array of n integers using malloc.*/
     int *array = malloc(sizeof(int) * n );

      //Assert that malloc is successful.
     assert(array != 0);

    /*Fill this array with random numbers, using rand().*/
    int i;

    for (i = 0; i < n; i++)
    {

         array[i] = 1 + (rand() %20);
    }

    /*Print the contents of the array.*/
    int k;

    for(k = 0; k < n; k++)
    {

        printf("\n%d\n", array[k]);
    }

    /*Pass this array along with n to the sort() function of part a.*/

    sort(array,n);


    /*Print the contents of the array.*/
    int w;

    for(w = 0; w < 20;  w++ )
    {
        printf("\n%d: %d\n", w + 1, array[w]);

    }


    free(array);

    return 0;
}
