#include <stdio.h>
#include <stdlib.h>



typedef struct tree {

	struct tree* left, * right;
	int data, id;

}tree;


void pre(tree* p);
void cen(tree* p);
void post(tree* p);

void fpre(tree* p, int Tid);
void fcen(tree* p, int Tid);
void fpost(tree* p, int Tid);


int main() {


	// 트리 세팅

	tree* p = NULL;
	p = (tree*)malloc(sizeof(tree));
	p->data = 20;
	p->id = 1;

	p->left = (tree*)malloc(sizeof(tree));
	p->left->data = 30;
	p->left->id = 2;

	p->right = (tree*)malloc(sizeof(tree));
	p->right->id = 3;
	p->right->data = 50;
	p->right->left = NULL;

	p->left->left = (tree*)malloc(sizeof(tree));
	p->left->left->id = 4;
	p->left->left->data = 70;
	p->left->left->left = NULL;
	p->left->left->right = NULL;

	p->left->right = (tree*)malloc(sizeof(tree));
	p->left->right->id = 5;
	p->left->right->data = 90;
	p->left->right->left = NULL;
	p->left->right->right = NULL;

	p->right->right = (tree*)malloc(sizeof(tree));
	p->right->right->id = 6;
	p->right->right->data = 120;
	p->right->left = NULL;

	p->right->right->left = (tree*)malloc(sizeof(tree));
	p->right->right->left->id = 7;
	p->right->right->left->data = 130;
	p->right->right->left->left = NULL;
	p->right->right->left->right = NULL;

	p->right->right->right = (tree*)malloc(sizeof(tree));
	p->right->right->right->id = 8;
	p->right->right->right->data = 80;
	p->right->right->right->left = NULL;
	p->right->right->right->right = NULL;


	// 본문 시작

	int N, Tid;

	scanf("%d %d", &N, &Tid);

	switch (N)
	{
	case 1: // 전위 순회
		fpre(p, Tid);
		break;

	case 2: // 중위 순회
		fcen(p, Tid);
		break;

	case 3: // 후위 순회
		fpost(p, Tid);
		break;

	}
	if (Tid >= 9 || Tid <= 0)
		printf("-1");

	return 0;
}



void fpre(tree* p, int Tid) {

	if (p->id == Tid)
		pre(p);
	if (p->left != NULL)
		fpre(p->left, Tid);
	if (p->right != NULL)
		fpre(p->right, Tid);

}
void fcen(tree* p, int Tid) {

	if (p->left != NULL)
		fcen(p->left, Tid);
	if (p->id == Tid)
		cen(p);
	if (p->right != NULL)
		fcen(p->right, Tid);


}
void fpost(tree* p, int Tid) {


	if (p->left != NULL)
		fpost(p->left, Tid);
	if (p->right != NULL)
		fpost(p->right, Tid);
	if (p->id == Tid)
		post(p);

}




void pre(tree* p) {

	printf(" %d", p->data);
	if(p->left != NULL)
		pre(p->left);
	if(p->right != NULL)
		pre(p->right);

}
void cen(tree* p) {


	if (p->left != NULL)
		cen(p->left);
	printf(" %d", p->data);
	if (p->right != NULL)
		cen(p->right);


}
void post(tree* p) {

	if (p->left != NULL)
		post(p->left);
	if (p->right != NULL)
		post(p->right);
	printf(" %d", p->data);

}

