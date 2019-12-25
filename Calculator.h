#include "Stack.h"
#include <string>
#include <map>
#include <math.h>

using namespace std;

class Calculator {
private:
	/*
	 * DATA MEMBERS
	 * expression - the expression given by the user, in infix form
	 * variables - a map including all the variables inside the expression as keys and their respective values
	 */
	string expression;
	map<string, double> variables;

	//returns true if a character is one of the operators supported by this program
	bool isOperator(char tar) {
		//making a character array with all the supported operators
		const int NUMOPS = 5;
		char ops[NUMOPS] = { '^', '*', '/', '+', '-' };

		//looking through each operant and checking if is is equal to the given character
		for (int i = 0; i < NUMOPS; i++)
			//returning true if it is equal to one of the operators
			if (ops[i] == tar)
				return true;
		//if we have reached this point, then the character is not equal to any of the operators, so we will return false
		return false;
	}


	//the is one of the functions used to obtain the values of the variables
	//this function takes a string and a character to split the string with and sets an array to the seperated strings
	void splitSTR(string str, char tar, int arrSize, string* res) {
		//we will not do anything if the new array will be of size 0
		if (arrSize <= 0) return;

		//making a varialbe for the index of the current element of the atring array, cur
		//making two variables for the start and end of the current substring of the given string
		int cur = 0;
		int i = 0, j;
		//looping through each character of the string
		for (j = i; j < str.length(); j++) {
			//if we reached the character that we will split at, we will set the element at the index of cur to the substring from i to j
			if (str[j] == tar) {
				res[cur++] = str.substr(i, j - i);
				//setting i (the starting point of the substrings) to j+1
				i = j + 1;
			}
		}
		//setting the last element of the string array
		res[cur] = str.substr(i, j - i);
		
	}

	//the is one of the functions used to obtain the values of the variables
	//this function counts the occurances of a character in a string
	int count(string str, char tar) {
		//initializing the variable with the total count
		int res = 0;
		
		//looping through each character of the string
		for (int i = 0; i < str.length(); i++) {
			//incrementing the res variable if we found an equal character
			if (str[i] == tar)
				res++;
		}
		//returning the total count
		return res;
	}
	
	//these functions help get the variable name(s)
	//these three functions are used to trim strings (remove outer white space)
	string& ltrim(string& str, const string& chars = "\t\n\v\f\r{ "){
		str.erase(0, str.find_first_not_of(chars));
		return str;
	}
	string& rtrim(string& str, const string& chars = "\t\n\v\f\r} "){
		str.erase(str.find_last_not_of(chars) + 1);
		return str;
	}
	string trim(string str, const string& chars = "\t\n\v\f\r{} "){
		return ltrim(rtrim(str, chars), chars);
	}

	//the is one of the functions used to obtain the values of the variables
	//this function takes an array of strings cotaining each varialbe and is value and adds them to a map containing all the variables and their values
	map<string, double> arrToMap(string* arr, int size) {
		//declaring the map, the key and the value variables
		map<string, double> res;
		string key;
		double value;
		//looping through each element of the string array
		for (int i = 0; i < size; i++) {
			//splitting the string into the key and the value
			splitKeyValue(arr[i], key, value);

			//adding the key, value pair to the map
			res.insert(pair<string, double>(trim(key), value));
		}
		//returning the map
		return res;
	}

	//the is one of the functions used to obtain the values of the variables
	//this function takes a string represting a variable and is value and sets the key parameter to the variable name and the value parameter to the value
	void splitKeyValue(string keyValuePair, string& key, double& value) {
		//initializing the vairiable that will be the index of the equals sign in the string
		int i;
		//increasing the index until we reach the equals sign
		for (i = 0; i < keyValuePair.length(); i++)
			if (keyValuePair[i] == '=')
				break;
		
		//setting the key to the substring from 0 to the index of the equals sign
		key = keyValuePair.substr(0, i);

		//setting the value to the the substring from the index of the equals sign plus one to the end of the string, parsed as a double
		value = stod(trim(keyValuePair.substr(i + 1, keyValuePair.length() - i - 1)));
	}

