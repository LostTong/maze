#include "set.h"


template <typename ValueType>
Set<ValueType>::Set()
{
}

template <typename ValueType>
Set<ValueType>::~Set()
{
	clear();
}

template <typename ValueType>
void Set<ValueType>::add(const ValueType *value) {
	add_rescusive(*value, root);
	value_map[value] = get_size() - 1;
}

template <typename ValueType>
void Set<ValueType>::add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) {
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
				cur_node->left->prev = last;
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
				cur_node->right->prev = last;
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
bool Set<ValueType>::contain(const ValueType *value) const {
	return contain_recursive(*value, root);
}

template <typename ValueType>
bool Set<ValueType>::contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const {
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
void Set<ValueType>::remove(const ValueType *value) {
	remove_recursive(*value, root, nullptr);
}

template <typename ValueType>
void Set<ValueType>::remove_recursive(const ValueType &value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_node){
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
			last = last->prev;
			value_map.erase(&value);
			delete cur_node;
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
void Set<ValueType>::clear(){
	clear_recursive(root);
	root = last = nullptr;
}

template <typename ValueType>
void Set<ValueType>::clear_recursive(const TreeNode<ValueType> *cur_node){
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
TreeNode<ValueType> *Set<ValueType>::get_last_node() const{
	return last;
}

template <typename ValueType>
int Set<ValueType>::get_size() const{
	return size;
}

template <typename ValueType>
TreeNode<ValueType> *Set<ValueType>::pop() {
	if (last == nullptr) {
		return nullptr;
	}
	remove(last->value);
	tmp = last;
	last = last->prev;
	return tmp;
}

template <typename ValueType>
ValueType *Set<ValueType>::get_value(int idx) {
	int tmp = idx % value_map.size();
	return (value_map.begin() + tmp)->first;
}