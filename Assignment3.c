#include<stdio.h>
#include<stdlib.h>


//헤더와 트레일러를 가지는 이중 연결 리스트

typedef struct Node {

	int element; // 양의정수
	struct Node* next; // 다음 포인터
	struct Node* prev; // 이전 포인터

}Node;

// 그룹의 헤더 단일 연결 리스트
typedef struct groupNode {

	char groupName; // 그룹의 이름
	struct groupNode* next; // 다음 포인터
	Node* header; // 그룹의 헤더 노드
	Node* trailer; // 그룹의 트레일러 노드
	
}groupNode;

// Create_group(g) : 그룹 g를 생성한다.
void Create_group(groupNode* headerGroup,char g);

// Destory_group(g) : 그룹 g를 파괴한다.
void Destory_group(groupNode* headerGroup,char g);

// Add_element(g, e) : 그룹 g에 원소 e를 추가한다.
void Add_element(groupNode* headerGroup,char g, int e);


// Remove_element(g, e) : 그룹 g의 원소 e를 제거한다.
void Remove_element(groupNode* headerGroup,char g, int e);

// Show_all() : 존재하는 모든 그룹의 원소들을 그룹별로 출력
void Show_all(groupNode* headerGroup);


int main() {

	// 그룹 연결리스트의 헤더 노드
	groupNode* headerGroup = NULL, * p, * q;
	int numCalculate, i, element;
	char charCalculate, groupName, tmp;

	// 초기 그룹의 헤더 노드 설정
	headerGroup = (groupNode*)malloc(sizeof(groupNode));
	headerGroup->header = NULL; // 그룹 헤더노드
	headerGroup->trailer = NULL; // 그룹 헤더노드
	headerGroup->next = NULL;


	scanf("%d", &numCalculate); // 연산 개수를 입력한다.
	for (i = 0; i < numCalculate; i++) { // 반복

		scanf("%c", &tmp); // 공백제거
		scanf("%c", &charCalculate); // 연산 입력

		//printf("$ %c $\n", charCalculate);

		switch (charCalculate) {
		case 'C': // 그룹 생성
			scanf("%c", &tmp); // 공백제거
			scanf("%c", &groupName); // 그룹 이름 입력
			Create_group(headerGroup, groupName);
			break;
		case 'D': // 그룹 삭제
			scanf("%c", &tmp); // 공백제거
			scanf("%c", &groupName); // 그룹 이름 입력
			Destory_group(headerGroup, groupName);
			break;

		case 'A': // 원소 추가 
			scanf("%c", &tmp); // 공백제거
			scanf("%c %d", &groupName,&element); // 그룹 이름과 원소 입력
			Add_element(headerGroup, groupName, element);
			break;

		case'R': // 원소 삭제
			scanf("%c", &tmp); // 공백제거
			scanf("%c %d", &groupName, &element); // 그룹 이름과 원소 입력
			Remove_element(headerGroup, groupName, element);
			break;

		case 'S': // 출력
			Show_all(headerGroup);
			break;
		}

	}

	////// 그룹과 element 모두 free //////

	p = headerGroup->next; // 헤더 다음의 위치 (초기 위치)

	free(headerGroup); // 그룹 헤더 노드는 원소의 헤더와 트레일러가 없으니 따로 해제
	Node* pp , * qq; // 원소의 연결리스트 해제

	while (p != NULL) { // 반복으로 해제	
		q = p; // 해제할 위치
		p = p->next; // 다음 해제할 그룹을 미리 저장한다.

		pp = q->header; // 그룹의 원소 연결리스트 접근
	
		while (1) { // 반복으로 원소 연결리스트 해제
			qq = pp; // 해제할 위치
			pp = pp->next; // 다음 해제할 노드 원소 미리 연결

			free(qq); // 해제
			if (pp == NULL) // 트레일러 노드, next가 NULL인 노드에 도착시 끝
				break;
		}

		free(q); // 해제
	}


	return 0;
}



void Create_group(groupNode* headerGroup, char g) {
	//그룹 g가 이미 존재하는 경우, 아무 작업도 하지 않음
	groupNode* p = headerGroup->next; // 첫번째 값의 위치
	int S = 0; // 이미 존재하면 1로 바꿔준다.

	while (p != NULL) {
		if (p->groupName == g) {
			S = 1; // 이미 그룹 존재
			break;
		}
		p = p->next; // 다음으로
	}

	if (S == 0) {
		p = headerGroup; // 위치 초기화

		//그룹 이름은 오름차순으로 저장
		while (1) { // 추가할 위치 찾기

			if (p->next == NULL) { // 마지막 위치에 도착하면 끝에 추가
				p->next = (groupNode*)malloc(sizeof(groupNode)); // 그룹 생성

				// 원소 노드를 만든다.
				p->next->header = (Node*)malloc(sizeof(Node));
				p->next->trailer = (Node*)malloc(sizeof(Node));
				// 연결
				p->next->header->next = p->next->trailer;
				p->next->header->prev = NULL;
				p->next->trailer->next = NULL;
				p->next->trailer->prev = p->next->header;

				// 생성된 그룹 설정
				p->next->next = NULL;
				p->next->groupName = g;

				break; // 끝
			}
			else if (p->next->groupName > g) { // 자신보다 큰 그룹의 이름을 만남

				groupNode* newGroup = (groupNode*)malloc(sizeof(groupNode)); // 새 그룹 생성
				// 연결
				newGroup->next = p->next; // 다음
				p->next = newGroup; // 이전
				// 생성된 그룹 설정
				newGroup->groupName = g;

				// 원소 노드를 만든다.
				newGroup->header = (Node*)malloc(sizeof(Node));
				newGroup->trailer = (Node*)malloc(sizeof(Node));
				// 연결
				newGroup->header->next = p->next->trailer;
				newGroup->header->prev = NULL;
				newGroup->trailer->next = NULL;
				newGroup->trailer->prev = p->next->header;

				break; // 끝
			}



			p = p->next; // 다음으로
		}
		
	}
	
	


}

