#include<stdio.h>
#include<stdlib.h>


typedef struct Node {

	struct Node* next;
	int element;

}Node;


void freeNode(Node* p);
void getNode(Node** p, int Num);
Node* Union(Node* A, Node* B);
Node* intersect(Node* A, Node* B);


//모든 집합은 헤더(header) 노드가 추가된 단일연결리스트 형태로 구축되어야 한다
int main() {
	Node* headerA = NULL, * headerB = NULL, 
		* headerUnion = NULL, * headerIntersect = NULL,
		* p;
	int sizeA, sizeB, i, Num;
	//모든 집합은 오름차순 양의 정수로 저장 및 출력되어야 한다

	scanf("%d", &sizeA);

	// 헤더 노드
	headerA = (Node*)malloc(sizeof(Node));
	headerA->next = NULL;
	headerA->element = NULL;

	for (i = 0, p = headerA; i < sizeA; i++) {
		scanf("%d", &Num);
		getNode(&(p->next), Num); // 새 노드 생성
		p = p->next; // 다음으로
	}
	



	scanf("%d", &sizeB);

	// 헤더 노드
	headerB = (Node*)malloc(sizeof(Node));
	headerB->next = NULL;
	headerB->element = NULL;

	for (i = 0, p = headerB; i < sizeB; i++) {
		scanf("%d", &Num);
		getNode(&(p->next), Num); // 새 노드 생성
		p = p->next; // 다음으로
	}

	//합집합
	headerUnion = Union(headerA->next, headerB->next); // 헤더 다음 노드 부터
	// 출력
	for (p = headerUnion->next; p != NULL; p = p->next)
		printf(" %d", p->element);

	if (headerUnion->next == NULL) // 합집합이 공집합일때
		printf(" 0");

	printf("\n"); // 줄바꿈

	//교집합
	headerIntersect = intersect(headerA->next, headerB->next); // 헤더 다음 노드 부터
	//출력
	for (p = headerIntersect->next; p != NULL; p = p->next)
		printf(" %d", p->element);

	if (headerIntersect->next == NULL) // 교집합이 공집합일때
		printf(" 0");

	freeNode(headerA);
	freeNode(headerB);
	freeNode(headerUnion);
	freeNode(headerIntersect);
	

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

Node* Union(Node* A, Node* B){ // 합집합

	Node* returnNode = NULL, * nodeA = A, * nodeB = B, * p = NULL;
	returnNode = (Node*)malloc(sizeof(Node));
	returnNode->next = NULL;
	p = returnNode;

	// 작은 값 먼저
	while (nodeA != NULL && nodeB != NULL) {

		if (nodeA->element > nodeB->element) {

			getNode(&(p->next), nodeB->element); // 노드 만들기
			p = p->next; // 다음으로
			nodeB = nodeB->next;
		}
		else if (nodeA->element < nodeB->element) {
			
			getNode(&(p->next), nodeA->element); // 노드 만들기
			p = p->next; // 
			nodeA = nodeA->next;

		}
		else { // 같은 값일때 아무 값이나 넣어도 무관

			getNode(&(p->next), nodeB->element); // 노드 만들기
			p = p->next; // 다음으로
			nodeA = nodeA->next;
			nodeB = nodeB->next;
		}

	}
	
	// 나머지가 있다면 붙이기

	while (nodeA != NULL) {

		getNode(&(p->next), nodeA->element); // 노드 만들기
		p = p->next; // 
		nodeA = nodeA->next;

	}

	while (nodeB != NULL) {

		getNode(&(p->next), nodeB->element); // 노드 만들기
		p = p->next; // 다음으로
		nodeB = nodeB->next;

	}

	return returnNode;
}


Node* intersect(Node* A, Node* B) { // 교집합

	Node* returnNode = NULL, * nodeA = A, * nodeB = B, * p = NULL;
	returnNode = (Node*)malloc(sizeof(Node));
	returnNode->next = NULL;
	p = returnNode;

	while (nodeA != NULL && nodeB != NULL) {

		if (nodeA->element > nodeB->element) 
			nodeB = nodeB->next;
		else if (nodeA->element < nodeB->element) 
			nodeA = nodeA->next;
		else { // 같은 값일때만 노드에 추가

			getNode(&(p->next), nodeB->element); // 노드 만들기
			p = p->next; // 다음으로
			nodeA = nodeA->next;
			nodeB = nodeB->next;
		}

	}

	return returnNode;

}