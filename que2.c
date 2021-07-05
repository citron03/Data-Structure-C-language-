#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//add_front(deque, X) : deque의 앞에 원소 X를 추가(주교재의 push와 동일). 
//add_rear(deque, X) : deque의 뒤에 원소 X를 추가(주교재의 inject와 동일). 
//delete_front(deque) : deque의 앞에 있는 원소를 반환한 다음 삭제(주교재의 pop과동일). 
//delete_rear(deque) : deque의 뒤에 있는 원소를 반환한 다음 삭제(주교재의 eject와 동일). 
//print(deque) : deque의 모든 원소들을 전단부터 후단까지 차례로 출력.

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


	front = rear = NULL; // 초기화

	scanf("%d", &n);

	for (i = 0; i < n; i++) {

		getchar();
		scanf("%s", cal);

		if (strcmp(cal, "AF") == 0) { // 프론트에 더한다.
			scanf("%d", &addNum);

			if (front == NULL) // 처음 노드 생성시
			{
				getnode(&front);
				front->ele = addNum;
			}
			else {
				add_front(front, addNum);
				front = front->prev; // 처음 위치 저장
			}
			
			if (rear == NULL) // 처음 노드 생성
				rear = front;

		}
		else if (strcmp(cal, "AR") == 0) { // 레어에 더한다.
			scanf("%d", &addNum);

			if (rear == NULL) // 처음 노드 생성
			{
				getnode(&rear);
				rear->ele = addNum;
			}
			else{
				add_rear(rear, addNum);
				rear = rear->next; // 최근 위치 저장
			}

			if (front == NULL) // 처음 노드 생성
				front = rear;

		}
		else if (strcmp(cal, "DF") == 0) { // 프론트에서 뺸다.
			
			if (front == rear) {
				printf("underflow");
				return 0;
			}

			p = front->next; // 프론트 위치 저장
			delete_front(front);

			if (p == NULL) // 다음 위치가 없음. 즉 마지막
				front = NULL;
			else
				front = p; // 새로운 프론트
			
			if (front == NULL) // 초기화 상태
				rear = NULL;
		}
		else if (strcmp(cal, "DR") == 0) { // 레어에서 뺀다.

			if (front == rear) {
				printf("underflow");
				return 0;
			}

			p = rear->prev; // 레어 위치 저장
			delete_rear(rear);
	
			if (p == NULL) // 레어의 다음 위치가 없음.
				rear = NULL;
			else
				rear = p; // 새로운 레어

			if (rear == NULL) // 초기화 상태
				front = NULL;
		}
		else if (strcmp(cal, "P") == 0)  // 출력한다.
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