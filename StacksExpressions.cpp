/*  Program: Calculator v1.2 (WITH EXTRA CREDIT 1 AND 2)
 *	Author: Daniel Zelfo
 *	Class: CSCI 220
 *	Date: 10/14/2019
 *	Description: This program is made up of a calculator class which can return the postfix notation of an expression, and evaluate any mathematical expression
 *				 The Calculator class uses a stack data structure to obtain the postfix notation of any given expression and evaluated an expression using its postfix notation
 *				 The Calculator can also handle expression with variables
 *				 The Calculator class is also able to validate mathematical expressions
 *	I certify that the code below is my own work.
 *
 *	Exception(s): N/A
 *
 */

#include <iostream>
#include "Calculator.h"
int main()
{
	//initializing the expression and variables strings
	string expression, variables;

	//creating the calculator object
	Calculator calc;

	//outputting the program information
	cout << "Daniel Zelfo's Calculator" << endl
		 << "Enter 0 to exit the program." << endl

	//asking the user for the expression
		 << "Enter an expression: ";
	//inputting the expression
	getline(cin, expression);
	//asking the user for the variables (if any exist)
	cout << "Enter variable values (e.g. x = 2) seperated with commas (optional): ";
	//inputting the variables
	getline(cin, variables);

	//continuing until the user enters 0
	while (expression != "0" && variables != "0") {
		//setting the expression and variables in the calculator object
		try {
			calc.setExpr(expression);
		} catch (string err) {
			cout << err << endl;
			return 0;
		}
		calc.setVars(variables);

		//outputting the postfix expression
		cout << "Postfix expression: " << calc.postfix() << endl
		//outputting the evaluation of the expression
			 << "Result: " << calc.eval() << endl

		//getting another expression from the user
			 << "Enter an expression: ";
			 getline(cin, expression);
		//stopping if the user entered 0
		if (expression == "0") break;
		//getting the variables values of that expression from the user
		cout << "Enter variable values (optional): ";
			 getline(cin, variables);
	}
	return 0;
}
