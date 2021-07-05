#include <stdio.h>
#include <stdlib.h>


int push(char* stack, int top ,char c);
char pop(char* stack , int top);

int main() {

	char calString[1000], stack[1000], compare;
	int i = 0, top = -1, OK = 0, totalNum = 0;

	gets(calString);

	while (calString[i]) {

		if (calString[i] == '(' || calString[i] == '{' || calString[i] == '[') {
			top = push(stack, top, calString[i]);
			totalNum++;
		}
		 else if(calString[i] == ')' || calString[i] == '}' || calString[i] == ']'){
			compare = pop(stack, top);
			top--;
			if (compare == '('  && calString[i] == ')'  
				|| compare == '{' && calString[i] == '}'
				|| compare == '[' && calString[i] == ']')
				OK += 2;
			totalNum++;
		}
		i++;
	}


	if (OK == totalNum)
		printf("OK_%d", totalNum);
	else
		printf("Wrong_%d", totalNum);


	return 0;
}


int push(char* stack, int top, char c) {
	top++;
	stack[top] = c;
	return top;
}
char pop(char* stack, int top) {

	char topChar = stack[top];
	return topChar;
}