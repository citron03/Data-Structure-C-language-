#include<stdio.h>


void flip(int* p, int a, int b);

int main() {

	int Sequence[100], i, length, changeLen, leftChange, rightChange, tmp, j, l;
	scanf("%d", &length);

	for (i = 0; i < length; i++)
		scanf("%d", &Sequence[i]);

	scanf("%d", &changeLen);



	for (i = 0; i < changeLen; i++) {
		scanf("%d %d", &leftChange, &rightChange);
		flip(Sequence, leftChange, rightChange); // 바꾸기 함수로 바꿈
	}



	for (i = 0; i < length; i++)
		printf(" %d", Sequence[i]);

	return 0;
}


void flip(int* p, int a, int b) { // 바꾸기

	int i, tmp;

	for (i = a; i <=  a + (b - a)/2 ; i++) {
		tmp = p[i];
		p[i] = p[b - (i - a)];
		p[b - (i - a)] = tmp;
	}


}