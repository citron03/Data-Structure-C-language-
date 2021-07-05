#include <stdio.h>
#include <stdlib.h>

// 루트를 제외한 각 노드는 하나의 문자를 표현
typedef struct tree {

	//자식이 최대 26개인 트리 구축 필요
	struct tree* childrens[26];
	//영어 단어는 대문자로만 구성
	char data;

}tree;

int findWordInTree(tree* directory, char word);
void freeTree(tree* directory);

int main() {

	int N, i, j, find, searchNum, ii;
	char word[101];
	tree *directory = NULL, * p = NULL;

	directory = (tree*)malloc(sizeof(tree)); // 트리 루트

	for (i = 0; i < 26; i++) // 배열 포인터의 초기화
		directory->childrens[i] = NULL;

	scanf("%d", &N); // 입력될 사전 단어 개수
	getchar(); // 엔터키 제거

	for (i = 0; i < N; i++) {

		gets(word); // 단어 입력
		j = 0; // 단어의 처음부터 찾아나간다

		p = directory; // 처음부터 확인
		while (word[j] >= 'A' && word[j] <= 'Z') { // 단어를 하나하나 검증
			
			find = findWordInTree(p, word[j]); // 만약 존재하다면 그 위치를 받는다.
			if (p->childrens[find] == NULL) {  // 없다면 그 장소에 대입한다.
				p->childrens[find] = (tree*)malloc(sizeof(tree)); // 새로이 할당

				for (ii = 0; ii < 26; ii++)  // 배열 포인터의 초기화
					p->childrens[find]->childrens[ii] = NULL; // 새로 만든 노드의 포인터 배열을 초기화 한다.
				
				p->childrens[find]->data = word[j]; // 데이터를 대입한다.
				p = p->childrens[find]; // 경로로 진행한다.
			}
			else  // 데이터가 이미 존재한다면
				p = p->childrens[find]; // 그 경로로 진행한다.

			j++; // 다음 글자로 이동한다.
		}

	}


	scanf("%d", &searchNum); // 찾을 단어의 개수
	getchar(); // 엔터키 제거
	
	for (i = 0; i < searchNum; i++) { // 반복

		gets(word); // 단어를 입력받는다.
		j = 0;
		p = directory; // 초기화


		while (word[j] >= 'A' && word[j] <= 'Z') { // 단어 찾기

			find = findWordInTree(p, word[j]); // 만약 존재하다면 그 위치를 받는다.
			if (p->childrens[find] == NULL) { // 찾지 못했다.
				printf("\n"); // 다음 단어로 넘어간다.
				break;
			}
			else {
				printf("%c", p->childrens[find]->data); // 출력
				p = p->childrens[find]; // 그리고 그 경로로 진행한다.
			}
			j++; // 다음 글자로
		}

	}


	// 메모리 할당 해제
	freeTree(directory); // 내부 노드들 해제
	free(directory); // 루트 노드 해제
	return 0;
}


int findWordInTree(tree* directory, char word) { // 데이터가 이미 존재하는지 찾는다.

	int i; 

	for (i = 0; i < 26; i++) {
		if (directory->childrens[i] == NULL) // 끝에 도달하였을 시에
			return i; 
		else if (directory->childrens[i]->data == word) // 이미 존재하면
			return i;
	}
}

void freeTree(tree* directory) {

	int i;

	for (i = 0; i < 26; i++) { // 최대 26번 반복
		if (directory->childrens[i] != NULL) { // 데이터가 있는 상태일때
			freeTree(directory->childrens[i]); // 재귀
			free(directory->childrens[i]); // 해제한다.
		}
		else
			break; // 끝에 도달시 종료
	}

}