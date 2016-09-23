#include <iostream>
#include <string>
#include <assert.h>

using namespace std;
template<class key_T, class mapped_T>
class treeNode {
	public:
		treeNode *left;
		pair<key_T, mapped_T> data;
		treeNode *right;
		treeNode<key_T, mapped_T>* insert(treeNode<key_T, mapped_T> *, pair<key_T, mapped_T>);
};
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* treeNode<key_T, mapped_T>::insert(treeNode<key_T, mapped_T> *root, pair<key_T, mapped_T> idata){
	if (root != 0){
		if(root->data.first < idata.first) //Right side of tree
			root->right = root->insert(root->right, idata);
		else
			root->left = root->insert(root->left, idata);
	}else {
		root = new treeNode<key_T, mapped_T>();
		root->data = idata;
	}
	return root;
}

template<class key_T, class mapped_T>
class Map_T{
	public:
		treeNode<key_T, mapped_T> *root;
		int size;
		void insert(pair<key_T, mapped_T>);
};
template<class key_T, class mapped_T>
void Map_T<key_T, mapped_T>:: insert(pair<key_T, mapped_T> idata){
	if (this->size == 0){
		this->root = new treeNode<key_T, mapped_T>();
		this->root->data = idata;
		size++;
	}else{
		if (this->root->data.first < idata.first) {
			this->root->right = this->root->insert(this->root->right, idata);
		}
		else
			this->root->left = this->root->insert(this->root->left, idata);
		size++;
	}
/*	treeNode<key_T, mapped_T> *current = root, *temp;
	if(this->size == 0){
		root = new treeNode<key_T, mapped_T>();
		root->data = idata;
		this->size++;
	}else{
		while(current != 0){
			if (current->data.first > idata.first)
				current = current->right;
			else
				current = current->left;
		}
		temp = new treeNode<key_T, mapped_T>();
		temp->data = idata;
		current = temp;
		this->size++;
	}*/
}
