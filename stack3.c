#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isOperand(char p);
void push(char* stack, int top, char S);
char pop(char* stack, int top);
int priority(char* c, int i);


void pushPri(int* pri, int top, int P);
int popPri(int* pri, int top);

// ������ �̿��Ͽ� ���������� ������������ ��ȯ�ϴ� ���α׷��� �ۼ��Ͻÿ�

int main() {

//������ �迭�̳� ���Ḯ��Ʈ�� ������
//������ �ǿ����ڴ� ������(�빮��)�� ��Ÿ����, �� ������ �ִ���̴� 100���� ��

	int N, i, top, topP, symbolP, j, pri[100], topPri; // �켱������ ���� ������ �ϳ� �� �����. stack�� �� operator���� �켱������ �����Ѵ�.
	char stack[100], symbolsting[100];
	

	scanf("%d", &N);
	getchar();
	for (i = 0; i < N; i++) {
		j = 0;
		top = -1; // ���� �ʱ�ȭ
		topPri = -1;
		scanf("%s", symbolsting);

		while (symbolsting[j]) {
			if (isOperand(symbolsting[j]))
				printf("%c", symbolsting[j]);
			else if (symbolsting[j] == '('){
				top++;
				push(stack, top, symbolsting[j]);
				topPri++;
				pushPri(pri, topPri, 0); // �켱���� 0
			}
			else if (symbolsting[j] == ')') {
				while (stack[top] != '(' && top != -1){
					if (stack[top] == '&' || stack[top] == '|')
					{ // �ѹ��� �Ѵ�
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
			else { // ��� operation�� ��

				// �ɺ��� �켱����
				symbolP = priority(symbolsting, j);

				// ž�� �켱����
				topP = popPri(pri, topPri);
				//printf(" %d %d  @\n",symbolP ,topP);
				while (top != -1 && 
				 symbolP <=	topP) { // ���ÿ� ����� ������ �켱������ �� ���� ��
					if (stack[top] == '&' || stack[top] == '|')
					{ // �ѹ��� �Ѵ�
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

					// ž�� �켱���� �缳��
					topP = popPri(pri, topPri);

				}

				if (symbolsting[j] == '&' || symbolsting[j] == '|')
				{ // �ѹ��� �Ѵ�
					top++;
					push(stack, top, symbolsting[j]);
					topPri++;
					pushPri(pri, topPri, symbolP);

					top++;
					push(stack, top, symbolsting[j]);
					topPri++;
					pushPri(pri, topPri, symbolP);

					j++; // ��������
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

// �켱���� ����

void pushPri(int* pri, int top, int P) {
	pri[top] = P;
}
int popPri(int* pri, int top) {
	return pri[top];
}