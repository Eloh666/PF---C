#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>










//////////////////////////////////////////

void printTreeOrder(node * tree)
{
	if (tree != nullptr)
	{
		printTreeOrder(tree->left);
		std::cout << "Node ->" << tree->data << std::endl;
		printTreeOrder(tree->right);
	}
}

/////////////////////////////////////////

inline void insertNode(node ** tree, int value)
{
	if (*tree == nullptr)
	{
		*tree = new node();
		(*tree)->data = value;
		(*tree)->left = nullptr;
		(*tree)->right = nullptr;
	}
	else if ((*tree)->data < value)
	{
		insertNode(&((*tree)->right), value);
	}
	else if ((*tree)->data > value)
	{
		insertNode(&((*tree)->left), value);
	}
}

inline void copyTree(node * sourceTree, node ** destTree)
{
	if (sourceTree != nullptr)
	{
		*destTree = new node();
		(*destTree)->data = sourceTree->data;
		(*destTree)->left = nullptr;
		(*destTree)->right = nullptr;
		copyTree(sourceTree->left, &((*destTree)->left));
		copyTree(sourceTree->right, &((*destTree)->right));
	}
}

inline void deleteTree(node ** tree)
{
	if (*tree != nullptr)
	{
		deleteTree(&((*tree)->left));
		deleteTree(&((*tree)->right));
		delete *tree;
		*tree = nullptr;
	}
}

inline void getValuesInOrder(node * tree, std::string &results)
{
	if (tree != nullptr)
	{
		getValuesInOrder(tree->left, results);
		if (results != "")
		{
			results += " ";
		}
		results += std::to_string(tree->data);
		getValuesInOrder(tree->right, results);
	}
}

inline void getValuesPostOrder(node * tree, std::string &results)
{
	if (tree != nullptr)
	{
		getValuesPostOrder(tree->left, results);
		getValuesPostOrder(tree->right, results);
		if (results != "")
		{
			results += " ";
		}
		results += std::to_string(tree->data);	
	}
}

inline void getValuesPreOrder(node * tree, std::string &results)
{
	if (tree != nullptr)
	{
		if (results != "")
		{
			results += " ";
		}
		results += std::to_string(tree->data);
		getValuesPreOrder(tree->left, results);
		getValuesPreOrder(tree->right, results);
	}
}

inline std::vector<int> getValuesVector(std::string line, std::string splitOn)
{
	std::vector<int> results;
	auto cString = const_cast<char*>(line.c_str());
	char * token;

	token = strtok(cString, splitOn.c_str());
	while (token != nullptr)
	{
		results.push_back(std::stoi(token));
		token = strtok(nullptr, splitOn.c_str());
	}
	return results;
}

inline bool binarySearch(node * tree, int value)
{
	if (tree == nullptr)
	{
		return false;
	}
	else
	{
		if(tree->data == value)
		{
			return true;
		}
		else
		{
			if(tree->data > value)
			{
				return binarySearch(tree->left, value);
			}
			else
			{
				return binarySearch(tree->right, value);
			}
		}
	}
}

inline node * getLeftmostSon(node * current, node * &parent)
{
	if(current->left == nullptr)
	{
		parent->left = nullptr;
		return current;
	}
	else if (current == parent)
	{
		return getLeftmostSon(current->left, parent);
	}
	else
	{
		return getLeftmostSon(current->left, parent->left);
	}
	
}

inline void linkRightBranch(node * &current, node * toLink)
{
	if(current->right == nullptr)
	{
		current->right = toLink;
	}
	else
	{
		linkRightBranch(current->right, toLink);
	}
}

inline node* deleteNode(node * tree, int value)
{
	if(tree == nullptr)
	{
		return tree;
	}
	else if (tree->data < value)
	{
		tree->right = deleteNode(tree->right, value);
	}
	else if (tree->data > value)
	{
		tree->left = deleteNode(tree->left, value);
	}
	else
	{
		//all brances are null
		if(tree->left == nullptr && tree->right == nullptr)
		{
			delete tree;
			return nullptr;
		}
		//left branch null
		else if (tree->left == nullptr && tree->right != nullptr)
		{
			auto temp = tree->right;
			delete tree;
			tree = nullptr;
			return temp;
		}
		//right branch null
		else if (tree->left != nullptr && tree->right == nullptr)
		{
			auto temp = tree->left;
			delete tree;
			tree = nullptr;
			return temp;
		}
		//no null brances
		else
		{
			auto rightLeftMostSon = getLeftmostSon(tree->right, tree->right);
			if(tree->right != rightLeftMostSon)
			{
				linkRightBranch(rightLeftMostSon, tree->right);
			}
			rightLeftMostSon->left = tree->left;
			
			delete tree;
			tree = nullptr;
			return rightLeftMostSon;
		}
	}
	return tree;
}