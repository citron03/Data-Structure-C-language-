#include<stdio.h>
#include<stdlib.h>



typedef struct node {

	char elem;
	struct node* prev;
	struct node* next;
}node;


void add(node *list, int r, char e);
void delete(node *list, int r);
char get(node *list, int r);
void print(node *list);
void linkedFree(node* p); // 모든 연결리스트 할당 해제
void get_node(node** phead); // 초기 노드 설정

int main() {

	node* head = NULL, * trailer = NULL;
	char input, e, getReturn;
	int n, i, r, length = 0;

	get_node(&head);
	get_node(&trailer);

	//head = (node*)malloc(sizeof(node));
	//trailer = (node*)malloc(sizeof(node));


	//head->prev = NULL;
	head->next = trailer; // 다음 노드의 주소
	//trailer->next = NULL;
	trailer->prev = head; // 이전 노드의 주소


	scanf("%d", &n);  // 연산의 개수
	for (i = 0; i < n; i++) {

		getchar();
		scanf("%c", &input);
		switch (input) {
		case 'A':
			scanf("%d %c", &r, &e);
			if (length + 1 < r || r < 0) // 불가능한 위치에 삽입
			{
				printf("invalid position\n");
				break;
			}
			add(head, r, e);
			length++;
			break;
		case 'D':
			scanf("%d", &r);
			if (length < r || r < 0) // 없는 위치의 데이터 삭제
			{
				printf("invalid position\n");
				break;
			}
			delete(head, r);
			length--;
			break;
		case 'G':
			scanf("%d", &r);
			getReturn = get(head, r);
			if (getReturn == '0' || r < 0) // 데이터가 없는 곳
				printf("invalid position\n");
			else
				printf("%c\n", getReturn);
			break;
		case 'P':
			print(head);
			break;
		}
	}


	linkedFree(head);
	return 0;
}


void add(node *list, int r, char e) {

	int i;
	node* find = list;
	for (i = 1; i < r; i++) // 삽입할 위치를 찾아간다.
		find = find->next;
	

	node* adding = (node*)malloc(sizeof(node));
	adding->elem = e;

	adding->next = find->next;
	find->next->prev = adding;
	adding->prev = find;
	find->next = adding;

}
void delete(node* list, int r) {

	int i;
	node* find = list;

	for (i = 0; i < r; i++) // 삭제할 위치를 찾아간다. 추가와는 달리 head를 0으로 보고 시작
		find = find->next;

	find->next->prev = find->prev;
	find->prev->next = find->next;

	free(find);
}
char get(node* list, int r) {


	int i;
	node* find = list;

	for (i = 0; i < r; i++) { // 추가와는 달리 head를 0으로 보고 시작
		find = find->next;
		if (find->next == NULL)
			return '0'; // invalid position 발생
	}

	return find->elem;
}
void print(node* list) {

	node* find = list;

	do {
		find = find->next;
		printf("%c", find->elem);

	} while (find->next->next != NULL); // 다음 노드가 트레일러노드이면 종료

	printf("\n");
}


void linkedFree(node* p) {

	if (p->next == NULL) // 재귀 종료
		free(p); // 트레일러 노드의 할당 해제
	else {
		linkedFree(p->next); // 재귀
		free(p);
	}
}

void get_node(node** phead) { // 초기화

	node* Node = (node*)malloc(sizeof(node));
	Node->next = NULL;
	Node->prev = NULL;
	
	*phead = Node; // phead에 Node가 가르키는 주소를 저장한다.
}