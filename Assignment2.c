#include <stdio.h>
#include <stdlib.h>


void sumOfTriangle(int n, int* p);

int main() {

	int i, * p, n;
	p == NULL; // 초기화

	scanf("%d", &n);
	p = (int*)malloc(sizeof(int) * n); // 동적할당
	if (p == NULL) // 동적할당이 안되었을 경우
		return -1;

	for (i = 0; i < n; i++)
		scanf("%d", &p[i]);

	sumOfTriangle(n, p); // 함수를 실행한다.


	//free(p); // 할당 해제한다.
	return 0;
}


void sumOfTriangle(int n, int* p) {

	int i;

	//베이스 케이스(base case)
	if (n == 1){
		printf(" %d", p[0]); // 마지막 하나의 출력
		free(p); // 마지막 배열 할당 해제
	}
	//재귀 케이스(recursion)
	else {
		int* pp = NULL; // 새로운 배열을 만듦
		pp = (int*)malloc(sizeof(int) * (n - 1)); // 크기가 하나 작은 배열
		if (pp == NULL) // 할당이 제대로 되지 않았을 경우를 고려
			return -1;


		for (i = 0; i < n - 1; i++) // 새로운 배열에
			pp[i] = p[i] + p[i + 1]; // 양 옆의 두 개의 값을 대입한다.
		sumOfTriangle(n - 1, pp); // 재귀


		for (i = 0; i < n; i++)
			printf(" %d", p[i]); // 반복해서 출력한다.
		printf("\n"); // 가시성을 위한 줄바꿈

		free(p); // 다 사용된 배열 할당 해제
	}

}