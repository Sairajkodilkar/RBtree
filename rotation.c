#include "rotation.h"
#include "RBtree.h"

void leftRotate(RBtree *tree, node *nd){
	node *x, *y;
	x = nd;
	y = x->r;

	x->r = y->l;
	y->l = x;

	if(x->r != tree->nil)
		x->r->p = x;

	if(x == tree->root)
		tree->root = y;
	else if(x->p->l == x)
		x->p->l = y;
	else 
		x->p->r= y;

	y->p = x->p;
	x->p = y;
	
	return;
}


void rightRotate(RBtree *tree, node *nd){
	node *x, *y;
	x = nd;
	y = x->l;

	x->l = y->r;
	y->r = x;

	if(x->l != tree->nil)
		x->l->p = x;

	if(x == tree->root)
		tree->root = y;
	if(x->p->r == x)
		x->p->r= y;
	else 
		x->p->l= y;

	y->p = x->p;
	x->p = y;
	
	return;
}

