/* CS261- Assignment 1 - Q.4*/
/* Name: Shaun Stapleton
 * Date: 06/30/14
 * Solution description: Sort student structs in ascending order in array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

//Allocate memory for array.
//Precondition: struc student created.
//Postcondition: memory allocated for array of students.
struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *p = malloc(5 * sizeof(struct student));

     //Assert that malloc is successful.
     assert(p != 0);


     /*return the pointer*/
     return p;
}

//Sort Function for random numbers in array.
//Precondition: Array holding random numbers is entered into
//sort call.
//Postcondition: Numbers are sorted in ascending order.
void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
    int s;
    int nextSmallest;
    int tempArray[n];

    for(s = 0; s < n - 1; s++)
    {
       nextSmallest = indexOfSmallest(students, s, n);
       //swapValues(number[s], number[nextSmallest]);

       struct student temp;
       temp = students[s];
       students[s] = students[nextSmallest];
       students[nextSmallest] = temp;

    }
}



//Function for sort function to find the smallest number each iteration.
//Precondition: Sort Function called
//Postcondition: Smaller number assigned to smallest index.
int indexOfSmallest(struct student *students, int startIndex, int n)
{

    int min = students[startIndex].score;
    int indexOfMin = startIndex;
    int k;

    //Find smallest number each time.
    for(k = startIndex + 1; k < n; k++ )
    {
        if (students[k].score < min)
        {

            //Assigns smallest number accordingly.
            min = students[k].score;
            indexOfMin = k;

        }

    }

    return indexOfMin;
}

//Precondition: Memory allocated for n number of students.
//Postcondition: Generates randomized array of students with ids and scores.
void generate(struct student* students){

     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    students->id = 1 + (rand() %5);


    students->score = (rand()&100);

}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("\nID: %d\t", students[i].id);
        printf("Score: %d\n", students[i].score);

    }
}


int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 5;

    //Random number generator.
     srand(time(0));

    //student pointer
    struct student* stud = NULL;

    /*Allocate memory for n students using malloc.*/
    stud = allocate();



    /*Generate random IDs and scores for the n students, using rand().*/
    /*call generate for all values to ensure unique ids*/
   generate(&stud[0]);

    do
  {
      generate(&stud[1]);

  }while( stud[1].id == stud[0].id);

       do
  {
      generate(&stud[2]);

  }while( stud[2].id == stud[0].id || stud[2].id == stud[1].id);

    do
  {
      generate(&stud[3]);

  }while( stud[3].id == stud[0].id || stud[3].id == stud[1].id || stud[3].id == stud[2].id);

   do
  {
      generate(&stud[4]);

  }while( stud[4].id == stud[0].id || stud[4].id == stud[1].id || stud[4].id == stud[2].id ||
          stud[4].id == stud[3].id );


    /*Print the contents of the array of n students.*/
    printf("\nContents of array prior to sorting.\n\n");
    output(stud);

    /*Pass this array along with n to the sort() function*/
    sort(stud, n);

    /*Print the contents of the array of n students.*/
    printf("\n\nContents of array after sorting.\n\n");
    output(stud);

    return 0;
}
