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

/* Replace dest by src and free the dest */
void RBtreeTransplant(RBtree *tree, node *dest, node *src){
	if(dest == tree->root)
		tree->root = src;
	else if(dest == dest->p->l)
		dest->p->l = src;
	else
		dest->p->r = src;
	src->p = dest->p;

	return ;
}

node *RBtreeMinimal(RBtree *tree, node *nd){
	node *x, *y;
	x = tree->nil;
	y = nd;
	//x follows y
	while(y != tree->nil){
		x = y;
		y = y->l;
	}
	return x;
}
node *RBtreeMaximal(RBtree *tree, node *nd){
	node *x, *y;
	x = tree->nil;
	y = nd;
	//x follows y
	while(y != tree->nil){
		x = y;
		y = y->r;
	}
	return x;
}

void RBtreeFixup(RBtree *tree, node *x) {
	while(x != tree->root && x->color == BLACK){
		node *sibling;
		if(x == x->p->r){
			sibling = x->p->l;
			if(sibling->color == RED){ //convert case 1 to case 2, 3 or 4
				//we need to switch colors before rotations so that it does not create new violation
				//starting from x->p
				sibling->color = BLACK;
				x->p = RED;
				leftRotate(tree, x->p);
				sibling = x->p->r;

			}
			if(sibling->l->color == BLACK && sibling->r->color == BLACK){
				sibling->color = RED;
				x = x->p; //when sibling becomes red then parent violets the condition instead of x
			}
			else {
				if(sibling->r->color == BLACK){
					sibling->l->color = BLACK; 	//convert case 3 to case 4 by rotating about sibling and making it red
					sibling->color = RED;
					rightRotate(tree, sibling);
					sibling = x->p->l;
				}
				sibling->color = sibling->p->color; //sibling color is taken as parent color to make black count same after rotation
				sibling->p->color = BLACK; //Make parent color black to accept left child of sibling after rotation
				sibling->r->color = BLACK;
				leftRotate(tree, sibling->p);
				x = tree->root;
			}
		}

		else{
			sibling = x->p->r;
			if(sibling->color == RED){ //convert case 1 to case 2, 3 or 4
				//we need to switch colors before rotations so that it does not create new violation
				//starting from x->p
				sibling->color = BLACK;
				x->p = RED;
				rightRotate(tree, x->p);
				sibling = x->p->l;

			}
			if(sibling->r->color == BLACK && sibling->l->color == BLACK){
				sibling->color = RED;
				x = x->p; //when sibling becomes red then parent violets the condition instead of x
			}
			else {
				if(sibling->l->color == BLACK){
					sibling->r->color = BLACK; 	//convert case 3 to case 4 by rotating about sibling and making it red
					sibling->color = RED;
					leftRotate(tree, sibling);
					sibling = x->p->r;
				}
				sibling->color = sibling->p->color; //sibling color is taken as parent color to make black count same after rotation
				sibling->p->color = BLACK; //Make parent color black to accept left child of sibling after rotation
				sibling->l->color = BLACK;
				rightRotate(tree, sibling->p);
				x = tree->root;
			}
		}
	}

	x->color = BLACK;
}


void RBtreeDelete(RBtree *tree, int data){
	node *x = tree->nil, *y = tree->root, *temp;
	while(y != tree->nil) {
		x = y;
		if(data > y->data) {
			y = y->r;
		}
		else if(data < y->data) {
			y = y->l;
		}
		else {
			break;
		}
	}

	int ycolor = y->color;
	if(y->l == tree->nil){
		x = y->r;
		RBtreeTransplant(tree, y, y->r);
		free(y);
	}
	else if(y->r == tree->nil){
		x = y->l;
		RBtreeTransplant(tree, y, y->l);
		free(y);
	}
	else {
		node *mini = RBtreeMinimal(tree, y->r);
		ycolor = mini->color;
		if(mini != y->r){
			RBtreeTransplant(tree, mini, mini->r);
			mini->r = y->r;
			mini->r->p = mini;
		}

		RBtreeTransplant(tree, y, mini);
		mini->l = y->l;
		mini->color = y->color;
		x = mini->r;

		free(y);

	}

	if(ycolor == BLACK)
		RBtreeFixup(tree, x);
}

