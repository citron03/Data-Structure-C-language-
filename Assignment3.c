#include<stdio.h>
#include<stdlib.h>


//����� Ʈ���Ϸ��� ������ ���� ���� ����Ʈ

typedef struct Node {

	int element; // ��������
	struct Node* next; // ���� ������
	struct Node* prev; // ���� ������

}Node;

// �׷��� ��� ���� ���� ����Ʈ
typedef struct groupNode {

	char groupName; // �׷��� �̸�
	struct groupNode* next; // ���� ������
	Node* header; // �׷��� ��� ���
	Node* trailer; // �׷��� Ʈ���Ϸ� ���
	
}groupNode;

// Create_group(g) : �׷� g�� �����Ѵ�.
void Create_group(groupNode* headerGroup,char g);

// Destory_group(g) : �׷� g�� �ı��Ѵ�.
void Destory_group(groupNode* headerGroup,char g);

// Add_element(g, e) : �׷� g�� ���� e�� �߰��Ѵ�.
void Add_element(groupNode* headerGroup,char g, int e);


// Remove_element(g, e) : �׷� g�� ���� e�� �����Ѵ�.
void Remove_element(groupNode* headerGroup,char g, int e);

// Show_all() : �����ϴ� ��� �׷��� ���ҵ��� �׷캰�� ���
void Show_all(groupNode* headerGroup);


int main() {

	// �׷� ���Ḯ��Ʈ�� ��� ���
	groupNode* headerGroup = NULL, * p, * q;
	int numCalculate, i, element;
	char charCalculate, groupName, tmp;

	// �ʱ� �׷��� ��� ��� ����
	headerGroup = (groupNode*)malloc(sizeof(groupNode));
	headerGroup->header = NULL; // �׷� ������
	headerGroup->trailer = NULL; // �׷� ������
	headerGroup->next = NULL;


	scanf("%d", &numCalculate); // ���� ������ �Է��Ѵ�.
	for (i = 0; i < numCalculate; i++) { // �ݺ�

		scanf("%c", &tmp); // ��������
		scanf("%c", &charCalculate); // ���� �Է�

		//printf("$ %c $\n", charCalculate);

		switch (charCalculate) {
		case 'C': // �׷� ����
			scanf("%c", &tmp); // ��������
			scanf("%c", &groupName); // �׷� �̸� �Է�
			Create_group(headerGroup, groupName);
			break;
		case 'D': // �׷� ����
			scanf("%c", &tmp); // ��������
			scanf("%c", &groupName); // �׷� �̸� �Է�
			Destory_group(headerGroup, groupName);
			break;

		case 'A': // ���� �߰� 
			scanf("%c", &tmp); // ��������
			scanf("%c %d", &groupName,&element); // �׷� �̸��� ���� �Է�
			Add_element(headerGroup, groupName, element);
			break;

		case'R': // ���� ����
			scanf("%c", &tmp); // ��������
			scanf("%c %d", &groupName, &element); // �׷� �̸��� ���� �Է�
			Remove_element(headerGroup, groupName, element);
			break;

		case 'S': // ���
			Show_all(headerGroup);
			break;
		}

	}

	////// �׷�� element ��� free //////

	p = headerGroup->next; // ��� ������ ��ġ (�ʱ� ��ġ)

	free(headerGroup); // �׷� ��� ���� ������ ����� Ʈ���Ϸ��� ������ ���� ����
	Node* pp , * qq; // ������ ���Ḯ��Ʈ ����

	while (p != NULL) { // �ݺ����� ����	
		q = p; // ������ ��ġ
		p = p->next; // ���� ������ �׷��� �̸� �����Ѵ�.

		pp = q->header; // �׷��� ���� ���Ḯ��Ʈ ����
	
		while (1) { // �ݺ����� ���� ���Ḯ��Ʈ ����
			qq = pp; // ������ ��ġ
			pp = pp->next; // ���� ������ ��� ���� �̸� ����

			free(qq); // ����
			if (pp == NULL) // Ʈ���Ϸ� ���, next�� NULL�� ��忡 ������ ��
				break;
		}

		free(q); // ����
	}


	return 0;
}



void Create_group(groupNode* headerGroup, char g) {
	//�׷� g�� �̹� �����ϴ� ���, �ƹ� �۾��� ���� ����
	groupNode* p = headerGroup->next; // ù��° ���� ��ġ
	int S = 0; // �̹� �����ϸ� 1�� �ٲ��ش�.

	while (p != NULL) {
		if (p->groupName == g) {
			S = 1; // �̹� �׷� ����
			break;
		}
		p = p->next; // ��������
	}

	if (S == 0) {
		p = headerGroup; // ��ġ �ʱ�ȭ

		//�׷� �̸��� ������������ ����
		while (1) { // �߰��� ��ġ ã��

			if (p->next == NULL) { // ������ ��ġ�� �����ϸ� ���� �߰�
				p->next = (groupNode*)malloc(sizeof(groupNode)); // �׷� ����

				// ���� ��带 �����.
				p->next->header = (Node*)malloc(sizeof(Node));
				p->next->trailer = (Node*)malloc(sizeof(Node));
				// ����
				p->next->header->next = p->next->trailer;
				p->next->header->prev = NULL;
				p->next->trailer->next = NULL;
				p->next->trailer->prev = p->next->header;

				// ������ �׷� ����
				p->next->next = NULL;
				p->next->groupName = g;

				break; // ��
			}
			else if (p->next->groupName > g) { // �ڽź��� ū �׷��� �̸��� ����

				groupNode* newGroup = (groupNode*)malloc(sizeof(groupNode)); // �� �׷� ����
				// ����
				newGroup->next = p->next; // ����
				p->next = newGroup; // ����
				// ������ �׷� ����
				newGroup->groupName = g;

				// ���� ��带 �����.
				newGroup->header = (Node*)malloc(sizeof(Node));
				newGroup->trailer = (Node*)malloc(sizeof(Node));
				// ����
				newGroup->header->next = p->next->trailer;
				newGroup->header->prev = NULL;
				newGroup->trailer->next = NULL;
				newGroup->trailer->prev = p->next->header;

				break; // ��
			}



			p = p->next; // ��������
		}
		
	}
	
	


}

