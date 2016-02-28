// BinaryTree.cpp : Defines the entry point for the console application.
//

//TODO - make_shared -- copy_tree -- delete_node!

#include <iostream>
#include <memory>

using namespace std;

typedef struct nod
{
	int data;
	struct nod* leftNode;
	struct nod* rightNode;
} node;

void insertNode(node** tree, int value)
{

	if (*tree == nullptr)
	{
		*tree = new node;
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

void printTreeOrder(node* tree)
{
	if (tree != nullptr)
	{
		printTreeOrder(tree->leftNode);
		cout << "Node ->" << tree->data << endl;
		printTreeOrder(tree->rightNode);
	}
}

void printTreeWidth(node * tree)
{
	if (tree != nullptr)
	{
		printTreeWidth(tree->leftNode);
		printTreeWidth(tree->rightNode);
		cout << "Node ->" << tree->data << endl;
	}
}

void cutTree(node ** tree)
{
	if (*tree != nullptr)
	{
		cutTree(&((*tree)->leftNode));
		cutTree(&((*tree)->rightNode));
		delete *tree;
	}
}

void printTreePO(node * tree)
{
	if (tree != nullptr)
	{
		cout << "Node ->" << tree->data << endl;
		printTreePO(tree->leftNode);
		printTreePO(tree->rightNode);
	}
}

bool searchTree(node * tree, int value)
{
	if (tree != nullptr)
	{
		if (tree->data == value)
		{
			return true;
		}
		else
			return (searchTree(tree->leftNode, value) || searchTree(tree->rightNode, value));
	}
	else
		return false;
}

void copyTree(node * sourceTree, node ** destTree)
{
	if (sourceTree != nullptr)
	{
		*destTree = new node;
		(*destTree)->data = sourceTree->data;
		(*destTree)->leftNode = nullptr;
		(*destTree)->rightNode = nullptr;
		copyTree(sourceTree->leftNode, &((*destTree)->leftNode));
		copyTree(sourceTree->rightNode, &((*destTree)->rightNode));
	}
}

int main()
{
	node* tree = nullptr;
	int value, searchValue;
	for (auto i = 0; i <= 5; i++)
	{
		cout << "Insert value for the tree ";
		cin >> value;
		insertNode(&tree, value);
	}
	cout << "In order: " << endl;
	printTreeOrder(tree);
	cout << "By width: " << endl;
	printTreeWidth(tree);
	cout << "In Pre-Order: " << endl;
	printTreePO(tree);
	/*
	cout << "Insert value for the tree ";
	cin >> searchValue;
	if (searchTree(tree, searchValue))
	{
		cout << "Found!" << endl;
	}
	else
	{
		cout << "Value " << searchValue << " not found." << endl;
	}*/

	node *treeCopy = nullptr;
	copyTree(tree, &treeCopy);
	cout << endl;
	cout << "In order2: " << endl;
	printTreeOrder(treeCopy);
	cout << "By width2: " << endl;
	printTreeWidth(treeCopy);
	cout << "In Pre-Order2: " << endl;
	printTreePO(treeCopy);
	cutTree(&tree);
	cutTree(&treeCopy);
	return 0;
}
