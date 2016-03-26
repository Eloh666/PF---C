#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS

void insertNode(node ** tree, int value)
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

void copyTree(node * sourceTree, node ** destTree)
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

void deleteTree(node ** tree)
{
	if (*tree != nullptr)
	{
		deleteTree(&((*tree)->left));
		deleteTree(&((*tree)->right));
		delete *tree;
	}
}

void getValuesInOrder(node * tree, std::string &results)
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

std::vector<int> getValuesVector(std::string line, std::string splitOn)
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