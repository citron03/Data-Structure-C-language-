#include <stdio.h>
#include <stdlib.h>


int combination(int n, int k); // 함수 원형 선언

int main() {

	// nCk의 계산
	int n, k;

	scanf("%d %d", &n, &k); // 입력

	printf("%d", combination(n, k)); // 출력


	return 0;
}



int combination(int n, int k) { // 함수 구현

	if (k == 0 || k == n) // 베이스 케이스(base case)
		return 1;
	else { // 재귀
		return combination(n - 1, k - 1) + combination(n - 1, k);

	}
}