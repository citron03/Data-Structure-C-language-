#include<stdio.h>
#include<stdlib.h>


typedef struct Node {

	struct Node* next;
	int element;

}Node;


void freeNode(Node* p);
void getNode(Node** p, int Num);
int subset(Node* ap, Node* bp);

//집합은 헤더 노드가 없는 단일연결리스트(singly-inked list) 형태로 구축되어야 한다.
int main() {

	Node* setA = NULL, * setB = NULL, * p = NULL, *A = NULL, * B = NULL;
	int sizeA, sizeB, i, Num;
	
	//입력 A
	scanf("%d", &sizeA);
	
	if (sizeA != 0) { // 공집합이 아닐경우

		// 첫 노드 생성
		scanf("%d", &Num);
		getNode(&setA, Num); // 노드를 만듦
		A = setA; // 처음 위치 포인터

		for (i = 0; i < sizeA - 1; i++) {
			scanf("%d", &Num);
			getNode(&(setA->next), Num); // 현재 NULL인 next에 노드를 만든다.
			setA = setA->next; // 만들어진 노드를 가르킨다. (마지막 순서의 노드를 가르킨다.)
		}
	}

	// 입력 B
	scanf("%d", &sizeB);
	if (sizeB != 0) { // 공집합이 아닐경우

	// 첫 노드 생성
		scanf("%d", &Num);
		getNode(&setB, Num); // 노드를 만듦
		B = setB; // 처음 위치 포인터

		for (i = 0; i < sizeB - 1; i++) {
			scanf("%d", &Num);
			getNode(&(setB->next), Num); // 노드를 만듦
			setB = setB->next; // 다음으로
		}
	}

	// 집합은 오름차순 양의 정수로 저장 및 출력되어야 한다
	//  공집합은 공집합을 포함한 모든 집합의 부분집합이다

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
		q = pp; // 해제할 노드
		pp = pp->next; // 다음 노드로
		free(q); // 해제
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

	int subSet = 0; // 초기 상태는 subset, 만약 아니면 1.
	int Small = -1, Acount = 0, A = 0; // A는 ap의 길이
	Node* setA = ap, * setB = bp;
	// A ⊂ B이면 0을 출력하고, 
	// 그렇지 않으면 집합 B에 속하지 않은 집합 A의 가장 작은 원소를 표준 출력한다

	while (setA != NULL && setB != NULL) {

		//printf("%d %d \n", setA->element, setB->element);

		if (setA->element > setB->element) 
			setB = setB->next;
		else if (setA->element < setB->element){ // A가 더 클때는 A와 B의 공통값이 아닌것
			if (Small == -1) // 가장 작은 버려지는 값 저장
				Small = setA->element; // 오름차순이기에 버려지는 첫번쨰 값이 제일 작다.
			setA = setA->next;
			A++; // A의 길이를 센다
		}
		else { // 같을 때
			setA = setA->next;
			setB = setB->next;
			Acount++;
			A++; // A의 길이를 센다
		}
	}

	while (setA != NULL) {
		if(Small == -1)
			Small = setA->element;
		setA = setA->next;
		A++; // A의 길이를 센다
	}


	// A ⊂ B일때
	if (Acount == A)
		return subSet; // 0을 리턴한다.
	else // 아닐때
		return Small;
}