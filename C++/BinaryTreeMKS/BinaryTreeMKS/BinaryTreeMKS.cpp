// BinaryTree.cpp : Defines the entry point for the console application.
//

//TODO - make_shared -- copy_tree -- delete_node!

#include <iostream>
#include <memory>
#include "stdafx.h"

using namespace std;

typedef struct nod
{
	int data;
	shared_ptr<struct nod> leftNode;
	shared_ptr<struct nod> rightNode;
} node;

void insertNode(shared_ptr<node> *tree, int value)
{

	if (*tree == nullptr)
	{
		*tree = make_shared<node>();
		(*tree)->data = value;
		(*tree)->leftNode = nullptr;
		(*tree)->rightNode = nullptr;
	}
	else if ((*tree)->data <= value)
	{
		insertNode(&((*tree)->rightNode), value);
	}
	else
	{
		insertNode(&((*tree)->leftNode), value);
	}
}

void printTreeOrder(shared_ptr<node> tree)
{
	if (tree != nullptr)
	{
		printTreeOrder(tree->leftNode);
		cout << "Node ->" << tree->data << endl;
		printTreeOrder(tree->rightNode);
	}
}


int main()
{
	shared_ptr<node> tree = nullptr;
	int value, searchValue;
	for (auto i = 0; i <= 5; i++)
	{
		cout << "Insert value for the tree ";
		cin >> value;
		insertNode(&tree, value);
	}
	cout << "In order: " << endl;
	printTreeOrder(tree);
	return 0;
}