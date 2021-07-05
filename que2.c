#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//add_front(deque, X) : deque�� �տ� ���� X�� �߰�(�ֱ����� push�� ����). 
//add_rear(deque, X) : deque�� �ڿ� ���� X�� �߰�(�ֱ����� inject�� ����). 
//delete_front(deque) : deque�� �տ� �ִ� ���Ҹ� ��ȯ�� ���� ����(�ֱ����� pop������). 
//delete_rear(deque) : deque�� �ڿ� �ִ� ���Ҹ� ��ȯ�� ���� ����(�ֱ����� eject�� ����). 
//print(deque) : deque�� ��� ���ҵ��� ���ܺ��� �Ĵܱ��� ���ʷ� ���.

typedef struct deque {

	int ele;
	struct deque* next, * prev;

}deque;


void add_front(deque *D, int X);
void add_rear(deque *D, int X);
int delete_front(deque *D);
int delete_rear(deque *D);
void print(deque *D);
void getnode(deque **D);

int main() {

	deque* front, * rear, * p, * q;
	int n, i, addNum;
	char cal[3];


	front = rear = NULL; // �ʱ�ȭ

	scanf("%d", &n);

	for (i = 0; i < n; i++) {

		getchar();
		scanf("%s", cal);

		if (strcmp(cal, "AF") == 0) { // ����Ʈ�� ���Ѵ�.
			scanf("%d", &addNum);

			if (front == NULL) // ó�� ��� ������
			{
				getnode(&front);
				front->ele = addNum;
			}
			else {
				add_front(front, addNum);
				front = front->prev; // ó�� ��ġ ����
			}
			
			if (rear == NULL) // ó�� ��� ����
				rear = front;

		}
		else if (strcmp(cal, "AR") == 0) { // ��� ���Ѵ�.
			scanf("%d", &addNum);

			if (rear == NULL) // ó�� ��� ����
			{
				getnode(&rear);
				rear->ele = addNum;
			}
			else{
				add_rear(rear, addNum);
				rear = rear->next; // �ֱ� ��ġ ����
			}

			if (front == NULL) // ó�� ��� ����
				front = rear;

		}
		else if (strcmp(cal, "DF") == 0) { // ����Ʈ���� �A��.
			
			if (front == rear) {
				printf("underflow");
				return 0;
			}

			p = front->next; // ����Ʈ ��ġ ����
			delete_front(front);

			if (p == NULL) // ���� ��ġ�� ����. �� ������
				front = NULL;
			else
				front = p; // ���ο� ����Ʈ
			
			if (front == NULL) // �ʱ�ȭ ����
				rear = NULL;
		}
		else if (strcmp(cal, "DR") == 0) { // ����� ����.

			if (front == rear) {
				printf("underflow");
				return 0;
			}

			p = rear->prev; // ���� ��ġ ����
			delete_rear(rear);
	
			if (p == NULL) // ������ ���� ��ġ�� ����.
				rear = NULL;
			else
				rear = p; // ���ο� ����

			if (rear == NULL) // �ʱ�ȭ ����
				front = NULL;
		}
		else if (strcmp(cal, "P") == 0)  // ����Ѵ�.
			print(front);

	}

	// free

	p = front;
	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}

	return 0;
}




void add_front(deque* D, int X) {

	deque* p = (deque*)malloc(sizeof(deque));

	p->ele = X;
	p->next = D;
	p->prev = NULL;

	D->prev = p;

}
void add_rear(deque* D, int X) {

	deque* p = (deque*)malloc(sizeof(deque));
	p->ele = X;
	p->prev = D;
	p->next = NULL;

	D->next = p;

}
int delete_front(deque* D) {
	D->next->prev = NULL;
	free(D);
}


int delete_rear(deque* D) {
	D->prev->next = NULL;
	free(D);
}



void print(deque* D) {

	deque* p = D;

	while (p != NULL) {
		printf(" %d", p->ele);
		p = p->next;
	}
	printf("\n");
}


void getnode(deque** D) {

	deque* p = (deque*)malloc(sizeof(deque));
	p->next = NULL;
	p->prev = NULL;

	*D = p;
}