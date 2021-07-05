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

				// ������ ��
				right = pop(stack, top);
				top--;
				// ���� ��
				left = pop(stack, top);
				top--;

				// ��� �� ����
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


	//������ �����ڴ� ���ϱ�, ������, ���ϱ�, ����� �����Ǹ�, ���� ���� ����
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