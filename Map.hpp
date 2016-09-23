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
		if(root->data.first > idata.first) //Right side of tree
			root = root->insert(root->right, idata);
		else
			root = root->insert(root->left, idata);
	}else {
		root = new treeNode<key_T, mapped_T>();
		root->data = idata;
	}
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
	if (root == 0){
		this->root = new treeNode<key_T, mapped_T>();
		this->root->data = idata;
		size++;
		cout<<"data is: "<<this->root->data.first<<endl;
	}else{
		if (root->)
		this->root->insert(this->root, idata);
		size++;
	}
}
