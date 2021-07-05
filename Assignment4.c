#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int* arr; // 배열 (동적할당)
	int n, top; // 배열의 크기 및 top 위치
} Stack;

typedef struct queue {
	Stack S1, S2; // 두 개의 스택 선언
} Queue;

//스택의 각 메쏘드(push, pop, init, is_empty 등)를 개별 함수로 구현 (큐의 ADT와 무관하게 독립적으로 구현)

void init_queue(Queue* Q);
void free_queue(Queue* Q);

// 스택 매소드
void init_stack(Stack *S, int n);
void push(Stack *S, int data);
int pop(Stack *S);
int is_empty(Stack *S);
int is_full(Stack *S);
void free_stack(Stack* S);

// 큐의 메소드
void enqueue(Queue *Q, int data);
void dequeue(Queue *Q);


int main() {

	int m, i, insertNum, de;
	char cal;
	Queue Q;


	// 큐의 초기화를 한다.
	init_queue(&Q);
	
	//2) 두 번째 라인 : 양의 정수 m(연산의 개수)
	scanf("%d", &m);
	 
	//3) 세 번째 이후 라인 : m개의 연산이 차례로 입력됨

	for (i = 0; i < m; i++) {
		// 연산의 종류는 E (삽입), D (삭제)
		getchar();
		scanf("%c", &cal); // 계산식을 받는다.
		if (cal == 'E') { // 삽입
			scanf("%d", &insertNum); // 삽입할 숫자
			enqueue(&Q, insertNum); // 함수 호출
		}
		else if (cal == 'D') 
			dequeue(&Q);	

	}

	free_queue(&Q); // 동적 할당을 해제한다.

	return 0;
}


void init_queue(Queue *Q) {

	int n1, n2;

	//1) 첫 번째 라인 : 양의 정수 n1, n2(두 스택의 크기)
	scanf("%d %d", &n1, &n2);

	// 스택 함수 호출
	init_stack(&Q->S1, n1);
	init_stack(&Q->S2, n2);


}


void init_stack(Stack *S, int n) {

	S->arr = (int*)malloc(sizeof(int) * n); // 스택을 동적할당한다.
	S->n = n; // 최대 갯수
	S->top = -1; // top의 초기값

}



void push(Stack *S, int data) {

	int n = 0; // 이동개수

	if (!is_full(S)) // 꽉 차있지 않을때만 푸시 가능하다.
	{
		S->top++;
		S->arr[S->top] = data;
	}
	else
		printf("overflow\n"); // 아무런 연산을 하지 않는다.

}
int pop(Stack *S) {

	if (!is_empty(S)) { // 비어있지 않을때만 팝 가능하다.
		S->top--;
		return S->arr[S->top + 1];
	}
	else
		printf("underflow\n"); // 출력 후 연산 무시한다.
	return 0;


}
int is_empty(Stack *S) {

	if (S->top == -1) // 비어있다.
		return 1;
	else // 아니다
		return 0;

}
int is_full(Stack *S) {

	if (S->top + 1 == S->n) // 꽉 차있다.
		return 1;
	else // 아니다.
		return 0;
}



void enqueue(Queue *Q, int data) {

	int n = 0; // 이동 횟수를 의미한다.

	if (is_empty(&Q->S2) && is_full(&Q->S1)) { // S1이 가득 차 있을때 S2가 비어있으면 옮긴 후 넣을 수 있다.
		while (!is_empty(&Q->S1))  // 빌때까지 반복
		{
			push(&Q->S2, pop(&Q->S1)); // S1에서 꺼내서 S2에 집어넣는다.
			n++;
		}
	}

	if (!is_full(&Q->S1)) // 꽉차지 않았을때
		printf("+ %d %d\n", data, n); // 출력한다.

	// 삽입한다.
	push(&Q->S1, data);

}
void dequeue(Queue *Q) {

	int n = 0; // 이동횟수를 의미한다.
	int popInt;

	if (!is_empty(&Q->S2)) { // S2에 남아있을때

		printf("- %d %d\n", pop(&Q->S2),n); //출력
		//S2에 원소가 있다면 바로 팝해서 출력한다.
	}
	else { // S2가 비어있을 때

		while (!is_empty(&Q->S1))  // 빌때까지 반복
		{
			push(&Q->S2, pop(&Q->S1)); // S1에서 꺼내서 S2에 집어넣는다.
			n++;
		}

		popInt = pop(&Q->S2); // 팝해서 저장한다.
		if (popInt)
			printf("- %d %d\n", popInt, n); // 비어있지 않을때 출력
		//S2에 원소가 있다면 바로 팝해서 출력한다.

	}

}

void free_queue(Queue* Q) { // 큐 해제
	
	free_stack(&Q->S1); // 모두 메소드를 불러 해제한다
	free_stack(&Q->S2);
}

void free_stack(Stack* S) { // 스택 해제

	free(S->arr); // free
}