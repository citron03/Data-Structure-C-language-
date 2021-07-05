#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int* arr; // �迭 (�����Ҵ�)
	int n, top; // �迭�� ũ�� �� top ��ġ
} Stack;

typedef struct queue {
	Stack S1, S2; // �� ���� ���� ����
} Queue;

//������ �� �޽��(push, pop, init, is_empty ��)�� ���� �Լ��� ���� (ť�� ADT�� �����ϰ� ���������� ����)

void init_queue(Queue* Q);
void free_queue(Queue* Q);

// ���� �żҵ�
void init_stack(Stack *S, int n);
void push(Stack *S, int data);
int pop(Stack *S);
int is_empty(Stack *S);
int is_full(Stack *S);
void free_stack(Stack* S);

// ť�� �޼ҵ�
void enqueue(Queue *Q, int data);
void dequeue(Queue *Q);


int main() {

	int m, i, insertNum, de;
	char cal;
	Queue Q;


	// ť�� �ʱ�ȭ�� �Ѵ�.
	init_queue(&Q);
	
	//2) �� ��° ���� : ���� ���� m(������ ����)
	scanf("%d", &m);
	 
	//3) �� ��° ���� ���� : m���� ������ ���ʷ� �Էµ�

	for (i = 0; i < m; i++) {
		// ������ ������ E (����), D (����)
		getchar();
		scanf("%c", &cal); // ������ �޴´�.
		if (cal == 'E') { // ����
			scanf("%d", &insertNum); // ������ ����
			enqueue(&Q, insertNum); // �Լ� ȣ��
		}
		else if (cal == 'D') 
			dequeue(&Q);	

	}

	free_queue(&Q); // ���� �Ҵ��� �����Ѵ�.

	return 0;
}


void init_queue(Queue *Q) {

	int n1, n2;

	//1) ù ��° ���� : ���� ���� n1, n2(�� ������ ũ��)
	scanf("%d %d", &n1, &n2);

	// ���� �Լ� ȣ��
	init_stack(&Q->S1, n1);
	init_stack(&Q->S2, n2);


}


void init_stack(Stack *S, int n) {

	S->arr = (int*)malloc(sizeof(int) * n); // ������ �����Ҵ��Ѵ�.
	S->n = n; // �ִ� ����
	S->top = -1; // top�� �ʱⰪ

}



void push(Stack *S, int data) {

	int n = 0; // �̵�����

	if (!is_full(S)) // �� ������ �������� Ǫ�� �����ϴ�.
	{
		S->top++;
		S->arr[S->top] = data;
	}
	else
		printf("overflow\n"); // �ƹ��� ������ ���� �ʴ´�.

}
int pop(Stack *S) {

	if (!is_empty(S)) { // ������� �������� �� �����ϴ�.
		S->top--;
		return S->arr[S->top + 1];
	}
	else
		printf("underflow\n"); // ��� �� ���� �����Ѵ�.
	return 0;


}
int is_empty(Stack *S) {

	if (S->top == -1) // ����ִ�.
		return 1;
	else // �ƴϴ�
		return 0;

}
int is_full(Stack *S) {

	if (S->top + 1 == S->n) // �� ���ִ�.
		return 1;
	else // �ƴϴ�.
		return 0;
}



void enqueue(Queue *Q, int data) {

	int n = 0; // �̵� Ƚ���� �ǹ��Ѵ�.

	if (is_empty(&Q->S2) && is_full(&Q->S1)) { // S1�� ���� �� ������ S2�� ��������� �ű� �� ���� �� �ִ�.
		while (!is_empty(&Q->S1))  // �������� �ݺ�
		{
			push(&Q->S2, pop(&Q->S1)); // S1���� ������ S2�� ����ִ´�.
			n++;
		}
	}

	if (!is_full(&Q->S1)) // ������ �ʾ�����
		printf("+ %d %d\n", data, n); // ����Ѵ�.

	// �����Ѵ�.
	push(&Q->S1, data);

}
void dequeue(Queue *Q) {

	int n = 0; // �̵�Ƚ���� �ǹ��Ѵ�.
	int popInt;

	if (!is_empty(&Q->S2)) { // S2�� ����������

		printf("- %d %d\n", pop(&Q->S2),n); //���
		//S2�� ���Ұ� �ִٸ� �ٷ� ���ؼ� ����Ѵ�.
	}
	else { // S2�� ������� ��

		while (!is_empty(&Q->S1))  // �������� �ݺ�
		{
			push(&Q->S2, pop(&Q->S1)); // S1���� ������ S2�� ����ִ´�.
			n++;
		}

		popInt = pop(&Q->S2); // ���ؼ� �����Ѵ�.
		if (popInt)
			printf("- %d %d\n", popInt, n); // ������� ������ ���
		//S2�� ���Ұ� �ִٸ� �ٷ� ���ؼ� ����Ѵ�.

	}

}

void free_queue(Queue* Q) { // ť ����
	
	free_stack(&Q->S1); // ��� �޼ҵ带 �ҷ� �����Ѵ�
	free_stack(&Q->S2);
}

void free_stack(Stack* S) { // ���� ����

	free(S->arr); // free
}