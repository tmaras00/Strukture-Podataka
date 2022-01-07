#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;
typedef struct Node* position;
typedef struct Node
{
	int el;
	position left;
	position right;
}node;

position create_el(int a);
position insert(position root, position p);//vraca root
int ab(int a, int b, position root);
int replace(position root);
int printinorder(position root);

int main()
{
	position root = NULL;
	int i = 0;
	int a[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	for (i; i < 10; i++)
	{
		root = insert(root, create_el(a[i]));
	}
	printinorder(root);
	replace(root);
	printinorder(root);
	return 0;
}

int printinorder(position p) {
	if (p == NULL) {
		return EXIT_SUCCESS;
	}
	else {

		printinorder(p->left);
		printf("%d\t", p->el);
		printinorder(p->right);
	}
	return EXIT_SUCCESS;
}

position create_el(int a)
{
	position p = (position)malloc(sizeof(node));
	p->left = p->right = NULL;
	p->el = a;
	return p;
}

position insert(position root, position p)
{
	if (root == NULL)
	{
		root = p;
		return root;
	}
	else if (root->el <= p->el)
	{
		root->left = insert(root->left, p);
	}
	else if (root->el > p->el)
	{
		root->right = insert(root->right, p);
	}
	return root;
}

int ab(int a, int b, position root)
{
	if (root->left != NULL)
	{
		a = root->left->el;
	}
	if (root->right != NULL)
	{
		b = root->right->el;
	}
	return 0;
}

int replace(position current)
{
	int l_before = 0;
	int d_before = 0;
	int l_now = 0;
	int d_now = 0;

	if (current != NULL)
	{
		if (current->left != NULL)
		{
			l_before = current->left->el;
		}
		if (current->right != NULL)
		{
			d_before = current->right->el;
		}

		replace(current->left);
		replace(current->right);

		if (current->left != NULL)
		{
			l_now = current->left->el;
		}

		if (current->right != NULL)
		{
			d_now = current->right->el;
		}

		return current->el = l_now + d_now + l_before + d_before;
	}
	return 0;
}
