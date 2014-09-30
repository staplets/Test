/* CS261- Assignment 2 - calc.c*/
/* Name: Shaun Stapleton
 * Date: 07/09/14
 * Solution description: Program will read in the command line values
 * and calculate in Reverse Polish Notation.
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};



//Precondition: Operand called that must use two numbers.
////Postcondition: Program will continue if there are enough
//variables to perform the operand.
int isLessThanTwo(DynArr *v)
{
	if(v->size >= 2)
	{
		return 1;
	}

	return 0;
}


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	/* FIXME: You will write this function */
	int pass = 0;
	double uno;
	double dos;
	double sum;

	pass = isLessThanTwo(stack);

	//If there are enough numbers for operand.
	if (pass == 1)
    {
        //get and pop top value.
       dos = topDynArr(stack);
       popDynArr(stack);

       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

       //add values.
       sum = uno + dos;


       //Place sum back in stack.
       pushDynArr(stack, sum);

    }
    else if(pass == 0) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	/* FIXME: You will write this function */
    int pass = 0;
	double uno;
	double dos;
	double diff;

	pass = isLessThanTwo(stack);

	//If there are enough numbers for operand.
	if (pass == 1)
    {
        //get and pop top value.
       dos = topDynArr(stack);
       popDynArr(stack);

       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

       //subtract values.
       diff = uno - dos;


       //Place difference back in stack.
       pushDynArr(stack, diff);

    }
    else if(pass == 0) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	/* FIXME: You will write this function */
    int pass = 0;
	double uno;
	double dos;
	double quotient;

	pass = isLessThanTwo(stack);

	//If there are enough numbers for operand.
	if (pass == 1)
    {
        //get and pop top value.
       dos = topDynArr(stack);
       popDynArr(stack);

       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

       //divide values.
       quotient = (uno/dos);


       //Place quotient back in stack.
       pushDynArr(stack, quotient);

    }
    else if(pass == 0) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void multiply(struct DynArr *stack)
{
	/* FIXME: You will write this function */
    int pass = 0;
	double uno;
	double dos;
	double product;

	pass = isLessThanTwo(stack);

	//If there are enough numbers for operand.
	if (pass == 1)
    {
        //get and pop top value.
       dos = topDynArr(stack);
       popDynArr(stack);

       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

       //multiply values.
       product = (uno * dos);


       //Place product back in stack.
       pushDynArr(stack, product);

    }
    else if(pass == 0) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void power(struct DynArr *stack)
{
	/* FIXME: You will write this function */
    int pass = 0;
	double uno;
	double dos;
	double power;

	pass = isLessThanTwo(stack);

	//If there are enough numbers for operand.
	if (pass == 1)
    {
        //get and pop top value.
       dos = topDynArr(stack);
       popDynArr(stack);

       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

       power = uno;

       //run power of second number on first
       int k;
       for(k = 0; k < dos - 1; k++)
       {
           power *= uno;

       }

       //Place power back in stack.
       pushDynArr(stack, power);

    }
    else if(pass == 0) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void squared(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double square;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign square
       square = (uno * uno);


       //Place power back in stack.
       pushDynArr(stack, square);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void cubed(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double cube;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign square
       cube = (uno * uno * uno);


       //Place power back in stack.
       pushDynArr(stack, cube);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void absolute(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double absolute;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign absolute value
       absolute = abs(uno);

       //Place power back in stack.
       pushDynArr(stack, absolute);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void squareRoot(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double squareRoot;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign sqrt value
       squareRoot = sqrt(uno);

       //Place sqrt back in stack.
       pushDynArr(stack, squareRoot);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void exponential(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double expo;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign exp value
       expo = exp(uno);

       //Place expo back in stack.
       pushDynArr(stack, expo);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void logOutput(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double logValue;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign log value
       logValue = log10(uno);

       //Place log10 back in stack.
       pushDynArr(stack, logValue);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

void lnOutput(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double uno;
	double lnValue;

	//If there are enough numbers for operand.
	if (stack->size >= 1)
    {
       //get and pop top value.
       uno = topDynArr(stack);
       popDynArr(stack);

        //assign ln value
       lnValue = log(uno);

       //Place ln back in stack.
       pushDynArr(stack, lnValue);

    }
    else if(stack->size < 1) //If not enough numbers for operand.
    {
        printf("\n\nThere were not enough numbers for the operand. Exiting...\n\n");

        exit(1);

    }
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;
	TYPE num;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++)
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
			add(stack);
		else if(strcmp(s,"-") == 0)
			subtract(stack);
		else if(strcmp(s, "/") == 0)
			divide(stack);
		else if(strcmp(s, "x") == 0)
			multiply(stack);
		else if(strcmp(s, "^") == 0)
			power(stack);
		else if(strcmp(s, "^2") == 0)
			squared(stack);
		else if(strcmp(s, "^3") == 0)
			cubed(stack);
		else if(strcmp(s, "abs") == 0)
			absolute(stack);
		else if(strcmp(s, "sqrt") == 0)
			squareRoot(stack);
		else if(strcmp(s, "exp") == 0)
			exponential(stack);
		else if(strcmp(s, "ln") == 0)
			lnOutput(stack);
		else if(strcmp(s, "log") == 0)
			logOutput(stack);
        else if(strcmp(s, "pi") == 0)
            //Place pi in stack.
            pushDynArr(stack, 3.14159265);
        else if(strcmp(s, "e") == 0)
            //Place e in stack.
            pushDynArr(stack, 2.7182818);
		else
		{
			// FIXME: You need to develop the code here (when s is not an operator) - Done
			// Remember to deal with special values ("pi" and "e")- Done
            int numResult = 0;

            numResult = isNumber(s, &num);

			if(numResult == 1)
            {
                pushDynArr(stack, num);

            }
            else if (numResult == 0)
            {

                printf("\n\nError, you entered a non number and non operand. Exiting...\n\n");
                exit(1);
            }

		}
	}	//end for

	/* FIXME: You will write this part of the function (2 steps below)
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */

    //Output error is too many numbers were input.
    if(stack->size != 1)
    {
        printf("\n\nLooks like there were more numbers than operands. Exiting...\n\n");
        exit(1);

    }

    //Assign result.
    result = topDynArr(stack);

    //deallocate memory
    deleteDynArr(stack);

	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

    TYPE result;

    //Assign result to result.
	result = calculate(argc,argv);

    //Output result.
	printf("\n\nThe result is %f \n\n",result);

	return 0;
}
