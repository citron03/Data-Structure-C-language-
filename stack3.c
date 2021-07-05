#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isOperand(char p);
void push(char* stack, int top, char S);
char pop(char* stack, int top);
int priority(char* c, int i);


void pushPri(int* pri, int top, int P);
int popPri(int* pri, int top);

// 스택을 이용하여 중위수식을 후위수식으로 변환하는 프로그램을 작성하시오

int main() {

//스택은 배열이나 연결리스트로 구현함
//수식의 피연산자는 영문자(대문자)로 나타내고, 각 수식의 최대길이는 100으로 함

	int N, i, top, topP, symbolP, j, pri[100], topPri; // 우선순위를 위한 스택을 하나 더 만든다. stack에 들어간 operator들의 우선순위를 저장한다.
	char stack[100], symbolsting[100];
	

	scanf("%d", &N);
	getchar();
	for (i = 0; i < N; i++) {
		j = 0;
		top = -1; // 스택 초기화
		topPri = -1;
		scanf("%s", symbolsting);

		while (symbolsting[j]) {
			if (isOperand(symbolsting[j]))
				printf("%c", symbolsting[j]);
			else if (symbolsting[j] == '('){
				top++;
				push(stack, top, symbolsting[j]);
				topPri++;
				pushPri(pri, topPri, 0); // 우선순위 0
			}
			else if (symbolsting[j] == ')') {
				while (stack[top] != '(' && top != -1){
					if (stack[top] == '&' || stack[top] == '|')
					{ // 한번더 한다
						printf("%c", pop(stack, top));
						top--;
						popPri(pri, topPri);
						topPri--;
						printf("%c", pop(stack, top));
						top--;
						popPri(pri, topPri);
						topPri--;
					}
					else {
						printf("%c", pop(stack, top));
						top--;
						popPri(pri, topPri);
						topPri--;
					}
				}
				pop(stack, top);
				top--;

				popPri(pri, topPri);
				topPri--;
			}
			else { // 계산 operation일 때

				// 심볼의 우선순위
				symbolP = priority(symbolsting, j);

				// 탑의 우선순위
				topP = popPri(pri, topPri);
				//printf(" %d %d  @\n",symbolP ,topP);
				while (top != -1 && 
				 symbolP <=	topP) { // 스택에 저장된 연산의 우선순위가 더 높을 때
					if (stack[top] == '&' || stack[top] == '|')
					{ // 한번더 한다
						printf("%c", pop(stack, top));
						top--;
						popPri(pri, topPri);
						topPri--;

						printf("%c", pop(stack, top));
						top--;
						popPri(pri, topPri);
						topPri--;
					}
					else {
						printf("%c", pop(stack, top));
						top--;
						popPri(pri, topPri);
						topPri--;
					}

					// 탑의 우선순위 재설정
					topP = popPri(pri, topPri);

				}

				if (symbolsting[j] == '&' || symbolsting[j] == '|')
				{ // 한번더 한다
					top++;
					push(stack, top, symbolsting[j]);
					topPri++;
					pushPri(pri, topPri, symbolP);

					top++;
					push(stack, top, symbolsting[j]);
					topPri++;
					pushPri(pri, topPri, symbolP);

					j++; // 다음으로
				}
				else {
					top++;
					push(stack, top, symbolsting[j]);
					topPri++;
					pushPri(pri,topPri, symbolP);
				}
			}
			j++;
		}

		while (top != -1) {
			printf("%c", pop(stack, top));
			top--;

		}

		printf("\n");
	}


	return 0;
}

int isOperand(char p) {

	if (p >= 'A' && p <= 'Z')
		return 1;
	else
		return 0;

}



void push(char* stack, int top, char S) {

	stack[top] = S;

}

char pop(char* stack, int top) {

	return stack[top];
}


int priority(char* symbolsting, int j) {


	if (symbolsting[j] == '!'
		// +
		|| (symbolsting[j] == '+' && 
			!(symbolsting[j - 1] >= 'A' && symbolsting[j - 1] <= 'Z') && 
			(symbolsting[j - 1] != ')') && 
			(symbolsting[j + 1] != '(')
			)
		// -
		|| (symbolsting[j] == '-' && 
			!(symbolsting[j - 1] >= 'A' && 
				symbolsting[j - 1] <= 'Z') && 
			(symbolsting[j - 1] != ')') &&
			(symbolsting[j + 1] != '(')
			)
		)
		return 6;
	else if (symbolsting[j] == '*')
		return 5;
	else if (symbolsting[j] == '/')
		return 5;
	else if (symbolsting[j] == '+')
		return 4;
	else if (symbolsting[j] == '-')
		return 4;
	else if (symbolsting[j] == '>')
		return 3;
	else if (symbolsting[j] == '<')
		return 3;
	else if (symbolsting[j] == '&')
		return 2;
	else if (symbolsting[j] == '|')
		return 1;
	else if (symbolsting[j] == '(')
		return 0;
}

// 우선순위 스택

void pushPri(int* pri, int top, int P) {
	pri[top] = P;
}
int popPri(int* pri, int top) {
	return pri[top];
}