void Destory_group(groupNode* headerGroup, char g) {
	// 그룹 g가 존재하지 않은 경우, 아무 작업도 하지 않음

	groupNode* p = headerGroup->next; // 첫번째 값의 위치
	groupNode* q = headerGroup; // 삭제할 위치 전의 노드 위치
	while (p != NULL) {

		if (p->groupName == g) { // 삭제할 그룹 발견시
			q->next = p->next; // 삭제할 그룹을 중심으로 전후 연결
			free(p); // 삭제
			break;
		}
		else if (p->groupName > g) // 오름차순 이기 때문에
			break;
		q = p;
		p = p->next; // 다음으로
	}


}


void Add_element(groupNode* headerGroup, char g, int e) {

	//그룹 g가 존재하지 않은 경우, 아무 작업도 하지 않음
	//그룹 g에 원소 e가 이미 존재하는 경우, 아무 작업도 하지 않음
	//(단, 번호가 같은 원소가 있어도 그룹이 다르면 다른 원소로 간주함에 주의.예를 들어, 그룹 A의 원소 10은 Add(B, 10) 연산에는 아무 영향을 미치지 않음.) 
	//원소들은 오름차순으로 저장되어 있어야 함.따라서, Add 연산 시 원소가 삽입될 위치를 원소의 번호를 비교해서 찾아야 함.
	groupNode* p = headerGroup->next; // 첫번째 값의 위치
	Node* addFind;

	while (p != NULL) { // 그룹 찾기

		if (p->groupName == g) { // 원소를 추가할 그룹을 발견
			addFind = p->header; // 원소의 헤더 노드

			while (1) { // 원소를 넣을 위치를 찾기
				addFind = addFind->next; // 다음 노드로
				if (addFind->next == NULL) { // 트레일러 노드에 도달

					Node* addNewElement = (Node*)malloc(sizeof(Node)); // 노드 생성
					addNewElement->next = addFind->prev->next;
					addNewElement->prev = addFind->prev;
					//갱신
					addFind->prev->next = addNewElement;
					addFind->prev = addNewElement;

					addNewElement->element = e; // 값을 넣음

					p = NULL; // 그룹 찾기 강제종료
					break; // 끝
				}
				else if (addFind->element > e) { // 삽입할 위치를 찾음

					Node* addNewElement = (Node*)malloc(sizeof(Node)); // 노드 생성
					addNewElement->next = addFind->prev->next;
					addNewElement->prev = addFind->prev;
					//갱신
					addFind->prev->next = addNewElement;
					addFind->prev = addNewElement;

					addNewElement->element = e; // 값을 넣음

					p = NULL; // 그룹 찾기 강제종료
					break; // 끝
				}
				else if (addFind->element == e) { // 이미 있음
					p = NULL; // 그룹 찾기 강제종료
					break; // 끝
				}
			}
		}
		else if (p->groupName > g) // 오름차순 이기 때문에
			break;

		if(p != NULL) // 끝이 아닐때
			p = p->next; // 다음으로
	}

}


void Remove_element(groupNode* headerGroup, char g, int e) {

	//해당 원소가 없는 경우, 아무 작업도 하지 않음
	//이 연산의 결과로 그룹 g에 원소가 하나도 없어도, 그룹 자체는 존재(즉, 파괴하지 않음)

	groupNode* p = headerGroup->next; // 첫번째 값의 위치
	Node* addFind;

	while (p != NULL) { // 그룹 찾기

		if (p->groupName == g) { // 원소를 제거할 그룹을 발견
			addFind = p->header->next; // 첫번째 원소의 위치

			while (addFind != NULL) { //제거할 원소 찾기

				if (addFind->element == e) { // 찾음

					// 연결 정보 갱신
					addFind->prev->next = addFind->next;
					addFind->next->prev = addFind->prev;

					free(addFind); // 삭제
					p = NULL; // 그룹 찾기 강제종료
					break; // 끝
				}

				addFind = addFind->next; // 다음 노드로
			}
		}
		if(p != NULL) // 끝이 아닐때
			p = p->next; // 다음 그룹
	}

}


void Show_all(groupNode* headerGroup) {

	// 모든 그룹, 원소를 출력
	groupNode* p = headerGroup->next; // 첫 노드
	Node* q;

	while(p != NULL) { // 출력

		printf("%c:", p->groupName); // 그룹 이름을 출력한다.
		q = p->header->next; // 원소의 헤더노드 다음 노드, 첫번째 값이 있는 노드
		while (q->next != NULL) { // next가 NULL이면 트레일러 노드. 트레일러 노드 도달시 종료
			// 모든 원소 출력
			printf(" %d", q->element);
			q = q->next; // 다음으로
		}

		p = p->next; // 다음 그룹으로
		printf("\n"); // 줄바꿈
	}

}
