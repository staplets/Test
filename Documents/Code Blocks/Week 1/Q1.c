/* CS261- Assignment 1 - Q.1*/
/* Name: Shaun Stapleton
 * Date: 06/30/14
 * Solution description: Program will Generate random Id's and scores
 * for 10 students and then output them, find the highest and lowest scores,
 *  and the average in class.
 */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>

struct student{
	int id;
	int score;
};

//Allocate memory for array.
//Precondition: struc student created.
//Postcondition: memory allocated for array of students.
struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *p = malloc(10 * sizeof(struct student));

     //Assert that malloc is successful.
     assert(p != 0);


     /*return the pointer*/
     return p;
}

//Precondition: Memory allocated for n number of students.
//Postcondition: Generates randomized array of students with ids and scores.
void generate(struct student* students){



     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/

    students->id = 1 + (rand() %10);


    students->score = (rand()&100);

}

//Output of array.
//Precondition: array filled.
//Postcondition: Output to screen.
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("\nID: %d\t", students[i].id);
        printf("Score: %d\n", students[i].score);

    }
}

//Summary of average, high, and low student scores.
//Precondition: Array full of randomized information.
//Postcondition: results of average, high, and low.
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int i;
     int t;
     int low = students[0].score;
     int lowID;
     int high = students[0].score;
     int highID;
     int total;
     int avg;

    //For loop to find highest and lowest values of array.
     for (i = 1; i < 10; i++ )
     {
         if(students[i - 1 ].score < students[i].score && students[i - 1 ].score < low)
         {
             low = students[i - 1].score;
             lowID = students[i - 1].id;

         }
         else if(students[i - 1 ].score < students[i].score && high < students[i].score)
         {
            high = students[i].score;
            highID = students[i].id;

         }
         else if(students[i - 1].score > students[i].score && low > students[i].score)
         {
             low = students[i].score;
             lowID = students[i].id;

         }
         else if(students[i - 1].score > students[i].score && students[i - 1].score > high)
         {
             high = students[i - 1].score;
             highID = students[i - 1].id;

         }

     }

    //For loop to total up all scores in array.
     for (t = 0; t < 10; t++)
     {
         total = (total + students[t].score);
     }

     //Finding average of scores.
     avg = (total/10);

     //Output of results.
     printf("\nThe minimum score is: %d\t User ID: %d", low, lowID);
     printf("\nThe maximum score is: %d\t User ID: %d", high, highID);
     printf("\nThe average score is: %d\n", avg);

}

//Deallocation of memory.
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free(stud);
}

int main(){
    struct student* stud = NULL;

    //Random number generator.
     srand(time(0));

    /*call allocate*/
    stud = allocate();

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

    do
  {
      generate(&stud[5]);

  }while( stud[5].id == stud[0].id || stud[5].id == stud[1].id || stud[5].id == stud[2].id ||
          stud[5].id == stud[3].id || stud[5].id == stud[4].id);

   do
  {
      generate(&stud[6]);

  }while( stud[6].id == stud[0].id || stud[6].id == stud[1].id || stud[6].id == stud[2].id ||
          stud[6].id == stud[3].id || stud[6].id == stud[4].id || stud[6].id == stud[5].id);

  do
  {
      generate(&stud[7]);

  }while( stud[7].id == stud[0].id || stud[7].id == stud[1].id || stud[7].id == stud[2].id ||
          stud[7].id == stud[3].id || stud[7].id == stud[4].id || stud[7].id == stud[5].id ||
          stud[7].id == stud[6].id);

   do
  {
      generate(&stud[8]);

  }while( stud[8].id == stud[0].id || stud[8].id == stud[1].id || stud[8].id == stud[2].id ||
          stud[8].id == stud[3].id || stud[8].id == stud[4].id || stud[8].id == stud[5].id ||
          stud[8].id == stud[6].id || stud[8].id == stud[7].id);

  do
  {
      generate(&stud[9]);

  }while( stud[9].id == stud[0].id || stud[9].id == stud[1].id || stud[9].id == stud[2].id ||
          stud[9].id == stud[3].id || stud[9].id == stud[4].id || stud[9].id == stud[5].id ||
          stud[9].id == stud[6].id || stud[9].id == stud[7].id || stud[9].id == stud[8].id);

    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
