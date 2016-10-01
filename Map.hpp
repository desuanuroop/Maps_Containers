#include <iostream>
#include <string>
#include <assert.h>
#include <typeinfo>
#include <stdexcept>

using namespace std;
template<class key_T, class mapped_T>
class treeNode {
	public:
		treeNode *left;
		pair<key_T, mapped_T> data;
		treeNode *right;
		treeNode *parent;
		int heigh, num;
		//Member functions
		treeNode();
		treeNode<key_T, mapped_T>* insert(treeNode<key_T, mapped_T> *, pair<key_T, mapped_T>, int);
		int height(treeNode<key_T, mapped_T> *);
};
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>::treeNode() {
	this->left = NULL;
	this->right = NULL;
	this->parent = NULL;
}
template<class key_T, class mapped_T>
int treeNode<key_T, mapped_T>::height(treeNode<key_T, mapped_T> *node){
	return node==NULL? -1 : node->heigh;
}

template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* treeNode<key_T, mapped_T>::insert(treeNode<key_T, mapped_T> *root, pair<key_T, mapped_T> idata, int count){
	if (root != NULL){
		if(root->data.first < idata.first){ //Right side of tree
			root->right = root->insert(root->right, idata, count);
			root->right->parent = root;
			if(height(root->right) - height(root->left) == 2){
				if(idata.first > root->right->data.first)
					root = rotateWithRightChild(root);
				else
					root = doubleWithRightChild(root);
			}
		}
		else{ //Left side of tree
			root->left = root->insert(root->left, idata, count);
			root->left->parent = root;
			if(height(root->left) - height(root->right) == 2){
				if(idata.first < root->left->data.first)
					root = rotateWithLeftChild(root);
				else
					root = doubleWithLeftChild(root);
			}
		}
	}else {
		root = new treeNode<key_T, mapped_T>();
		root->data = idata;
		root->num = count;
	}
	root->heigh = max(height(root->left), height(root->right)) +1;
	return root;
}
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* rotateWithLeftChild(treeNode<key_T, mapped_T> *pa){
//	cout<<"In rotation 1: "<< pa->data.first<<endl;
//	Change parent
	pa->left->parent = pa->parent;
	pa->parent = pa->left;
//	Changed
	treeNode<key_T, mapped_T> *tempL = pa->left;
	pa->left = tempL->right;
	if (tempL->right != 0){
		tempL->right->parent = pa;
	}
	tempL->right = pa;
	pa->heigh = max(pa->height(pa->left), pa->height(pa->right)) +1 ;
	tempL->heigh = max(tempL->height(tempL->left), pa->heigh) +1;
	return tempL;
}
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* rotateWithRightChild(treeNode<key_T, mapped_T> *pa){
//	cout<<"In rotation 2: "<< pa->data.first<<endl;
//	Change parent
	pa->right->parent = pa->parent;
	pa->parent = pa->right;
//	Changed
	treeNode<key_T, mapped_T> *tempL = pa->right;
	pa->right = tempL->left;
	if(tempL->left != 0){
		tempL->left->parent = pa;
	}
	tempL->left = pa;
	pa->heigh = max(pa->height(pa->left), pa->height(pa->right)) +1;
	tempL->heigh = max(tempL->height(tempL->right), pa->heigh) +1;
	return tempL;
}
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* doubleWithLeftChild(treeNode<key_T, mapped_T> *parent){
//	cout<<"In double with 1"<<endl;
	parent->left = rotateWithRightChild(parent->left);
	return rotateWithLeftChild(parent);
}

template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* doubleWithRightChild(treeNode<key_T, mapped_T> *parent){
//	cout<<"In double with 2"<<endl;
	parent->right = rotateWithLeftChild(parent->right);
	return rotateWithRightChild(parent);
}

template<class key_T, class mapped_T>
class Map_T{
        //Iterator Class
	public:
	class Iterator{
		public:
			key_T first;
			mapped_T second;
			treeNode<key_T, mapped_T> *node;
			Iterator(treeNode<key_T, mapped_T> *);
	};
	//Map_T class memebers.
	treeNode<key_T, mapped_T> *root;
	int count;

	void insert(pair<key_T, mapped_T>);
	treeNode<key_T, mapped_T>* InsertTraversal(treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T>*);

	//Constructor and Assignment Operators
	Map_T();
	Map_T& operator=(const Map_T &);
	Map_T(Map_T<key_T, mapped_T> &);
	void deleteNode(treeNode<key_T, mapped_T> *);
	~Map_T();

        //Size
        size_t size() const;
        bool empty() const{
                return this->count == 0 ? 1:0;
        }

	//Iterator
	Iterator begin(); //Points to first elment in map
	Iterator end();
	Iterator rbegin();//Changes these two to ReverseIterator
	Iterator rend();

        //Element Access
        Iterator find(const key_T &);
        mapped_T& at(const key_T &);
        const mapped_T& at(const key_T &) const;
        mapped_T& operator[](const key_T &);
};

//InnerClass Iterators
template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::Iterator::Iterator(treeNode<key_T, mapped_T> *Node){
	if(Node != NULL){
		this->node = Node;
		this->first = Node->data.first;
		this->second = Node->data.second;
	}else{
		this->node = Node;
		this->first = 0;
		this->second = 0;
	}
}

template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::Map_T(){
//	cout<<"In constructor"<<endl;
	this->count = 0;
	this->root = NULL;
}
//copy constructor
template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::Map_T(Map_T<key_T, mapped_T> &original){
	this->count = 0;
	this->root = NULL;
	this->root = this->InsertTraversal(original.root, this->root);
}

