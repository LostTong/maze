#pragma once

template <typename ValueType>
class TreeNode
{
public:
	TreeNode(const ValueType &value);
	~TreeNode();

	TreeNode<ValueType> *left;
	TreeNode<ValueType> *right;
	TreNode<ValueType> *prev;
	ValueType value;
};

template <typename ValueType>
bool operator < (const TreeNode<ValueType> &left_node, const TreeNode<ValueType> &right_node);

template <typename ValueType>
bool operator == (const TreeNode<ValueType> &left_node, const TreeNode<ValueType> &right_node);


