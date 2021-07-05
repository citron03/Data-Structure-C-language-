#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int isOperand(char symbol);
void push(int* stack, int top, int calInt);
int pop(int* stack, int top);

int doOperator(int left, int right, char opr);

int main() {

	char calChar[100];
	int top = -1, N, i, j, stack[100], left, right;
	
	scanf("%d", &N);
	getchar();

	for (i = 0; i < N; i++) {
		j = 0;
		scanf("%s", calChar);

		while (calChar[j]) {
			
			if (!isOperand(calChar[j])) {
				top++;
				push(stack, top, calChar[j] - '0');
			}
			else {

				// 오른쪽 항
				right = pop(stack, top);
				top--;
				// 왼쪽 항
				left = pop(stack, top);
				top--;

				// 계산 후 저장
				top++;
				push(stack, top, doOperator(left, right, calChar[j]));
			}

			
			j++;
		}

		printf("%d\n", pop(stack, top));
	}

	return 0;
}


int isOperand(char symbol) {


	//수식의 연산자는 곱하기, 나누기, 더하기, 빼기로 구성되며, 정수 연산 수행
	if (symbol == '+' ||
		symbol == '-' ||
		symbol == '*' ||
		symbol == '/')
		return 1;
	else
		return 0;
}


void push(int* stack, int top, int calInt) {

	stack[top] = calInt;

}

int pop(int* stack, int top) {
	return stack[top];
}


int doOperator(int left, int right, char opr) {

	switch (opr)
	{
	case '+':
		return left + right;
		break;
	case '-':
		return left - right;
		break;
	case '*':
		return left * right;
		break;
	case '/':
		return left / right;
		break;

	}


}