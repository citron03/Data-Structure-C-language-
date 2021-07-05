#include <stdio.h>
#include <stdlib.h>


void sumOfTriangle(int n, int* p);

int main() {

	int i, * p, n;
	p == NULL; // �ʱ�ȭ

	scanf("%d", &n);
	p = (int*)malloc(sizeof(int) * n); // �����Ҵ�
	if (p == NULL) // �����Ҵ��� �ȵǾ��� ���
		return -1;

	for (i = 0; i < n; i++)
		scanf("%d", &p[i]);

	sumOfTriangle(n, p); // �Լ��� �����Ѵ�.


	//free(p); // �Ҵ� �����Ѵ�.
	return 0;
}


void sumOfTriangle(int n, int* p) {

	int i;

	//���̽� ���̽�(base case)
	if (n == 1){
		printf(" %d", p[0]); // ������ �ϳ��� ���
		free(p); // ������ �迭 �Ҵ� ����
	}
	//��� ���̽�(recursion)
	else {
		int* pp = NULL; // ���ο� �迭�� ����
		pp = (int*)malloc(sizeof(int) * (n - 1)); // ũ�Ⱑ �ϳ� ���� �迭
		if (pp == NULL) // �Ҵ��� ����� ���� �ʾ��� ��츦 ���
			return -1;


		for (i = 0; i < n - 1; i++) // ���ο� �迭��
			pp[i] = p[i] + p[i + 1]; // �� ���� �� ���� ���� �����Ѵ�.
		sumOfTriangle(n - 1, pp); // ���


		for (i = 0; i < n; i++)
			printf(" %d", p[i]); // �ݺ��ؼ� ����Ѵ�.
		printf("\n"); // ���ü��� ���� �ٹٲ�

		free(p); // �� ���� �迭 �Ҵ� ����
	}

}