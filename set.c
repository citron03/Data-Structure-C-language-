#include<stdio.h>
#include<stdlib.h>


typedef struct Node {

	struct Node* next;
	int element;

}Node;


void freeNode(Node* p);
void getNode(Node** p, int Num);
int subset(Node* ap, Node* bp);

//������ ��� ��尡 ���� ���Ͽ��Ḯ��Ʈ(singly-inked list) ���·� ����Ǿ�� �Ѵ�.
int main() {

	Node* setA = NULL, * setB = NULL, * p = NULL, *A = NULL, * B = NULL;
	int sizeA, sizeB, i, Num;
	
	//�Է� A
	scanf("%d", &sizeA);
	
	if (sizeA != 0) { // �������� �ƴҰ��

		// ù ��� ����
		scanf("%d", &Num);
		getNode(&setA, Num); // ��带 ����
		A = setA; // ó�� ��ġ ������

		for (i = 0; i < sizeA - 1; i++) {
			scanf("%d", &Num);
			getNode(&(setA->next), Num); // ���� NULL�� next�� ��带 �����.
			setA = setA->next; // ������� ��带 ����Ų��. (������ ������ ��带 ����Ų��.)
		}
	}

	// �Է� B
	scanf("%d", &sizeB);
	if (sizeB != 0) { // �������� �ƴҰ��

	// ù ��� ����
		scanf("%d", &Num);
		getNode(&setB, Num); // ��带 ����
		B = setB; // ó�� ��ġ ������

		for (i = 0; i < sizeB - 1; i++) {
			scanf("%d", &Num);
			getNode(&(setB->next), Num); // ��带 ����
			setB = setB->next; // ��������
		}
	}

	// ������ �������� ���� ������ ���� �� ��µǾ�� �Ѵ�
	//  �������� �������� ������ ��� ������ �κ������̴�

	printf("%d", subset(A, B));


	if(A != NULL)
		freeNode(A);
	if(B != NULL)
		freeNode(B);

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


int subset(Node* ap, Node* bp) {

	int subSet = 0; // �ʱ� ���´� subset, ���� �ƴϸ� 1.
	int Small = -1, Acount = 0, A = 0; // A�� ap�� ����
	Node* setA = ap, * setB = bp;
	// A �� B�̸� 0�� ����ϰ�, 
	// �׷��� ������ ���� B�� ������ ���� ���� A�� ���� ���� ���Ҹ� ǥ�� ����Ѵ�

	while (setA != NULL && setB != NULL) {

		//printf("%d %d \n", setA->element, setB->element);

		if (setA->element > setB->element) 
			setB = setB->next;
		else if (setA->element < setB->element){ // A�� �� Ŭ���� A�� B�� ���밪�� �ƴѰ�
			if (Small == -1) // ���� ���� �������� �� ����
				Small = setA->element; // ���������̱⿡ �������� ù���� ���� ���� �۴�.
			setA = setA->next;
			A++; // A�� ���̸� ����
		}
		else { // ���� ��
			setA = setA->next;
			setB = setB->next;
			Acount++;
			A++; // A�� ���̸� ����
		}
	}

	while (setA != NULL) {
		if(Small == -1)
			Small = setA->element;
		setA = setA->next;
		A++; // A�� ���̸� ����
	}


	// A �� B�϶�
	if (Acount == A)
		return subSet; // 0�� �����Ѵ�.
	else // �ƴҶ�
		return Small;
}