void Destory_group(groupNode* headerGroup, char g) {
	// �׷� g�� �������� ���� ���, �ƹ� �۾��� ���� ����

	groupNode* p = headerGroup->next; // ù��° ���� ��ġ
	groupNode* q = headerGroup; // ������ ��ġ ���� ��� ��ġ
	while (p != NULL) {

		if (p->groupName == g) { // ������ �׷� �߽߰�
			q->next = p->next; // ������ �׷��� �߽����� ���� ����
			free(p); // ����
			break;
		}
		else if (p->groupName > g) // �������� �̱� ������
			break;
		q = p;
		p = p->next; // ��������
	}


}


void Add_element(groupNode* headerGroup, char g, int e) {

	//�׷� g�� �������� ���� ���, �ƹ� �۾��� ���� ����
	//�׷� g�� ���� e�� �̹� �����ϴ� ���, �ƹ� �۾��� ���� ����
	//(��, ��ȣ�� ���� ���Ұ� �־ �׷��� �ٸ��� �ٸ� ���ҷ� �����Կ� ����.���� ���, �׷� A�� ���� 10�� Add(B, 10) ���꿡�� �ƹ� ������ ��ġ�� ����.) 
	//���ҵ��� ������������ ����Ǿ� �־�� ��.����, Add ���� �� ���Ұ� ���Ե� ��ġ�� ������ ��ȣ�� ���ؼ� ã�ƾ� ��.
	groupNode* p = headerGroup->next; // ù��° ���� ��ġ
	Node* addFind;

	while (p != NULL) { // �׷� ã��

		if (p->groupName == g) { // ���Ҹ� �߰��� �׷��� �߰�
			addFind = p->header; // ������ ��� ���

			while (1) { // ���Ҹ� ���� ��ġ�� ã��
				addFind = addFind->next; // ���� ����
				if (addFind->next == NULL) { // Ʈ���Ϸ� ��忡 ����

					Node* addNewElement = (Node*)malloc(sizeof(Node)); // ��� ����
					addNewElement->next = addFind->prev->next;
					addNewElement->prev = addFind->prev;
					//����
					addFind->prev->next = addNewElement;
					addFind->prev = addNewElement;

					addNewElement->element = e; // ���� ����

					p = NULL; // �׷� ã�� ��������
					break; // ��
				}
				else if (addFind->element > e) { // ������ ��ġ�� ã��

					Node* addNewElement = (Node*)malloc(sizeof(Node)); // ��� ����
					addNewElement->next = addFind->prev->next;
					addNewElement->prev = addFind->prev;
					//����
					addFind->prev->next = addNewElement;
					addFind->prev = addNewElement;

					addNewElement->element = e; // ���� ����

					p = NULL; // �׷� ã�� ��������
					break; // ��
				}
				else if (addFind->element == e) { // �̹� ����
					p = NULL; // �׷� ã�� ��������
					break; // ��
				}
			}
		}
		else if (p->groupName > g) // �������� �̱� ������
			break;

		if(p != NULL) // ���� �ƴҶ�
			p = p->next; // ��������
	}

}


void Remove_element(groupNode* headerGroup, char g, int e) {

	//�ش� ���Ұ� ���� ���, �ƹ� �۾��� ���� ����
	//�� ������ ����� �׷� g�� ���Ұ� �ϳ��� ���, �׷� ��ü�� ����(��, �ı����� ����)

	groupNode* p = headerGroup->next; // ù��° ���� ��ġ
	Node* addFind;

	while (p != NULL) { // �׷� ã��

		if (p->groupName == g) { // ���Ҹ� ������ �׷��� �߰�
			addFind = p->header->next; // ù��° ������ ��ġ

			while (addFind != NULL) { //������ ���� ã��

				if (addFind->element == e) { // ã��

					// ���� ���� ����
					addFind->prev->next = addFind->next;
					addFind->next->prev = addFind->prev;

					free(addFind); // ����
					p = NULL; // �׷� ã�� ��������
					break; // ��
				}

				addFind = addFind->next; // ���� ����
			}
		}
		if(p != NULL) // ���� �ƴҶ�
			p = p->next; // ���� �׷�
	}

}


void Show_all(groupNode* headerGroup) {

	// ��� �׷�, ���Ҹ� ���
	groupNode* p = headerGroup->next; // ù ���
	Node* q;

	while(p != NULL) { // ���

		printf("%c:", p->groupName); // �׷� �̸��� ����Ѵ�.
		q = p->header->next; // ������ ������ ���� ���, ù��° ���� �ִ� ���
		while (q->next != NULL) { // next�� NULL�̸� Ʈ���Ϸ� ���. Ʈ���Ϸ� ��� ���޽� ����
			// ��� ���� ���
			printf(" %d", q->element);
			q = q->next; // ��������
		}

		p = p->next; // ���� �׷�����
		printf("\n"); // �ٹٲ�
	}

}
