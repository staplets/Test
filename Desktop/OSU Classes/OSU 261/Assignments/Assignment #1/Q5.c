/* CS261- Assignment 1 - Q.5*/
/* Name: Shaun Stapleton
 * Date: 06/30/14
 * Solution description: Request input and retun the input back to the user
 * in sticky caps. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

//Function to put word in sticky caps
//Precondition: word entered into interface
//Postcondition: Word in sticky caps.
void sticky(char* word){
     /*Convert to sticky caps*/
     int size = strlen(word);
     int i;

     for(i = 0; i < size; i++)
     {
         //Even letters are changed to upper case.
         //If already upper case they are left alone.
        if(i%2 == 0)
        {
            if(islower(word[i]))
            {
                word[i] = toUpperCase(word[i]);
            }
        }
        //Odd letters are changed to lower case.
        //If already lower case they are left alone.
        else if (i%2 == 1)
        {
            if(isupper(word[i]))
            {
                word[i] = toLowerCase(word[i]);
            }

        }

     }
}

int main(){
    /*Read word from the keyboard using scanf*/
    printf("\nPlease input a word and I will turn it into sticky caps: \n");

    char string[50];
    scanf("%s", string);

    /*Call sticky*/
    sticky(string);

    /*Print the new word*/
    printf("\n%s\n\n", string);

    return 0;
}
