#include <stdio.h>
#include <stdlib.h>


int combination(int n, int k); // �Լ� ���� ����

int main() {

	// nCk�� ���
	int n, k;

	scanf("%d %d", &n, &k); // �Է�

	printf("%d", combination(n, k)); // ���


	return 0;
}



int combination(int n, int k) { // �Լ� ����

	if (k == 0 || k == n) // ���̽� ���̽�(base case)
		return 1;
	else { // ���
		return combination(n - 1, k - 1) + combination(n - 1, k);

	}
}