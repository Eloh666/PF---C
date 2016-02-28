// BinaryTree.cpp : Defines the entry point for the console application.
//

//TODO - make_shared -- copy_tree -- delete_node!

#include <iostream>
#include <memory>
#define LEFT 0
#define RIGHT 1

using namespace std;

typedef struct nod
{
	int data;
	shared_ptr<struct nod> leftNode;
	shared_ptr<struct nod> rightNode;
} node;

void insertNode(shared_ptr<node>* tree, int value)
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

void printTreeWidth(shared_ptr<node> tree)
{
	if (tree != nullptr)
	{
		printTreeWidth(tree->leftNode);
		printTreeWidth(tree->rightNode);
		cout << "Node ->" << tree->data << endl;
	}
}

void cutTree(shared_ptr<node>* tree)
{
	if (*tree != nullptr)
	{
		cutTree(&((*tree)->leftNode));
		cutTree(&((*tree)->rightNode));
		*tree = nullptr;
	}
}

void printTreePO(shared_ptr<node> tree)
{
	if (tree != nullptr)
	{
		cout << "Node ->" << tree->data << endl;
		printTreePO(tree->leftNode);
		printTreePO(tree->rightNode);
	}
}

bool searchTree(shared_ptr<node> tree, int value)
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

void copyTree(shared_ptr<node> sourceTree, shared_ptr<node>* destTree)
{
	if (sourceTree != nullptr)
	{
		*destTree = make_shared<node>();
		(*destTree)->data = sourceTree->data;
		(*destTree)->leftNode = nullptr;
		(*destTree)->rightNode = nullptr;
		copyTree(sourceTree->leftNode, &((*destTree)->leftNode));
		copyTree(sourceTree->rightNode, &((*destTree)->rightNode));
	}
}

void delNod(shared_ptr<node> *parentNode, shared_ptr<node> *targetNode, int location)
{
		if((*targetNode)->leftNode != nullptr && (*targetNode)->rightNode != nullptr )
		{
			auto swapPointer = &((*targetNode)->rightNode);
			int swapValue;
			while((*swapPointer)->leftNode != nullptr)
			{
				swapPointer = &((*swapPointer)->leftNode);
			}
			swapValue = (*swapPointer)->data;
			if((*swapPointer)->rightNode != nullptr)
			{
				(*swapPointer)->data = (*swapPointer)->rightNode->data;
				(*swapPointer) = (*swapPointer)->rightNode;
			}
			else
			{
				(*swapPointer) = nullptr;
			}
			(*targetNode)->data = swapValue;
		}
		else if ((*targetNode)->rightNode == nullptr)
		{
			if(parentNode != targetNode)
			{
				if (location == LEFT)
				{
					(*parentNode)->leftNode = (*targetNode)->leftNode;
				}
				else
				{
					(*parentNode)->rightNode = (*targetNode)->leftNode;
				}
			}
			else
			{
				if (location == LEFT)
				{
					(*parentNode) = (*targetNode)->leftNode;
				}
				else
				{
					(*parentNode) = (*targetNode)->leftNode;
				}
			}
		}
		else if ((*targetNode)->leftNode == nullptr)
		{
			if (parentNode != targetNode)
			{
				if (location == LEFT)
				{
					(*parentNode)->leftNode = (*targetNode)->rightNode;
				}
				else
				{
					(*parentNode)->rightNode = (*targetNode)->rightNode;
				}
			}
			else
			{
				if (location == LEFT)
				{
					(*parentNode) = (*targetNode)->rightNode;
				}
				else
				{
					(*parentNode) = (*targetNode)->rightNode;
				}
			}
		}
}

void deleteNode(shared_ptr<node> *parentNode, shared_ptr<node> *targetNode, int value, int location)
{
	if(*targetNode != nullptr)
	{
		if((*targetNode)->data == value)
		{
			delNod(parentNode, targetNode, location);
			return;
		}
		else
		{
			deleteNode(targetNode, &((*targetNode)->leftNode), value, LEFT);
			deleteNode(targetNode, &((*targetNode)->rightNode), value, RIGHT);
		}
	}
}


int main()
{
	shared_ptr<node> tree = nullptr;
	int value, searchValue;
	for (auto i = 0; i <= 6; i++)
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
	cout << "Insert value for the tree ";
	cin >> searchValue;
	if (searchTree(tree, searchValue))
	{
		cout << "Found!" << endl;
	}
	else
	{
		cout << "Value " << searchValue << " not found." << endl;
	}

	shared_ptr<node> treeCopy = nullptr;
	copyTree(tree, &treeCopy);
	deleteNode(&treeCopy, &treeCopy, 7, 0);
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