	//this function returns whether or not a string is a variable - this is done by returning true if a letter is inside the string
	bool isVariable(string str) {
		//looping through each character of the string
		for (int i = 0; i < str.length(); i++)
			//if we found a letter we will return true
			if (isalpha(str[i]))
				return true;
		//we will return false if we reached this point because none of the characters in the string are letters
		return false;
	}

	//this function is used return a boolean value for whether or not the expression is valid
	//an expression is invalid if it contains more opening parentheses than closing parentheses, and vice versa
	//an expression is invalid if it contains at least two concurrent operators that aren't the minus operators
	bool validExpression(string exp) {
		//declaring a variable to be a temporary index of the string
		int tempI;
		//initializing a variable for the different between opening and closing parentheses to 0
		int parentheses = 0;
		//looping through each character of the string (from end to start)
		for (int i = exp.length() - 1; i >= 0; i--) {
			//we will decrement the parentheses varialbe if we find a closing parenthesis
			if (exp[i] == ')')
				parentheses--;
			//we will increment the parentheses varialbe if we find an opening parenthesis
			else if (exp[i] == '(')
				parentheses++;
			//checking if the current character is an operant
			else if (isOperator(exp[i])) {
				//we will set the temporary index of the string to the current index of the string
				tempI = i;
				//decrementing the temporary index of the string until we reach anything other than a space
				while (tempI >= 1 && exp[--tempI] == ' ');

				//if we reached an operant, we did not decrement the temporary index at all, or we reached an opening parenthesis AND the operant that we were looking ar is not a negative, then we will return false
				//this is because this means that we either have two operators after one another that arent negative operators (e.g. 2 ** 2), or we have an operant that isnt a negative by itself before a number or variable (e.g. ^2 + 1)
				if ((tempI == i || isOperator(exp[tempI]) || exp[tempI] == '(') && exp[i] != '-') {
					throw string("Illegal Expression: Invalid operators.");
					return false;
				}
			}
		}
		//we will return the boolean value for whether or not the difference in the opening an closing parenthesis is equal to 0
		if (parentheses != 0) {
			throw string("Illegal Expression: Unequal number of opening and closing parentheses.");
			return false;
		}
		return true;
	}

public:
	//default contractor
	Calculator() {}

	//constructor with the infix expression
	Calculator(string exp) {
		setExpr(exp);
	}

	//destructor
	~Calculator() {

	}

	//expression setter
	void setExpr(string exp) {
		if (validExpression(exp)) expression = exp;
	}

	//variables setter
	void setVars(string vars) {
		//initializing the splitter to a comma
		char splitter = ',';
		//initializng the array of the variables and their values to the number of commas in the given string plus 1
		int splitSize = (vars.length() == 0 ? 0 : count(vars, splitter) + 1);
		string* arr = new string[splitSize];

		//splitting the string into an array with each variable and its value
		splitSTR(vars, splitter, splitSize, arr);

		//setting the variables map to a map with all the variables as keys and values as values
		variables = arrToMap(arr, splitSize);
	}

	//expression getter
	string getExpr() {
		return expression;
	}

