#include <stdio.h>
#include <stdlib.h>

void PRINT(int* Q, int N);

int main() {

	int front = 0, rear = 0, * q = NULL, Qnum, n, i, insertNum;
	char cal;

	scanf("%d %d", &Qnum, &n);

	q = (int*)malloc(sizeof(int)*Qnum);

	for (i = 0; i < Qnum; i++)
		q[i] = 0; // �迭 �ʱ�ȭ

	for (i = 0; i < n; i++) { // n���� ��� ����

		getchar();
		scanf("%c", &cal);

		switch (cal)
		{
		case 'I':
			scanf("%d", &insertNum);
			if ((rear + 1) % Qnum == front ) //��ȭ����
			{
				printf("overflow"); // �����÷ο� ��� �� ��� �� ��� �׸��� ����
				PRINT(q, Qnum);
				return 0;
			}
			else {
				rear = (rear + 1) % Qnum;
				q[rear] = insertNum;
				break;
			}

		case 'D':
			if (rear  == front)  // �� ����
			{
				printf("underflow");
				return 0; // ����
			}
			else {
				front = (front + 1) % Qnum;
				q[front] = 0;
				break;
			}

		case 'P':
			PRINT(q, Qnum);
			break;
		}


	}


	return 0;
}



void PRINT(int* Q, int N) {

	int i;


	for (i = 0; i < N; i++)
		printf(" %d", Q[i]);
	printf("\n");
}