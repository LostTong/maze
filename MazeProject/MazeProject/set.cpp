#include "set.h"


template <typename ValueType>
Set::Set()
{
}

template <typename ValueType>
Set::~Set()
{
}

template <typename ValueType>
void Set::add(const ValueType &value) {
	add_rescusive(value, root);
}

template <typename ValueType>
void Set::add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) {
	// root
	if (cur_node == nullptr) {
		cur_node = new TreeNode<ValueType>(value);
		last = cur_node;
		size += 1;
	}
	else {
		// left
		if (value < cur_node->value) {
			if(cur_node->left == nullptr){
				cur_node->left = new TreeNode<ValueType>(value);
				last = cur_node->left;
				size += 1;
			}
			else{
				add_rescursive(value, cur_node->left);
			}
		}
		// right
		else {
			if(cur_node->right == nullptr){
				cur_node->right = new TreeNode<ValueType>(value);
				last = cur_node->right;
				size += 1;
			}
			else{
				add_rescursive(value, cur_node->right);
			}
		}
	}
}

template <typename ValueType>
bool Set::contain(const ValueType &value) const {
	return contains_recursive(value, root);
}

template <typename ValueType>
bool Set::contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const {
	if (cur_node == nullptr) {
		return false;
	}
	if(value == cur_node->value){
		return true;
	}
	if (value < curr_node->value) {
		return contain_recursive(value, cur_node->left);
	}
	return contain_recursive(value, cur_node->right);
}

template <typename ValueType>
void Set::remove(const ValueType &value) {
	remove_recursive(value, root, nullptr);
}

template <typename ValueType>
void Set::remove_recursive(const ValueType &value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_node){
	if(cur_node != nullptr){
		if(value == cur_node->value){
			size -= 1;
			// left
			if(cur_node->left != nullptr){
				// root
				if(prev_node == nullptr){
					root = curr->left;
				}
				// left
				else if(prev_node->left == cur_node){
					prev_node->left = cur_node->left;
				}
				// right
				else{
					prev_node->right = cur_node->left;
				}

				if(cur_node->right != nullptr){
					cur_node->left->right = cur_node->right;
				}
			}
			// right
			else if(cur_node->right != nullptr){
				// root
				if(prev_node == nullptr){
					root = cur_node->right;
				}
				// left
				else if(prev_node->left == cur_node){
					prev_node->left = cur_node->right;
				}
				// right
				else{
					prev_node->right = curr_node->right;
				}
			}
			// leaf
			else{
				// root
				if(prev_node == nullptr){
					root = nullptr;
				}
				// left
				else if(prev_node->left == curr_node){
					prev_node->left = nullptr;
				}
				// right
				else{
					prev_node->right = nullptr;
				}
			}
		}
		else {
			if(curr_node->value > value){
				remove_recursive(value, cur_node->left, cur_node);
			}
			else{
				remove_recursive(value, cur_node->right, cur_node);
			}
		}
	}
}

template <typename ValueType>
void Set::clear(){
	clear_recursive(root);
}

template <typename ValueType>
void Set::clear_recursive(TreeNode<ValueType> *cur_node){
	if(cur_node == nullptr){
		return;
	}
	if(cur_node->left != nullptr){
		clear_recursive(cur_node->left);
	}
	if(cur_node->right != nullptr){
		clear_recursive(cur_node->right);
	}
	delete curr_node;
}

template <typename ValueType>
TreeNode<ValueType> *Set::get_last_node(){
	return last;
}

template <typename ValueType>
int Set::get_size(){
	return size;
}