	//the postfix function - returns the postfix form of the expression that the used set
	string postfix() {
		//initializing the operators stack, the result string (of the postfix expression), the current index in the string of the expression
		Stack<char>* operators = new Stack<char>;
		string res = "";
		int cur = 0, tempCur;

		//we will loop through each character of the expression
		for (int cur = 0; cur < expression.length(); cur++) {
			
			//if the current character is a space, we will continue to the next character
			if (expression[cur] == ' ') continue;
			
			//checking if the current character is an operant
			if (isOperator(expression[cur])) {
				
				//we will chech if the current character is a minus sign, to handle possible negative numbers
				if (expression[cur] == '-') {
					//we will make the temporary index equal to the current index
					tempCur = cur;
					//we will decrement the temporary index until we reach a non-space character
					while (tempCur >= 1 && expression[--tempCur] == ' ');
					
					//checking if the index did not change, we reached another operant, or we reached an opening parenthesis
					if (tempCur == cur || isOperator(expression[tempCur]) || expression[tempCur] == '(') {
						//we will treat the current character as a digit or letter and continue to the next character
						res += expression[cur];
						continue;
					}
				}
				
				//looping while the operators stack is not empty and we have not reached an opening parenthesis or an operant of higher presidence than the current operant
				while (!operators->empty() && operators->top() != '(' && (operators->top() != '+' && operators->top() != '-' || expression[cur] != '*' && expression[cur] != '/' && expression[cur] != '^') && (operators->top() != '*' && operators->top() != '/' || expression[cur] != '^') && (operators->top() != '^' || expression[cur] != '^')) {
					//we will add the top of the stack to the result string
					res += " ";
					res += operators->top();
					//we will pop the stack
					operators->pop();
				}
				//now we will push the current operant
				operators->push(expression[cur]);
				res += " ";
			}
			//we will push any opening parenthesis
			else if (expression[cur] == '(') 
				operators->push(expression[cur]);
			
			//checking if the current character is a closing parenthesis
			else if (expression[cur] == ')') {
				//we will add the top of the stack to the result string until we reach a closing parenthesis
				while (operators->top() != '(') {
					res += " ";
					res += operators->top();
					operators->pop();
				}
				//poping the opening parenthesis
				operators->pop();
			}
			//otherwise, we will add the current character to the result string
			else
				res += expression[cur];

		}

		//now we will pop the top of the operators stack until it is empty
		while (!operators->empty()) {
			res += " ";
			res += operators->top();
			operators->pop();
		}

		delete operators;

		return res;
	}

	//the eval function - returns the evaluated expression as a value
	double eval() {
		//initializing the postfix expression
		string postfixSTR = postfix();

		//initializng the double stack with the operands
		Stack<double>* operands = new Stack<double>;

		//declaring the two operants, the string of the current operand, and a temporary index
		double op1, op2;
		string curV;
		int tempCur;

		//looping through each character of the postfix expression
		for (int cur = 0; cur < postfixSTR.length(); cur++) {
			//we will skip spaces
			if (postfixSTR[cur] == ' ')  continue;

			//checking if we reached an operand
			if ((postfixSTR[cur] == '-' && (isdigit(postfixSTR[cur + 1]) || isalpha(postfixSTR[cur + 1])) || isdigit(postfixSTR[cur]) != 0) || isalpha(postfixSTR[cur])) {
				//setting the temporary index to the current index plus 1
				tempCur = cur + 1;
				//while we are still in the operand, we wil increase the ending index of the substring of the postfix expression
				while (isdigit(postfixSTR[tempCur]) != 0 || postfixSTR[tempCur] == '.' || isalpha(postfixSTR[tempCur]))
					tempCur++;

				//setting the current operand string to the substring from the beginning of the operand to the end
				curV = postfixSTR.substr(cur, tempCur - cur);

				//pushing the operand or its value if it is a variable
				operands->push((isVariable(curV) ? variables[curV] : stod(curV)));

				//setting the current index to the end of the operand
				cur = tempCur - 1;
			}

			//checking if the current character is an operator
			else if (isOperator(postfixSTR[cur])) {

				//getting the two operators, which are the top two operands in the stack
				op2 = operands->top();
				operands->pop();
				op1 = operands->top();
				operands->pop();
				
				//applying the appropriate operation
				if (postfixSTR[cur] == '^')
					operands->push(pow(op1, op2));
				else if (postfixSTR[cur] == '*')
					operands->push(op1 * op2);
				else if (postfixSTR[cur] == '/')
					operands->push(op1 / op2);
				else if (postfixSTR[cur] == '+')
					operands->push(op1 + op2);
				else if (postfixSTR[cur] == '-')
					operands->push(op1 - op2);
			}

		}

		//we will now return the top of the operands stack (to only remaining operand)

		op1 = operands->top();
		delete operands;
		return op1;
	}

};