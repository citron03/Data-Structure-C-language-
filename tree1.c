#include <stdio.h>
#include <stdlib.h>


// data(폴더 용량), left (왼쪽 자식 링크), right (오른쪽 자식 링크)

typedef struct tree {

	int data;
	struct tree* left, * right;

}tree;

void setting(tree** root);
void allFree(tree* root);
tree* insertTree(int data, tree* left, tree* right);

int main() {

	tree* root = NULL, * p = NULL;
	int N, i, NUM = 0;
	setting(&root);
	scanf("%d", &N);

	p = root;

	if (N >= 9)
		p = NULL;
	else if (N == 2 || N == 4 || N == 5) {
		p = p->left;
		if (N != 2) {
			if (N % 2 == 0)
				p = p->left;
			else
				p = p->right;
		}

	}
	else if(N != 1) {
		p = p->right;
		if (N != 3) {
			p = p->right;

			if (N != 6) {
				if (N % 2 == 0)
					p = p->right;
				else
					p = p->left;
			}
		}
	}
		



	
	if (p == NULL)
		printf("-1");
	else {
		printf("%d ", p->data);
		if (p->left != NULL)
			printf("%d ", p->left->data);
		if (p->right != NULL)
			printf("%d ", p->right->data);
	}
	
	allFree(root);

	return 0;
}


void setting(tree** root) {

	tree* l, * r, * F2, * F6, * F3;

	// F4
	l = insertTree(70, NULL, NULL);
	//F5
	r = insertTree(90, NULL, NULL);
	//F2
	F2 = insertTree(30, l, r);

	//F7
	l = insertTree(130, NULL, NULL);
	//F8
	r = insertTree(80, NULL, NULL);
	//F6
	F6 = insertTree(120, l, r);
	//F3
	F3 = insertTree(50, NULL, F6);

	//F1
	*root = insertTree(20, F2, F3);
}

void allFree(tree* root) {


	free(root->right->right->left);
	free(root->right->right->right);
	free(root->right->right);
	free(root->right);
	free(root->left->left);
	free(root->left->right);
	free(root->left);
	free(root);
}



tree* insertTree(int data, tree* left, tree* right) {
	// F6 = add(120, F7, F8)

	tree* p = NULL;

	p = (tree*)malloc(sizeof(tree));
	p->data = data;
	p->right = right;
	p->left = left;


	return p;

}