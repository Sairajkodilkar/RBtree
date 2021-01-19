#include <stdio.h>
#include <stdlib.h>
#include "RBtree.h"
#include "rotation.h"

extern node sentinal;

node sentinal = {0, BLACK, NULL, NULL, NULL};

void initRBtree(RBtree *tree){
	tree->nil = &sentinal;
	tree->root = tree->nil;
	return;
}

RBtree RBtreeSearch(const RBtree *tree, int data){
	node *temp = tree->root; 
	RBtree tr;
	while(temp != tree->nil && temp->data != data){
		if(temp->data > data)
			temp = temp->l;
		
		else if(temp->data < data)
			temp = temp->r;
	}

	tr.root = temp;
	tr.nil = tree->nil;

	return tr;
}

void _RBpreorder(const RBtree *tree, const node *n, int depth){
	if(n == tree->nil)
		return;
	else 
		_RBpreorder(tree, n->l, depth + 1);
		printf("%d at %d\n",n->data, depth);
		_RBpreorder(tree, n->r, depth + 1);
}
void RBpreorder(const RBtree *tree){
	_RBpreorder(tree, tree->root, 0);
}

/* fixup the tree which may be disturbed by newly inserted node z */

void RBInsertFix(RBtree *tree, node *z){
	node *uncle;
	while(z->p->color == RED){
		if(z->p == z->p->p->l){ // when uncle is right child
			uncle = z->p->p->r;
			if(uncle->color == RED){ //case 1: uncle is also red then simply convert it to black 
				uncle->color = BLACK;
				z->p->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else{
				if(z == z->p->r){ //case 2: convert case 2 to case 3 
					z = z->p;
					leftRotate(tree, z);
				}
				z->p->color = BLACK; //case 3: make parent black and grandparent red(valid since uncle is black) and rightrotate  
				z->p->p->color = RED;
				rightRotate(tree, z->p->p); 
			}
		}
		else {
			//same as above but uncle is left child
			uncle = z->p->p->l;
			if(uncle->color == RED){
				uncle->color = BLACK;
				z->p->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else{
				if(z == z->p->l){ 
					z = z->p;
					rightRotate(tree, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftRotate(tree, z->p->p); 
			}
		}

	}
	tree->root->color = BLACK;
	return;
}

void RBtreeInsert(RBtree *tree, int data){
	//Initialize new node;
	node *z = (node *) malloc(sizeof(node));
	z->color = RED;
	z->data = data;
	z->l = tree->nil;
	z->r = tree->nil;
	z->p = tree->nil;

	node *x = tree->nil, *y = tree->root;
	while(y != tree->nil) {
		x = y;
		if(data > y->data) {
			y = y->r;
		}
		else if( data < y->data) {
			y = y->l;
		}
		else {
			return;
		}
	}
	z->p = x;
	if(x == tree->nil)
		tree->root = z;
	else if(data > x->data)
		x->r = z;
	else
		x->l = z;

	RBInsertFix(tree, z);
	return;
}


void RBtreeDelete(RBtree *tree, int data){
}

