#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void push(char** stack, char c);
char pop(char** stack);
char peek(char* stack);
void duplicate(char** stack);
void upRotate(char* stack, int n);
void downRotate(char*stack, int n);
void print(char*stack);

int main() {

	int i, stackNum, calNum, rotate;
	char stack[100], * top = stack - 1, cal[6], data;

	scanf("%d %d", &stackNum, &calNum);


	for (i = 0; i < calNum; i++) {
		getchar();
		scanf("%s", cal);

		// POP, PUSH , PEEK, DUP, UpR, DownR, PRINT
		if (strcmp(cal, "POP") == 0) {
			if (top - stack < 0)
				printf("Stack Empty\n");
			else
				pop(&top);
		}
		else if (strcmp(cal, "PUSH") == 0) {
			getchar();
			scanf("%c", &data);
			if (top - stack + 1 == stackNum)
				printf("Stack FULL\n");
			else 
				push(&top, data);
			
		}
		else if (strcmp(cal, "PEEK") == 0) {
			if (top - stack < 0)
				printf("Stack Empty\n");
			else
				printf("%c\n",peek(top));
		}
		else if (strcmp(cal, "DUP") == 0) {
			if (top - stack + 1 == stackNum)
				printf("Stack FULL\n");
			else 
				duplicate(&top);
			
		}
		else if (strcmp(cal, "UpR") == 0) {
			scanf("%d", &rotate);
			if (rotate <= top - stack + 1)
				upRotate(top, rotate);
		}
		else if (strcmp(cal, "DownR") == 0) {
			scanf("%d", &rotate);
			if (rotate <= top - stack + 1)
				downRotate(top, rotate);
		}
		else if (strcmp(cal, "PRINT") == 0)
			print(top);
	}


	return 0;
}


void push(char** stack, char c) {
	*stack = *stack + 1;
	**stack = c;
}
char pop(char** stack) {

	char returnChar = **stack;
	*stack = *stack - 1;
	return returnChar;
}
char peek(char* stack) {
	char returnChar = *stack;
	return returnChar;
}
void duplicate(char** stack) {

	char* p = *stack;
	char dupChar = pop(&p);
	push(&p, dupChar);
	push(&p, dupChar);
	*stack = *stack + 1;
}
void upRotate(char* stack, int n) {

	int i;
	char* data;

	data = (char*)malloc(sizeof(char) * n);
	for (i = 0; i < n; i++) 
		data[i] = pop(&stack);
	// top이 data[0]에 저장. 이제 top을 제일 먼저 push
	
	push(&stack, data[0]);
	// 그 뒤로는 역순으로 push

	for (i = n - 1; i > 0; i--) 
		push(&stack, data[i]);
	

	free(data);
}
void downRotate(char* stack, int n) {

	int i;
	char* data;

	data = (char*)malloc(sizeof(char) * n);

	for (i = 0; i < n; i++)
		data[i] = pop(&stack);
	
	// top에서 n번째 데이터는 data[n-1]에 존재. 이를 마지막에 푸시
	for (i = n - 2; i >= 0; i--)
		push(&stack, data[i]);

	// 탑에 넣는다.
	push(&stack, data[n-1]);

	free(data);

}
void print(char* stack){

	char* stackp = stack;

	while ((*stackp >= 'a' && *stackp <= 'z') ||
		(*stackp >= 'A' && *stackp <= 'Z')) {
		printf("%c", *stackp);
		stackp--;
	}

	printf("\n");
}