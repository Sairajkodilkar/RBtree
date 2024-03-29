#ifndef _RB_TREE
#define _RB_TREE

#include <stdio.h>

/* RED-BLACK tree implimentation 
 * Reference: CLRS page 309-338
 *
 * RB tree has following properties which is to be maintained
 * 	1. Every node is either red or black.
 * 	2. The root is black.
 * 	3. Every leaf (NIL) is black.
 * 	4. If a node is Red, then both its children are black.
 * 	5. For each node, all simple paths from the node to descendant leaves constains the same number of black nodes.
 */


enum cl { RED, BLACK };

typedef struct node {
	int data;
	int color;

	struct node *p;
	struct node *l;
	struct node *r;

} node;


/* here instead of null pointer a sentinal is used
 * This is because of color requirement 
 */
extern node sentinal;

typedef struct RBtree {
	node *root;
	node *nil;
} RBtree;

/* Initializer function */
void initRBtree(RBtree *tree);

/* search the node in tree and gives back pointer to the subtree rooted at that node */
RBtree RBtreeSearch(const RBtree *tree, int data);

/* preorder traversal */
void RBpreorder(const RBtree *tree);

/* Insert the data in the Red black tree */
void RBtreeInsert(RBtree *tree, int data);

/* Delete the data element in Red black tree */
void RBtreeDelete(RBtree *tree, int data);

#endif

