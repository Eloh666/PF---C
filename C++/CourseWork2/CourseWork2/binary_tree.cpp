#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "binary_tree.h"
#include "treeFunctions.h"


// Creates an empty binary tree
binary_tree::binary_tree()
{

}

// Creates a binary tree with an initial value to store
binary_tree::binary_tree(int value)
{
	insertNode(&tree, value);
}

// Creates a binary tree from a collection of existing values
binary_tree::binary_tree(const std::vector<int> &values)
{
	for(auto i : values)
	{
		insertNode(&tree, i);
	}
}

// Creates a binary tree by copying an existing tree
binary_tree::binary_tree(const binary_tree &rhs)
{
	for (auto i : getValuesVector(rhs.inorder()," "))
	{
		insertNode(&tree, i);
	}
}

// Destroys (cleans up) the tree
binary_tree::~binary_tree()
{
	deleteTree(&tree);
}

// Adds a value to the tree
void binary_tree::insert(int value)
{
	insertNode(&tree, value);
}

// Removes a value from the tree
void binary_tree::remove(int value)
{
	tree = deleteNode(tree, value);
}

// Checks if a value is in the tree
bool binary_tree::exists(int value) const
{
	return binarySearch(tree, value);;
}

// Prints the tree to standard out in numerical order
std::string binary_tree::inorder() const
{
	std::string inOrder;
	getValuesInOrder(tree, inOrder);
	return inOrder;
}

// Prints the tree in pre-order
std::string binary_tree::preorder() const
{
	std::string preOrder;
	getValuesPreOrder(tree, preOrder);
	return preOrder;
}

// Prints the tree in post-order
std::string binary_tree::postorder() const
{
	std::string postOrder;
	getValuesPostOrder(tree, postOrder);
	return postOrder;
}

// Copy assignment operator
binary_tree& binary_tree::operator=(const binary_tree &other)
{
	auto values = getValuesVector(other.inorder(), " ");
	deleteTree(&tree);
	for (auto i : values)
	{
		insertNode(&tree, i);
	}
	return *this;
}

// Checks if two trees are equal
bool binary_tree::operator==(const binary_tree &other) const
{
	return (inorder() == other.inorder()) && (preorder() == other.preorder()) && (postorder() == other.postorder());
}

// Checks if two trees are not equal
bool binary_tree::operator!=(const binary_tree &other) const
{
	return !(inorder() == other.inorder()) && (preorder() == other.preorder()) && (postorder() == other.postorder());
}

// Inserts a new value into the binary tree
binary_tree& binary_tree::operator+(int value)
{
	insertNode(&tree, value);
	return *this;
}

// Removes a value from the binary tree
binary_tree& binary_tree::operator-(int value)
{
	deleteNode(tree, value);
	return *this;
}

// Reads in values from an input stream into the tree
std::istream& operator>>(std::istream &in, binary_tree &value)
{
	std::string treeValues(std::istreambuf_iterator<char>(in), {});
	auto newTreeValues= getValuesVector(treeValues, " ");
	for(auto i : newTreeValues)
	{
		value.insert(i);
	}
	return in;
}

// Writes the values, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const binary_tree &value)
{
	auto treeValues = value.inorder();
	out << treeValues;
	return out;
}
