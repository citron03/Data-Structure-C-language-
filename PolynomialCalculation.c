#include<stdio.h>
#include<stdlib.h>

// coef: ���� ���
// exp : ���� ����
// next : ���� ��带 ����Ű�� ��ũ


typedef struct Node {

	int coef, exp;
	struct Node* next;

}Node;

void getnode(Node** pp);
void appendTerm(Node* k, int c, int e);
Node* addPoly(Node* x, Node* y);


int main() {

	Node* header1 = NULL, * header2 = NULL, * p, * resultHeader = NULL;
	int numHeader1, numHeader2, i, coef, exp;
	
	scanf("%d", &numHeader1); // ù��° ���׽��� ���� ������ �Է�

	getnode(&header1); // ��� ����
	p = header1; // ������

	for (i = 0; i < numHeader1; i++) // ���� ������ŭ ����� ������ �Է¹ް� ��� ����
	{
		scanf("%d %d", &coef, &exp); 
		appendTerm(p, coef, exp); // ��� ����, �� ����
		p = p->next; // ��������
	}

	// �ι�° ���׽�

	scanf("%d", &numHeader2); // �ι�° ���׽��� ���� ������ �Է�
	getnode(&header2); // ��� ����
	p = header2; // ������

	for (i = 0; i < numHeader2; i++) // ���� ������ŭ ����� ������ �Է¹ް� ��� ����
	{
		scanf("%d %d", &coef, &exp);
		appendTerm(p, coef, exp); // ��� ����, �� ����, ���� ��� ���� ���Ե� ��� ��ġ�� p->next
		p = p->next; // ��������
	}


	resultHeader = addPoly(header1, header2); // ����

	//��� ���
	p = resultHeader;
	while (p->next != NULL) {
		p = p->next;
		printf(" %d %d", p->coef, p->exp);
	}

	return 0;
}



void  getnode(Node** pp) {

	Node* q = (Node*)malloc(sizeof(Node));
	q->next = NULL;

	*pp = q; // ������ ����� �ּҸ� �����Ѵ�.
}

void appendTerm(Node* k, int c, int e) { // �� �߰�

	Node* p = NULL;

	getnode(&p); // ���� ��带 �����.
	p->coef = c;
	p->exp = e;
	p->next = NULL;
	k->next = p; // ������ ��带 ������ ����

}

Node* addPoly(Node* x, Node* y) {

	Node* i, * j, * result, * p;

	getnode(&result);
	p = result; // ���� ����Ų��.

	i = x->next; // ù��° ���
	j = y->next;


	while ((i != NULL) && (j != NULL)) {

		//printf("%d %d\n%d %d\n\n", i->coef, i->exp, j->coef, j->exp);

		if (i->exp > j->exp)
		{
			appendTerm(p, i->coef, i->exp); // ū ������ ���׽� �߰�
			i = i->next;
			p = p->next;

		}else if (i->exp < j->exp) {

			appendTerm(p, j->coef, j->exp);
			j = j->next; // ���Ϸ�
			p = p->next;

		}else // ������ ���� ���
		{
			if (i->coef == (j->coef * -1)) // 0�� �ɶ��� ����
			{
				i = i->next;
				j = j->next;
			}
			else {
				appendTerm(p, j->coef + i->coef, j->exp); // ���ϱ�
				i = i->next;
				j = j->next;
				p = p->next;
			}
		}

	}

	// ���� ���׽� �ִٸ� ���̱� 
	while (i != NULL) {
		appendTerm(p, i->coef, i->exp);
		p = p->next;
		i = i->next;
	}

	while (j != NULL) {
		appendTerm(p, j->coef, j->exp);
		p = p->next;
		j = j->next;
	}


	return result;
}