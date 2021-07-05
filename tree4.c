#include <stdio.h>
#include <stdlib.h>


typedef struct tree {

	struct tree* left, * right;
	int num;

}tree;


void makeRootNode(tree** root, int left, int right, int center);
void makeNode(tree* root, int left, int right);
void find(tree* root, int center, tree** R);
void treeFree(tree* root);


int main() {

	int nodeNum, i, left, right, center, fNum, j;
	tree* root = NULL, * p = NULL;
	char LR[101];

	scanf("%d", &nodeNum);

	scanf("%d %d %d", &center, &left, &right); // 루트 노드
	makeRootNode(&root, left, right, center); // 루트 노드 먼저 만듦

	for (i = 1; i < nodeNum; i++) {

		scanf("%d %d %d", &center, &left, &right);


		find(root, center, &p); // 찾기
		makeNode(p, left, right); // 노드 만듦
	}


	scanf("%d", &fNum);
	getchar();

	for (i = 0; i < fNum; i++) {

		p = root;
		gets(LR);
		j = 0;

		while (LR[j] == 'L' || LR[j] == 'R') {
			printf(" %d", p->num);

			if (LR[j] == 'L') 
				p = p->left;
			else 
				p = p->right;
			j++;
		}
		printf(" %d\n", p->num);
	}

	treeFree(root);

	return 0;
}




void makeRootNode(tree** root, int left, int right, int center) {


	tree* rootTmp = NULL;

	rootTmp = (tree*)malloc(sizeof(tree));

	rootTmp->num = center;
	rootTmp->left = (tree*)malloc(sizeof(tree));
	rootTmp->right = (tree*)malloc(sizeof(tree));

	rootTmp->left->num = left;
	rootTmp->right->num = right;

	rootTmp->right->left = NULL;
	rootTmp->right->right = NULL;
	rootTmp->left->left = NULL;
	rootTmp->left->right = NULL;

	*root = rootTmp;

}


void makeNode(tree* root, int left, int right) {

	

	if (left == 0) 
		root->left = NULL;
	else {
		root->left = (tree*)malloc(sizeof(tree));
		root->left->num = left;
		root->left->left = NULL;
		root->left->right = NULL;
	}


	if (right == 0) 
		root->right = NULL;
	else {
		root->right = (tree*)malloc(sizeof(tree));
		root->right->num = right;
		root->right->left = NULL;
		root->right->right = NULL;
	}

}


void find(tree* root, int center, tree** R){

	if (root->num == center)
		*R = root;
	if(root->left != NULL)
		find(root->left, center, R);
	if (root->right != NULL)
		find(root->right, center, R);
	
}



void treeFree(tree* root) {

	if (root->left == NULL || root->right == NULL)
		free(root);
	else {
		treeFree(root->left);
		treeFree(root->right);
		free(root);
	}
}