template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* Map_T<key_T, mapped_T>::InsertTraversal(treeNode<key_T, mapped_T> *original, treeNode<key_T, mapped_T> *ro){
	if(original == NULL)
		return NULL;
	InsertTraversal(original->left, this->root);
	this->root = this->root->insert(this->root, original->data, ++this->count);
//	this->count++;
	InsertTraversal(original->right, this->root);
return this->root;
}

template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>& Map_T<key_T, mapped_T>:: operator=(const Map_T<key_T, mapped_T> &rhs){
	this->root = this->InsertTraversal(rhs.root, this->root);
}
template<class key_T, class mapped_T>
void Map_T<key_T, mapped_T>:: insert(pair<key_T, mapped_T> idata){
	this->root = this->root->insert(this->root, idata, ++this->count);
	this->root->heigh = max(this->root->height(this->root->left), this->root->height(this->root->right)) +1;
}

template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::begin(){
//	cout<<"In Begin"<<endl;
	treeNode<key_T, mapped_T> *begin = root;
	while(begin->left != NULL)
		begin = begin->left;
return Iterator(begin);
}

template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::end(){
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->right;
return Iterator(end);
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::rbegin(){
	treeNode<key_T, mapped_T> *begin = root;
	while(begin->right != NULL)
		begin = begin->right;
return Iterator(begin);
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>:: rend(){
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->left;
return Iterator(end);
}

//Element Access
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::find(const key_T &tofind){
	treeNode<key_T, mapped_T> *current = this->root;
	int flag =1;
	while(current){
		if(current->data.first == tofind) {
			flag = 0;
			break;
		}
		else if(current->data.first > tofind)
			current = current->left;
		else
			current = current->right;
	}
	if(flag)
		return this->end();
//		cout<<"Element not found"<<endl;
	else
		return Iterator(current);
}
template<class key_T, class mapped_T>
mapped_T& Map_T<key_T, mapped_T>::at(const key_T &gkey){
	treeNode<key_T, mapped_T> *current = this->root;
	int flag=0;
	while(current){
		if(current->data.first == gkey){
			flag = 1;
			break;
		}else if(current->data.first > gkey)
			current = current->left;
		else
			current = current->right;
	}
	if(flag)
		return current->data.second;
	else
		throw std::out_of_range("Out of bound");
}
template<class key_T, class mapped_T>
const mapped_T& Map_T<key_T, mapped_T>::at(const key_T &gkey) const{
	treeNode<key_T, mapped_T> *current = this->root;
	int flag = 0;
        while(current){
                if(current->data.first == gkey){
                        flag = 1;
                        break;
                }else if(current->data.first > gkey)
                        current = current->left;
                else
                        current = current->right;
        }
        if(flag)
                return current->data.second;
        else
                throw std::out_of_range("Out of bound");

}

template<class key_T, class mapped_T>
mapped_T& Map_T<key_T, mapped_T>::operator[](const key_T &index){
/*	treeNode<key_T, mapped_T> *ref = MorrisTraversal(this->root, index);
	cout<<"Returned is: "<< ref->data.first<<" "<<index<<endl;
	return ref->data.second;

	treeNode<key_T, mapped_T> *current = this->root;
	while(current){
		if(current->num == index)
			return current->data.second;
		else if(current->num < index)
			current = current->right;
		else
			current = current->left;
	}
	this->root = this->root->insert(this->root, make_pair(NULL, NULL), ++this->count);
	return root->data.second;*/
check:
	treeNode<key_T, mapped_T> *current = this->root;
	while(current){
		if(current->data.first == index)
			return current->data.second;
		else if(current->data.first < index)
			current = current->right;
		else
			current = current->left;
	}
	this->root = this->root->insert(this->root, make_pair(index, NULL), ++this->count);
	goto check;
}

//Size
template<class key_T, class mapped_T>
size_t Map_T<key_T, mapped_T>::size() const{
	return this->count;
}

//MOrris Traversal
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* MorrisTraversal(treeNode<key_T, mapped_T> *root, int index){
	int count = 0, flag = 0;
 	treeNode<key_T, mapped_T> *current, *pre;
  	if(root == NULL)
     		return 0;
	current = root;
	while(current != NULL){
    		if(current->left == NULL){
			count++;
			if(count == index)
				return current;
			current = current->right;
    		}else{
      			/* Find the inorder predecessor of current */
			pre = current->left;
			while(pre->right != NULL && pre->right != current)
				pre = pre->right;
		      	/* Make current as right child of its inorder predecessor */
		      	if(pre->right == NULL){
		        	pre->right = current;
		        	current = current->left;
      			}
		      	/* Revert the changes made in if part to restore the original tree i.e., fix the right child of predecssor */
      			else {
			        pre->right = NULL;
				count++;
				if(count == index)
					return current;
			        current = current->right;
			} /* End of if condition pre->right == NULL */
		} /* End of if condition current->left == NULL*/
	} /* End of while */
	return root;
}

template<class key_T, class mapped_T>
void Map_T<key_T, mapped_T>::deleteNode(treeNode<key_T, mapped_T> *node){
	if(node != NULL){
		deleteNode(node->left);
		deleteNode(node->right);
		node->left = NULL;
		node->right = NULL;
		free(node);
	}
}

template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::~Map_T(){
	if(this->root)
		deleteNode(this->root);
}
