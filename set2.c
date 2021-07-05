#include<stdio.h>
#include<stdlib.h>


typedef struct Node {

	struct Node* next;
	int element;

}Node;


void freeNode(Node* p);
void getNode(Node** p, int Num);
Node* Union(Node* A, Node* B);
Node* intersect(Node* A, Node* B);


//��� ������ ���(header) ��尡 �߰��� ���Ͽ��Ḯ��Ʈ ���·� ����Ǿ�� �Ѵ�
int main() {
	Node* headerA = NULL, * headerB = NULL, 
		* headerUnion = NULL, * headerIntersect = NULL,
		* p;
	int sizeA, sizeB, i, Num;
	//��� ������ �������� ���� ������ ���� �� ��µǾ�� �Ѵ�

	scanf("%d", &sizeA);

	// ��� ���
	headerA = (Node*)malloc(sizeof(Node));
	headerA->next = NULL;
	headerA->element = NULL;

	for (i = 0, p = headerA; i < sizeA; i++) {
		scanf("%d", &Num);
		getNode(&(p->next), Num); // �� ��� ����
		p = p->next; // ��������
	}
	



	scanf("%d", &sizeB);

	// ��� ���
	headerB = (Node*)malloc(sizeof(Node));
	headerB->next = NULL;
	headerB->element = NULL;

	for (i = 0, p = headerB; i < sizeB; i++) {
		scanf("%d", &Num);
		getNode(&(p->next), Num); // �� ��� ����
		p = p->next; // ��������
	}

	//������
	headerUnion = Union(headerA->next, headerB->next); // ��� ���� ��� ����
	// ���
	for (p = headerUnion->next; p != NULL; p = p->next)
		printf(" %d", p->element);

	if (headerUnion->next == NULL) // �������� �������϶�
		printf(" 0");

	printf("\n"); // �ٹٲ�

	//������
	headerIntersect = intersect(headerA->next, headerB->next); // ��� ���� ��� ����
	//���
	for (p = headerIntersect->next; p != NULL; p = p->next)
		printf(" %d", p->element);

	if (headerIntersect->next == NULL) // �������� �������϶�
		printf(" 0");

	freeNode(headerA);
	freeNode(headerB);
	freeNode(headerUnion);
	freeNode(headerIntersect);
	

	return 0;
}




void freeNode(Node* p) {

	Node* q = NULL, * pp = p;

	while (pp != NULL) {
		q = pp; // ������ ���
		pp = pp->next; // ���� ����
		free(q); // ����
	}
}



void getNode(Node** p, int Num) {

	Node* pp = NULL;

	pp = (Node*)malloc(sizeof(Node));
	pp->element = Num;
	pp->next = NULL;
	*p = pp;
}

Node* Union(Node* A, Node* B){ // ������

	Node* returnNode = NULL, * nodeA = A, * nodeB = B, * p = NULL;
	returnNode = (Node*)malloc(sizeof(Node));
	returnNode->next = NULL;
	p = returnNode;

	// ���� �� ����
	while (nodeA != NULL && nodeB != NULL) {

		if (nodeA->element > nodeB->element) {

			getNode(&(p->next), nodeB->element); // ��� �����
			p = p->next; // ��������
			nodeB = nodeB->next;
		}
		else if (nodeA->element < nodeB->element) {
			
			getNode(&(p->next), nodeA->element); // ��� �����
			p = p->next; // 
			nodeA = nodeA->next;

		}
		else { // ���� ���϶� �ƹ� ���̳� �־ ����

			getNode(&(p->next), nodeB->element); // ��� �����
			p = p->next; // ��������
			nodeA = nodeA->next;
			nodeB = nodeB->next;
		}

	}
	
	// �������� �ִٸ� ���̱�

	while (nodeA != NULL) {

		getNode(&(p->next), nodeA->element); // ��� �����
		p = p->next; // 
		nodeA = nodeA->next;

	}

	while (nodeB != NULL) {

		getNode(&(p->next), nodeB->element); // ��� �����
		p = p->next; // ��������
		nodeB = nodeB->next;

	}

	return returnNode;
}


Node* intersect(Node* A, Node* B) { // ������

	Node* returnNode = NULL, * nodeA = A, * nodeB = B, * p = NULL;
	returnNode = (Node*)malloc(sizeof(Node));
	returnNode->next = NULL;
	p = returnNode;

	while (nodeA != NULL && nodeB != NULL) {

		if (nodeA->element > nodeB->element) 
			nodeB = nodeB->next;
		else if (nodeA->element < nodeB->element) 
			nodeA = nodeA->next;
		else { // ���� ���϶��� ��忡 �߰�

			getNode(&(p->next), nodeB->element); // ��� �����
			p = p->next; // ��������
			nodeA = nodeA->next;
			nodeB = nodeB->next;
		}

	}

	return returnNode;

}