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
		pair<key_T, mapped_T> *data;
		treeNode *right;
		treeNode *parent;
		int heigh, num;
		//Member functions
		treeNode();
		treeNode<key_T, mapped_T>* insert(treeNode<key_T, mapped_T> *, const pair<key_T, mapped_T>);
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
treeNode<key_T, mapped_T>* treeNode<key_T, mapped_T>::insert(treeNode<key_T, mapped_T> *root, const pair<key_T, mapped_T> idata){
	if (root != NULL){
		if(root->data->first == idata.first){
			throw false;
		}
		if(root->data->first < idata.first){ //Right side of tree
			root->right = root->insert(root->right, idata);
			root->right->parent = root;
			if(height(root->right) - height(root->left) == 2){
				if(idata.first < root->right->data->first)
					root = doubleWithRightChild(root);
				else
					root = rotateWithRightChild(root);
			}
		}
		else{ //Left side of tree
			root->left = root->insert(root->left, idata);
			root->left->parent = root;
			if(height(root->left) - height(root->right) == 2){
				if(idata.first < root->left->data->first)
					root = rotateWithLeftChild(root);
				else
					root = doubleWithLeftChild(root);
			}
		}
	}else {
		//cout<<"New Node is: "<< idata.first<<" "<<idata.second<<endl;
		root = new treeNode<key_T, mapped_T>();
		root->data = new pair<key_T, mapped_T>(idata.first, idata.second);
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
	typedef pair<key_T, mapped_T> valueType;
	class Iterator {
		public:
			key_T first;
			mapped_T second;
			treeNode<key_T, mapped_T> *node;
                        treeNode<key_T, mapped_T> *root;
			treeNode<key_T, mapped_T> *parent;
			//Methods
			Iterator(treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T> *);//constructor
			Iterator& operator++();
			Iterator operator++(int);//postincrement
			Iterator& operator--();
			Iterator operator--(int);//postdecrement
			valueType& operator*() const;
			valueType* operator->() const;
			void assign(treeNode<key_T, mapped_T> *);
	};
	class ConstIterator{
		public:
			key_T first;
			mapped_T second;
		private:
			const treeNode<key_T, mapped_T> *node;
                        treeNode<key_T, mapped_T> *root;
			treeNode<key_T, mapped_T> *parent;
			//Methods
		public:
			ConstIterator(const Iterator &);
			ConstIterator(const treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T> *);//constructor
			ConstIterator& operator++();
			ConstIterator operator++(int);//postincrement
			ConstIterator& operator--();
			ConstIterator operator--(int);//postdecrement
			const valueType& operator*() const;
			const valueType* operator->() const;
			void assign(treeNode<key_T, mapped_T> *);
	};
	//Map_T class memebers.
	treeNode<key_T, mapped_T> *root;
	int count;

	pair<Iterator, bool> insert(const pair<key_T, mapped_T>);
	treeNode<key_T, mapped_T>* InsertTraversal(treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T>*);

	//Constructor and Assignment Operators
	Map_T();
	Map_T& operator=(const Map_T &);
	Map_T(const Map_T<key_T, mapped_T> &);
	void erase(const key_T &);
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

	//ConstIterator
	ConstIterator begin() const;
	ConstIterator end() const;

        //Element Access
        Iterator find(const key_T &);
        mapped_T& at(const key_T &);
        const mapped_T& at(const key_T &) const;
        mapped_T& operator[](const key_T &);
};

//Map methods
template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::Map_T(){
//	cout<<"In constructor"<<endl;
	this->count = 0;
	this->root = NULL;
}
//copy constructor
template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::Map_T(const Map_T<key_T, mapped_T> &original){
	this->count = 0;
	this->root = NULL;
	this->root = this->InsertTraversal(original.root, this->root);
	indexing(this->root, 0);
}

template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* Map_T<key_T, mapped_T>::InsertTraversal(treeNode<key_T, mapped_T> *original, treeNode<key_T, mapped_T> *ro){
	if(original == NULL)
		return NULL;
	InsertTraversal(original->left, this->root);
	this->root = this->root->insert(this->root, *original->data);
	this->count++;
	InsertTraversal(original->right, this->root);
return this->root;
}

template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>& Map_T<key_T, mapped_T>:: operator=(const Map_T<key_T, mapped_T> &rhs){
	this->root = this->InsertTraversal(rhs.root, this->root);
	indexing(this->root, 0);
}

template<class key_T, class mapped_T>
pair<typename Map_T<key_T, mapped_T>::Iterator, bool> Map_T<key_T, mapped_T>::insert(const pair<key_T, mapped_T> idata){
	try{
		this->root = this->root->insert(this->root, idata);
		this->count++;
		this->root->heigh = max(this->root->height(this->root->left), this->root->height(this->root->right)) +1;
		indexing(this->root, 0);
	}catch(bool ret){
		Iterator alr = this->find(idata.first);
		return make_pair(alr, false);
	}
	Iterator alr = this->find(idata.first);
	return make_pair(alr, true);
}
//Helper
template<class key_T, class mapped_T>
int indexing(treeNode<key_T, mapped_T> *root, int n){
	if(root == NULL)
		return n;
	n = indexing(root->left, n);
	root->num = ++n;
	n = indexing(root->right, n);
	return n;
}
template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::begin(){
//	cout<<"In Begin"<<endl;
	treeNode<key_T, mapped_T> *begin = root;
	while(begin->left != NULL)
		begin = begin->left;
return Iterator(begin, this->root);
}

template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::end(){
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->right;
return Iterator(end, this->root);
}

template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::ConstIterator Map_T<key_T, mapped_T>::begin() const{
	cout<<"In const beegin"<<endl;
	treeNode<key_T, mapped_T> *begin = root;
	while(begin->left != NULL)
		begin = begin->left;
	Iterator it(begin, this->root);
return ConstIterator(it);
}

template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::ConstIterator Map_T<key_T, mapped_T>::end() const{
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->right;
	Iterator it(end, this->root);
return ConstIterator(it, it.node);
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::rbegin(){
	treeNode<key_T, mapped_T> *begin = root;
	while(begin->right != NULL)
		begin = begin->right;
return Iterator(begin, this->root);
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>:: rend(){
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->left;
return Iterator(end, this->root);
}

//Element Access
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::find(const key_T &tofind){
	treeNode<key_T, mapped_T> *current = this->root;
	int flag =1;
	while(current){
		if(current->data->first == tofind) {
			flag = 0;
			break;
		}
		else if(current->data->first > tofind)
			current = current->left;
		else
			current = current->right;
	}
	if(flag)
		return this->end();
//		cout<<"Element not found"<<endl;
	else
		return Iterator(current, this->root);
}
template<class key_T, class mapped_T>
mapped_T& Map_T<key_T, mapped_T>::at(const key_T &gkey){
	treeNode<key_T, mapped_T> *current = this->root;
	int flag=0;
	while(current){
		if(current->data->first == gkey){
			flag = 1;
			break;
		}else if(current->data->first > gkey)
			current = current->left;
		else
			current = current->right;
	}
	if(flag)
		return current->data->second;
	else
		throw std::out_of_range("Out of bound");
}
template<class key_T, class mapped_T>
const mapped_T& Map_T<key_T, mapped_T>::at(const key_T &gkey) const{
	treeNode<key_T, mapped_T> *current = this->root;
	int flag = 0;
        while(current){
                if(current->data->first == gkey){
                        flag = 1;
                        break;
                }else if(current->data->first > gkey)
                        current = current->left;
                else
                        current = current->right;
        }
        if(flag)
                return current->data->second;
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
		if(current->data->first == index)
			return current->data->second;
		else if(current->data->first < index)
			current = current->right;
		else
			current = current->left;
	}
	pair<key_T, mapped_T> p = make_pair(index, NULL);
	this->root = this->root->insert(this->root, p);
	this->count++;
	goto check;
}

//Size
template<class key_T, class mapped_T>
size_t Map_T<key_T, mapped_T>::size() const{
	return this->count;
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

//InnerClass Iterators
template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::Iterator::Iterator(treeNode<key_T, mapped_T> *Node, treeNode<key_T, mapped_T> *root){
        this->root = root;
	if(Node != NULL){
		this->node = Node;
		this->first = Node->data->first;
		this->second = Node->data->second;
	}else{
		this->node = Node;
		this->first = 0;
		this->second = 0;
	}
}
//Helper to find required indexec node
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* findNum(treeNode<key_T, mapped_T> *root, int index){
	treeNode<key_T, mapped_T> *current = root;
        while(current){
                if(current->num == index)
                        break;
                else if(current->num > index)
                        current = current->left;
                else
                        current = current->right;
        }
	return current;
}
template<class key_T, class mapped_T>
void Map_T<key_T, mapped_T>::Iterator::assign(treeNode<key_T, mapped_T> *current){
	this->node = current;
        if(current){
                this->first = current->data->first;
                this->second = current->data->second;
        }
        else {
                this->first = 0;
                this->second = 0;
        }
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator& Map_T<key_T, mapped_T>::Iterator::operator++(){//preincrement
	treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
	assign(current);
	return *this;
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::Iterator::operator++(int x){ //postincrement
	Map_T<key_T, mapped_T>::Iterator haveToReturn(this->node, this->root);
	treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
	assign(current);
	return haveToReturn;
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator& Map_T<key_T, mapped_T>::Iterator::operator--(){//predecrement
	treeNode<key_T, mapped_T> *current = findNum(root, node->num-1);
	assign(current);
	return *this;
}
template<class key_T, class mapped_T>
typename Map_T<key_T, mapped_T>::Iterator Map_T<key_T, mapped_T>::Iterator::operator--(int x){ //postincrement
        Map_T<key_T, mapped_T>::Iterator havetoReturn(this->node, this->root);
        treeNode<key_T, mapped_T> *current = findNum(root, node->num-1);
        assign(current);
        return havetoReturn;
}
template<class key_T, class mapped_T>
pair<key_T, mapped_T>& Map_T<key_T, mapped_T>::Iterator::operator*() const{
	return *node->data;
}
template<typename key_T, typename mapped_T>
pair<key_T, mapped_T>* Map_T<key_T, mapped_T>::Iterator::operator->() const{
	return node->data;
}
//ConstIterator Class
//constructor
template<typename key_T, typename mapped_T>
Map_T<key_T, mapped_T>::ConstIterator::ConstIterator(const treeNode<key_T, mapped_T> *Node, treeNode<key_T, mapped_T> *root){
        this->root = root;
        if(Node != NULL){
                this->node = Node;
                this->first = Node->data->first;
                this->second = Node->data->second;
        }else{
                this->node = Node;
                this->first = 0;
                this->second = 0;
        }
}

//Conversion from Iterator to ConstIterator
template<class key_T, class mapped_T>
Map_T<key_T, mapped_T>::ConstIterator::ConstIterator(const Map_T<key_T, mapped_T>::Iterator &it){
	this->root = it.root;
	if(it.node != NULL){
		this->node = it.node;
		this->first = it.node->data->first;
		this->second = it.node->data->second;
	}else{
		this->node = it.node;
		this->first = 0;
		this->second = 0;
	}
}
template<class key_T, class mapped_T>
void Map_T<key_T, mapped_T>::ConstIterator::assign(treeNode<key_T, mapped_T> *current){
	this->node = current;
        if(current){
                this->first = current->data->first;
                this->second = current->data->second;
        }
        else {
                this->first = 0;
                this->second = 0;
        }
}

template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::ConstIterator& Map_T<key_T, mapped_T>::ConstIterator::operator++(){//preincrement
	treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
	assign(current);
	return *this;
}
template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::ConstIterator Map_T<key_T, mapped_T>::ConstIterator::operator++(int z){//postincrement
        Map_T<key_T, mapped_T>::ConstIterator haveToReturn(this->node, this->root);
        treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
        assign(current);
        return haveToReturn;
}
template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::ConstIterator& Map_T<key_T, mapped_T>::ConstIterator::operator--(){//predecrement
        treeNode<key_T, mapped_T> *current = findNum(root, node->num-1);
        assign(current);
        return *this;
}
template<typename key_T, typename mapped_T>
typename Map_T<key_T, mapped_T>::ConstIterator Map_T<key_T, mapped_T>::ConstIterator::operator--(int z){//postdecrement
        Map_T<key_T, mapped_T>::ConstIterator haveToReturn(this->node, this->root);
        treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
        assign(current);
        return haveToReturn;
}
template<typename key_T, typename mapped_T>
const pair<key_T, mapped_T>& Map_T<key_T, mapped_T>::ConstIterator::operator*() const{
        return *node->data;
}
template<typename key_T, typename mapped_T>
const pair<key_T, mapped_T>* Map_T<key_T, mapped_T>::ConstIterator::operator->() const{
	return node->data;
}
