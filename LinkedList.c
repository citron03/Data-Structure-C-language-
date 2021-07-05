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
void linkedFree(node* p); // ��� ���Ḯ��Ʈ �Ҵ� ����
void get_node(node** phead); // �ʱ� ��� ����

int main() {

	node* head = NULL, * trailer = NULL;
	char input, e, getReturn;
	int n, i, r, length = 0;

	get_node(&head);
	get_node(&trailer);

	//head = (node*)malloc(sizeof(node));
	//trailer = (node*)malloc(sizeof(node));


	//head->prev = NULL;
	head->next = trailer; // ���� ����� �ּ�
	//trailer->next = NULL;
	trailer->prev = head; // ���� ����� �ּ�


	scanf("%d", &n);  // ������ ����
	for (i = 0; i < n; i++) {

		getchar();
		scanf("%c", &input);
		switch (input) {
		case 'A':
			scanf("%d %c", &r, &e);
			if (length + 1 < r || r < 0) // �Ұ����� ��ġ�� ����
			{
				printf("invalid position\n");
				break;
			}
			add(head, r, e);
			length++;
			break;
		case 'D':
			scanf("%d", &r);
			if (length < r || r < 0) // ���� ��ġ�� ������ ����
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
			if (getReturn == '0' || r < 0) // �����Ͱ� ���� ��
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
	for (i = 1; i < r; i++) // ������ ��ġ�� ã�ư���.
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

	for (i = 0; i < r; i++) // ������ ��ġ�� ã�ư���. �߰��ʹ� �޸� head�� 0���� ���� ����
		find = find->next;

	find->next->prev = find->prev;
	find->prev->next = find->next;

	free(find);
}
char get(node* list, int r) {


	int i;
	node* find = list;

	for (i = 0; i < r; i++) { // �߰��ʹ� �޸� head�� 0���� ���� ����
		find = find->next;
		if (find->next == NULL)
			return '0'; // invalid position �߻�
	}

	return find->elem;
}
void print(node* list) {

	node* find = list;

	do {
		find = find->next;
		printf("%c", find->elem);

	} while (find->next->next != NULL); // ���� ��尡 Ʈ���Ϸ�����̸� ����

	printf("\n");
}


void linkedFree(node* p) {

	if (p->next == NULL) // ��� ����
		free(p); // Ʈ���Ϸ� ����� �Ҵ� ����
	else {
		linkedFree(p->next); // ���
		free(p);
	}
}

void get_node(node** phead) { // �ʱ�ȭ

	node* Node = (node*)malloc(sizeof(node));
	Node->next = NULL;
	Node->prev = NULL;
	
	*phead = Node; // phead�� Node�� ����Ű�� �ּҸ� �����Ѵ�.
}