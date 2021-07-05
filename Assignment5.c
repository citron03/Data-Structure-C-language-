#include <stdio.h>
#include <stdlib.h>

// ��Ʈ�� ������ �� ���� �ϳ��� ���ڸ� ǥ��
typedef struct tree {

	//�ڽ��� �ִ� 26���� Ʈ�� ���� �ʿ�
	struct tree* childrens[26];
	//���� �ܾ�� �빮�ڷθ� ����
	char data;

}tree;

int findWordInTree(tree* directory, char word);
void freeTree(tree* directory);

int main() {

	int N, i, j, find, searchNum, ii;
	char word[101];
	tree *directory = NULL, * p = NULL;

	directory = (tree*)malloc(sizeof(tree)); // Ʈ�� ��Ʈ

	for (i = 0; i < 26; i++) // �迭 �������� �ʱ�ȭ
		directory->childrens[i] = NULL;

	scanf("%d", &N); // �Էµ� ���� �ܾ� ����
	getchar(); // ����Ű ����

	for (i = 0; i < N; i++) {

		gets(word); // �ܾ� �Է�
		j = 0; // �ܾ��� ó������ ã�Ƴ�����

		p = directory; // ó������ Ȯ��
		while (word[j] >= 'A' && word[j] <= 'Z') { // �ܾ �ϳ��ϳ� ����
			
			find = findWordInTree(p, word[j]); // ���� �����ϴٸ� �� ��ġ�� �޴´�.
			if (p->childrens[find] == NULL) {  // ���ٸ� �� ��ҿ� �����Ѵ�.
				p->childrens[find] = (tree*)malloc(sizeof(tree)); // ������ �Ҵ�

				for (ii = 0; ii < 26; ii++)  // �迭 �������� �ʱ�ȭ
					p->childrens[find]->childrens[ii] = NULL; // ���� ���� ����� ������ �迭�� �ʱ�ȭ �Ѵ�.
				
				p->childrens[find]->data = word[j]; // �����͸� �����Ѵ�.
				p = p->childrens[find]; // ��η� �����Ѵ�.
			}
			else  // �����Ͱ� �̹� �����Ѵٸ�
				p = p->childrens[find]; // �� ��η� �����Ѵ�.

			j++; // ���� ���ڷ� �̵��Ѵ�.
		}

	}


	scanf("%d", &searchNum); // ã�� �ܾ��� ����
	getchar(); // ����Ű ����
	
	for (i = 0; i < searchNum; i++) { // �ݺ�

		gets(word); // �ܾ �Է¹޴´�.
		j = 0;
		p = directory; // �ʱ�ȭ


		while (word[j] >= 'A' && word[j] <= 'Z') { // �ܾ� ã��

			find = findWordInTree(p, word[j]); // ���� �����ϴٸ� �� ��ġ�� �޴´�.
			if (p->childrens[find] == NULL) { // ã�� ���ߴ�.
				printf("\n"); // ���� �ܾ�� �Ѿ��.
				break;
			}
			else {
				printf("%c", p->childrens[find]->data); // ���
				p = p->childrens[find]; // �׸��� �� ��η� �����Ѵ�.
			}
			j++; // ���� ���ڷ�
		}

	}


	// �޸� �Ҵ� ����
	freeTree(directory); // ���� ���� ����
	free(directory); // ��Ʈ ��� ����
	return 0;
}


int findWordInTree(tree* directory, char word) { // �����Ͱ� �̹� �����ϴ��� ã�´�.

	int i; 

	for (i = 0; i < 26; i++) {
		if (directory->childrens[i] == NULL) // ���� �����Ͽ��� �ÿ�
			return i; 
		else if (directory->childrens[i]->data == word) // �̹� �����ϸ�
			return i;
	}
}

void freeTree(tree* directory) {

	int i;

	for (i = 0; i < 26; i++) { // �ִ� 26�� �ݺ�
		if (directory->childrens[i] != NULL) { // �����Ͱ� �ִ� �����϶�
			freeTree(directory->childrens[i]); // ���
			free(directory->childrens[i]); // �����Ѵ�.
		}
		else
			break; // ���� ���޽� ����
	}

}