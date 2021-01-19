#include "RBtree.h"

int main(){
	RBtree redblack;

	initRBtree(&redblack);
	int n;

	while(scanf("%d", &n) != EOF){
		RBtreeInsert(&redblack, n);
		RBpreorder(&redblack);
		printf("\n");
	}
	return 0;
}
