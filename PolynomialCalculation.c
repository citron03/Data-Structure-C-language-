#include<stdio.h>
#include<stdlib.h>

// coef: 항의 계수
// exp : 항의 차수
// next : 다음 노드를 가리키는 링크


typedef struct Node {

	int coef, exp;
	struct Node* next;

}Node;

void getnode(Node** pp);
void appendTerm(Node* k, int c, int e);
Node* addPoly(Node* x, Node* y);


int main() {

	Node* header1 = NULL, * header2 = NULL, * p, * resultHeader = NULL;
	int numHeader1, numHeader2, i, coef, exp;
	
	scanf("%d", &numHeader1); // 첫번째 다항식의 항의 개수를 입력

	getnode(&header1); // 노드 생성
	p = header1; // 헤더노드

	for (i = 0; i < numHeader1; i++) // 항의 개수만큼 계수와 차수를 입력받고 노드 생성
	{
		scanf("%d %d", &coef, &exp); 
		appendTerm(p, coef, exp); // 노드 생성, 값 주입
		p = p->next; // 다음으로
	}

	// 두번째 다항식

	scanf("%d", &numHeader2); // 두번째 다항식의 항의 개수를 입력
	getnode(&header2); // 노드 생성
	p = header2; // 헤더노드

	for (i = 0; i < numHeader2; i++) // 항의 개수만큼 계수와 차수를 입력받고 노드 생성
	{
		scanf("%d %d", &coef, &exp);
		appendTerm(p, coef, exp); // 노드 생성, 값 주입, 실제 노드 값이 주입된 노드 위치는 p->next
		p = p->next; // 다음으로
	}


	resultHeader = addPoly(header1, header2); // 덧셈

	//결과 출력
	p = resultHeader;
	while (p->next != NULL) {
		p = p->next;
		printf(" %d %d", p->coef, p->exp);
	}

	return 0;
}



void  getnode(Node** pp) {

	Node* q = (Node*)malloc(sizeof(Node));
	q->next = NULL;

	*pp = q; // 생성된 노드의 주소를 저장한다.
}

void appendTerm(Node* k, int c, int e) { // 항 추가

	Node* p = NULL;

	getnode(&p); // 먼저 노드를 만든다.
	p->coef = c;
	p->exp = e;
	p->next = NULL;
	k->next = p; // 생성된 노드를 다음에 저장

}

Node* addPoly(Node* x, Node* y) {

	Node* i, * j, * result, * p;

	getnode(&result);
	p = result; // 끝을 가리킨다.

	i = x->next; // 첫번째 노드
	j = y->next;


	while ((i != NULL) && (j != NULL)) {

		//printf("%d %d\n%d %d\n\n", i->coef, i->exp, j->coef, j->exp);

		if (i->exp > j->exp)
		{
			appendTerm(p, i->coef, i->exp); // 큰 차수의 다항식 추가
			i = i->next;
			p = p->next;

		}else if (i->exp < j->exp) {

			appendTerm(p, j->coef, j->exp);
			j = j->next; // 사용완료
			p = p->next;

		}else // 차수가 같을 경우
		{
			if (i->coef == (j->coef * -1)) // 0이 될때는 무시
			{
				i = i->next;
				j = j->next;
			}
			else {
				appendTerm(p, j->coef + i->coef, j->exp); // 더하기
				i = i->next;
				j = j->next;
				p = p->next;
			}
		}

	}

	// 남은 다항식 있다면 붙이기 
	while (i != NULL) {
		appendTerm(p, i->coef, i->exp);
		p = p->next;
		i = i->next;
	}

	while (j != NULL) {
		appendTerm(p, j->coef, j->exp);
		p = p->next;
		j = j->next;
	}


	return result;
}