#include <stdio.h>
#include <stdlib.h>



typedef struct tree {

	struct tree* left, * right;
	int data, id;

}tree;


int post(tree* p);

void fpre(tree* p, int Tid);


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

	int N;

	scanf("%d", &N);

	fpre(p, N);

	return 0;
}



void fpre(tree* p, int Tid) {

	if (Tid <= 0 || Tid >= 9)
		printf("-1");
	else {
		if (p->id == Tid)
			printf("%d", post(p));
		if (p->left != NULL)
			fpre(p->left, Tid);
		if (p->right != NULL)
			fpre(p->right, Tid);
	}
}




int post(tree* p) {


	if (p == NULL)
		return 0;


	if (p->left != NULL && p->right != NULL)
		return p->data + post(p->left) + post(p->right);
	else if (p->left != NULL || p->right == NULL)
		return post(p->left) + p->data;
	else if (p->right != NULL || p->left == NULL)
		return post(p->right) + p->data;
	else
		return p->data;


}