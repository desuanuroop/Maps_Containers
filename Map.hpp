#include <iostream>
#include <string>
#include <assert.h>
#include <typeinfo>
#include <stdexcept>
#include <utility>
namespace cs540 {
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
class Map{
        //Iterator Class
	public:
	typedef pair<key_T, mapped_T> valueType;
	class IteratorMembers{
		public:
			treeNode<key_T, mapped_T> *node;
			treeNode<key_T, mapped_T> *root;
			treeNode<key_T, mapped_T> *parent;
			IteratorMembers(){};
			void assign(treeNode<key_T, mapped_T> *);
	};
	class Iterator:public IteratorMembers {
		public:
/*			key_T first;
			mapped_T second;
			treeNode<key_T, mapped_T> *node;
                        treeNode<key_T, mapped_T> *root;
			treeNode<key_T, mapped_T> *parent;*/
			//Methods
			Iterator(treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T> *);//constructor
			Iterator& operator++();
			Iterator operator++(int);//postincrement
			Iterator& operator--();
			Iterator operator--(int);//postdecrement
			valueType& operator*() const;
			valueType* operator->() const;
//			void assign(treeNode<key_T, mapped_T> *);
	};
	class ConstIterator{
		public:
			const treeNode<key_T, mapped_T> *node;
                        treeNode<key_T, mapped_T> *root;
			treeNode<key_T, mapped_T> *parent;
			//Methods
		public:
			ConstIterator(const Iterator &);//conversion
			ConstIterator(const treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T> *);//constructor
			ConstIterator& operator++();
			ConstIterator operator++(int);//postincrement
			ConstIterator& operator--();
			ConstIterator operator--(int);//postdecrement
			const valueType& operator*() const;
			const valueType* operator->() const;
			void assign(treeNode<key_T, mapped_T> *);
	};
	class ReverseIterator: public IteratorMembers{
		public:
                        ReverseIterator(treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T> *);//constructor
			ReverseIterator& operator++();
			ReverseIterator operator++(int);
			ReverseIterator& operator--();
			ReverseIterator operator--(int);
			valueType& operator*()const;
			valueType *operator->()const;
//			void assign(treeNode<key_T, mapped_T> *);
	};
	//Map class memebers.
	treeNode<key_T, mapped_T> *root;
	int count;
	template<class IT_T>
	void insert(IT_T begin, IT_T end){
		for(IT_T current = begin; current != end; current++){
			this->insert(*current);
		}

	}
	pair<Iterator, bool> insert(const pair<key_T, mapped_T>);
	treeNode<key_T, mapped_T>* InsertTraversal(treeNode<key_T, mapped_T> *, treeNode<key_T, mapped_T>*);

	//Constructor and Assignment Operators
	Map();
	Map& operator=(const Map &);
	Map(const Map<key_T, mapped_T> &);
	Map(std::initializer_list<std::pair<const key_T, mapped_T>>);
	void erase(const key_T &);
	void erase(Iterator pos);
	void clear();
	treeNode<key_T, mapped_T>* delNode(treeNode<key_T, mapped_T> *, const key_T &);
	void deleteNode(treeNode<key_T, mapped_T> *);
	~Map();

        //Size
        size_t size() const;
        bool empty() const{
                return this->count == 0 ? 1:0;
        }

	//Iterator
	Iterator begin(); //Points to first elment in map
	Iterator end();

	//ConstIterator
	ConstIterator begin() const;
	ConstIterator end() const;

	//ReverseIterator
	ReverseIterator rbegin();
	ReverseIterator rend();

        //Element Access
        Iterator find(const key_T &);
	ConstIterator find(const key_T &)const;
        mapped_T& at(const key_T &);
        const mapped_T& at(const key_T &) const;
        mapped_T& operator[](const key_T &);

	//iterators Comparisons
	friend bool operator==(const Iterator &i1,const Iterator &i2){
		return(i1.node == i2.node);
	}
        friend bool operator==(const ConstIterator &i1,const ConstIterator &i2){
		return(i1.node == i2.node);
        }

	friend bool operator==(const ConstIterator &i1, const Iterator &i2){
		return(i1.node == i2.node);
	}
	friend bool operator==(const Iterator &i1, const ConstIterator &i2){
		return(i1.node == i2.node);
	}
 	friend bool operator!=(const Iterator &i1,const Iterator &i2){
                return(i1.node != i2.node);
        }
        friend bool operator!=(const ConstIterator &i1,const ConstIterator &i2){
                return(i1.node != i2.node);
        }
        friend bool operator!=(const ConstIterator &i1, const Iterator &i2){
                return(i1.node != i2.node);
        }
        friend bool operator!=(const Iterator &i1, const ConstIterator &i2){
                return(i1.node != i2.node);
        }
        friend bool operator==(const ReverseIterator &i1,const ReverseIterator &i2){
                return(i1.node == i2.node);
        }
	friend bool operator!=(const ReverseIterator &i1, const ReverseIterator &i2){
		return(i1.node != i2.node);
	}
};

//Map methods
template<class key_T, class mapped_T>
Map<key_T, mapped_T>::Map(){
	this->count = 0;
	this->root = 0;
}
//copy constructor
template<class key_T, class mapped_T>
Map<key_T, mapped_T>::Map(const Map<key_T, mapped_T> &original){
	this->count = 0;
	this->root = NULL;
	this->root = this->InsertTraversal(original.root, this->root);
	indexing(this->root, 0);
}

template<typename key_T, typename mapped_T>
Map<key_T, mapped_T>::Map(std::initializer_list<std::pair<const key_T, mapped_T>> lis){
	this->root = NULL;
	typename std::initializer_list<std::pair<const key_T, mapped_T>>::const_iterator it;
	for (it=lis.begin(); it!=lis.end(); ++it){
		this->insert(make_pair(get<0>(*it), get<1>(*it)));
	}
}
template<class key_T, class mapped_T>
treeNode<key_T, mapped_T>* Map<key_T, mapped_T>::InsertTraversal(treeNode<key_T, mapped_T> *original, treeNode<key_T, mapped_T> *ro){
	if(original == NULL)
		return NULL;
	InsertTraversal(original->left, this->root);
	this->root = this->root->insert(this->root, *original->data);
	this->count++;
	InsertTraversal(original->right, this->root);
return this->root;
}

template<class key_T, class mapped_T>
Map<key_T, mapped_T>& Map<key_T, mapped_T>:: operator=(const Map<key_T, mapped_T> &rhs){
	this->root = this->InsertTraversal(rhs.root, this->root);
	indexing(this->root, 0);
}

template<class key_T, class mapped_T>
pair<typename Map<key_T, mapped_T>::Iterator, bool> Map<key_T, mapped_T>::insert(const pair<key_T, mapped_T> idata){
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
	root->num = n++;
	n = indexing(root->right, n);
	return n;
}
template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::Iterator Map<key_T, mapped_T>::begin(){
	treeNode<key_T, mapped_T> *begin = root;
	while(begin != NULL && begin->left != NULL)
		begin = begin->left;
return Iterator(begin, this->root);
}

template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::Iterator Map<key_T, mapped_T>::end(){
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->right;
return Iterator(end, this->root);
}

template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator Map<key_T, mapped_T>::begin() const{
	treeNode<key_T, mapped_T> *begin = root;
	while(begin != NULL && begin->left != NULL)
		begin = begin->left;
	Iterator it(begin, this->root);
return ConstIterator(it);
}

template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator Map<key_T, mapped_T>::end() const{
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->right;
	Iterator it(end, this->root);
return ConstIterator(it);
}
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::ReverseIterator Map<key_T, mapped_T>::rbegin(){
	treeNode<key_T, mapped_T> *begin = root;
	while(begin != NULL && begin->right != NULL)
		begin = begin->right;
return ReverseIterator(begin, this->root);
}
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::ReverseIterator Map<key_T, mapped_T>:: rend(){
	treeNode<key_T, mapped_T> *end = root;
	while(end != NULL)
		end = end->left;
return ReverseIterator(end, this->root);
}

//Element Access
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::Iterator Map<key_T, mapped_T>::find(const key_T &tofind){
	treeNode<key_T, mapped_T> *current = this->root;
	int flag =1;
	while(current){
		if(current->data->first == tofind) {
			flag = 0;
			break;
		}
		else if(current->data->first < tofind)
			current = current->right;
		else
			current = current->left;
	}
	if(flag)
		return this->end();
	else
		return Iterator(current, this->root);
}

template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator Map<key_T, mapped_T>::find(const key_T &tofind) const{
        treeNode<key_T, mapped_T> *current = this->root;
        int flag =1;
        while(current){
                if(current->data->first == tofind) {
                        flag = 0;
                        break;
                }
                else if(current->data->first < tofind)
                        current = current->right;
                else
                        current = current->left;
        }
        if(flag)
                return this->end();
        else
                return ConstIterator(current, this->root);
}
template<class key_T, class mapped_T>
mapped_T& Map<key_T, mapped_T>::at(const key_T &gkey){
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
const mapped_T& Map<key_T, mapped_T>::at(const key_T &gkey) const{
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
mapped_T& Map<key_T, mapped_T>::operator[](const key_T &index){
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
	indexing(this->root, 0);
	goto check;
}

template<class key_T, class mapped_T>
size_t Map<key_T, mapped_T>::size() const{
	return this->count;
}
template<typename key_T, typename mapped_T>
void Map<key_T, mapped_T>::clear(){
	if(this->root)
		deleteNode(this->root);
	this->root=NULL;
}
template<typename key_T, typename mapped_T>
void Map<key_T, mapped_T>::erase(const key_T& delKeyNode){
	treeNode<key_T, mapped_T> *current = this->root;
	while(current){
		if(current->data->first == delKeyNode){
/*			if(!current->left && !current->right && !current->parent){
				this->root = NULL;
				delete current->data;
				delete current;
				this->count--;
			}else{*/
				 this->root = delNode(this->root, delKeyNode);
				indexing(this->root, 0);
				this->count--;
			return;
		}
		else if(current->data->first < delKeyNode)
			current = current->right;
		else
			current = current->left;
	}
	throw std::out_of_range("Not in map");
}
template<typename key_T, typename mapped_T>
void Map<key_T, mapped_T>::erase(Iterator pos){
	if(pos.node)
		this->erase(pos->first);
}
template<typename key_T, typename mapped_T>
treeNode<key_T, mapped_T>* Map<key_T, mapped_T>::delNode(treeNode<key_T, mapped_T> *rootN, const key_T &key){
	if(rootN == NULL)
		return rootN;
	if(rootN->data->first < key)
		rootN->right = delNode(rootN->right, key);
	else if(key < rootN->data->first)
		rootN->left = delNode(rootN->left, key);
	else{
		if(rootN->left == NULL){
			treeNode<key_T, mapped_T> *temp = rootN->right;
			delete rootN->data;
			delete rootN;
			return temp;
		}else if(rootN->right == NULL){
			treeNode<key_T, mapped_T> *temp = rootN->left;
			delete rootN->data;
			delete rootN;
			return temp;
		}
		treeNode<key_T, mapped_T>* temp = findNum(this->root, rootN->num+1);
		delete rootN->data;
		rootN->data = temp->data;
		rootN->right = delNode(rootN->right, temp->data->first);
	}
	return rootN;
}/*
template<typename key_T, typename mapped_T>
void delNode(treeNode<key_T, mapped_T> *node){
	if(!node->left && !node->right){
		if(node->parent->data->first < node->data->first)
			node->parent->right = NULL;
		else
			node->parent->left = NULL;
		delete node->data;
		delete node;
	}else if(!node->left){//noleft subtree
		if(!node->parent){ //deleting root node
			treeNode<key_T, mapped_T> *current = node->right;
			while(current->left)
				current = current->left;
//			node->num = current->num;
			if(current->parent->data->first < current->data->first)
				current->parent->right = current->right;
			else
				current->parent->left = current->right; //changed to right.
			if(current->right)//2.40
				current->right->parent = current->parent;
			delete node->data;//now 1:07
			node->data = current->data;//now 1:07
			delete current;
		}else{
			if(node->parent->data->first < node->data->first)
				node->parent->right = node->right;
			else
				node->parent->left = node->right;
			if(node->right)//2.40
				node->right->parent = node->parent;
			delete node->data;
			delete node;
		}
	}else if(!node->right){//noright subtree
		if(!node->parent){	//deleting root node
			treeNode<key_T, mapped_T> *current = node->left;
			while(current->right)
				current = current->right;
//			node->num = current->num;
			if(current->parent->data->first < current->data->first)
				current->parent->right = current->left; //2.49 changed from right to left
			else
				current->parent->left = current->left;//2.49 changed from right to left.
			if(current->left)
				current->left->parent = current->parent;
			delete node->data;
			node->data = current->data;
			delete current;
		}
		else{
			if(node->parent->data->first < node->data->first)
				node->parent->right = node->left;
 			else
				node->parent->left = node->left;
			if(node->left)//2.40
				node->left->parent = node->parent;
			delete node->data;
			delete node; //no use of this node.
		}
	}
	else{ //writing to same node. chaging data point
		treeNode<key_T, mapped_T> *current = node->right;
		while(current->left)
			current = current->left;
		if(current->parent->data->first < current->data->first){
			current->parent->right = current->right;
			if(current->right)
				current->right->parent = current->parent;
		}
		else{
			current->parent->left = current->left;
			if(current->left)
				current->left->parent = current->parent;
		}
//		current->parent->left = NULL;
		delete node->data;
		node->data = current->data;
		delete current;
	}//two childs
}*/
template<class key_T, class mapped_T>
void Map<key_T, mapped_T>::deleteNode(treeNode<key_T, mapped_T> *node){
	if(node != NULL){
		deleteNode(node->left);
		deleteNode(node->right);
		delete node->data;
		delete node;
	}
}

template<class key_T, class mapped_T>
Map<key_T, mapped_T>::~Map(){
	if(this->root)
		deleteNode(this->root);
}
//Comparators of map
template<typename key_T, typename mapped_T>
bool operator==(const Map<key_T, mapped_T> &map, const Map<key_T, mapped_T> &map2){
	int size = map.size();
	if(map.size() != map2.size())
		return false;
	else{
		for(int i=0;i<size;i++){
			treeNode<key_T, mapped_T> *node1 = findNum(map.root, i);
			treeNode<key_T, mapped_T> *node2 = findNum(map2.root, i);
			if((node1 == NULL || node2 == NULL) || (*node1->data != *node2->data))
				return false;
		}
	}
	return true;
}
template<typename key_T, typename mapped_T>
bool operator!=(const Map<key_T, mapped_T> &map, const Map<key_T, mapped_T> &map2){
	return !(map == map2);
}

template<typename key_T, typename mapped_T>
bool operator<(const Map<key_T, mapped_T> &map, const Map<key_T, mapped_T> &map2){
	if(map.size() >= map2.size())
		return false;
	else{
		for(int i=0;i<map.size(); i++){
			treeNode<key_T, mapped_T> *node1 = findNum(map.root, i);
			treeNode<key_T, mapped_T> *node2 = findNum(map2.root, i);
			if(node1->data < node2->data)
				return true;
		}
		return true;
	}
}
//InnerClass Iterators
template<class key_T, class mapped_T>
Map<key_T, mapped_T>::Iterator::Iterator(treeNode<key_T, mapped_T> *Node, treeNode<key_T, mapped_T> *root){
        this->root = root;
	this->node = Node;
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
void Map<key_T, mapped_T>::IteratorMembers::assign(treeNode<key_T, mapped_T> *current){
	this->node = current;
}
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::Iterator& Map<key_T, mapped_T>::Iterator::operator++(){//preincrement
	treeNode<key_T, mapped_T> *current;
	if(this->node == 0){
//		cout<<"Incrementing las position"<<endl;
		return *this;
//		current = findNum(this->root, this->root->num);
	}
	else
		current = findNum(this->root, this->node->num+1);
	this->assign(current);
	return *this;
}
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::Iterator Map<key_T, mapped_T>::Iterator::operator++(int x){ //postincrement
	Map<key_T, mapped_T>::Iterator haveToReturn(this->node, this->root);
	if(this->node == 0)
		return haveToReturn;
	else{
		treeNode<key_T, mapped_T> *current = findNum(this->root, this->node->num+1);
		this->assign(current);
		return haveToReturn;
	}
}
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::Iterator& Map<key_T, mapped_T>::Iterator::operator--(){//predecrement
	treeNode<key_T, mapped_T> *current;
	if(this->node == 0)
//		return *this;
		current= findNum(this->root, this->root->num+1);
	else
		current = findNum(this->root, this->node->num-1);
	this->assign(current);
	return *this;
}
template<class key_T, class mapped_T>
typename Map<key_T, mapped_T>::Iterator Map<key_T, mapped_T>::Iterator::operator--(int x){ //postdeccrement
        Map<key_T, mapped_T>::Iterator havetoReturn(this->node, this->root);
	treeNode<key_T, mapped_T> *current;
	if(this->node == 0)
//		return havetoReturn;
		current = findNum(this->root, this->root->num+1);
	else
		current = findNum(this->root, this->node->num-1);
        this->assign(current);
        return havetoReturn;
}
template<class key_T, class mapped_T>
pair<key_T, mapped_T>& Map<key_T, mapped_T>::Iterator::operator*() const{
//	assert(1 == 1);
	return *this->node->data;
}
template<typename key_T, typename mapped_T>
pair<key_T, mapped_T>* Map<key_T, mapped_T>::Iterator::operator->() const{
	return this->node->data;
}
//ConstIterator Class
//constructor
template<typename key_T, typename mapped_T>
Map<key_T, mapped_T>::ConstIterator::ConstIterator(const treeNode<key_T, mapped_T> *Node, treeNode<key_T, mapped_T> *root){
        this->root = root;
        this->node = Node;
}

//Conversion from Iterator to ConstIterator
template<class key_T, class mapped_T>
Map<key_T, mapped_T>::ConstIterator::ConstIterator(const Map<key_T, mapped_T>::Iterator &it){
	this->root = it.root;
	this->node = it.node;
}
template<class key_T, class mapped_T>
void Map<key_T, mapped_T>::ConstIterator::assign(treeNode<key_T, mapped_T> *current){
	this->node = current;
}

template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator& Map<key_T, mapped_T>::ConstIterator::operator++(){//preincrement
	if(this->node == 0)
		return *this;
	else{
		treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
		assign(current);
		return *this;
	}
}
template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator Map<key_T, mapped_T>::ConstIterator::operator++(int z){//postincrement
        Map<key_T, mapped_T>::ConstIterator haveToReturn(this->node, this->root);
	if(this->node == 0){
		return haveToReturn;
	}else{
	        treeNode<key_T, mapped_T> *current = findNum(root, node->num+1);
        	assign(current);
	        return haveToReturn;
	}
}
template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator& Map<key_T, mapped_T>::ConstIterator::operator--(){//predecrement
	treeNode<key_T, mapped_T> *current;
        if(this->node == 0)
		return *this;
//                current= findNum(this->root, this->root->num+1);
        else
                current = findNum(this->root, this->node->num-1);
        assign(current);
        return *this;
}
template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ConstIterator Map<key_T, mapped_T>::ConstIterator::operator--(int z){//postdecrement
        Map<key_T, mapped_T>::ConstIterator haveToReturn(this->node, this->root);
	treeNode<key_T, mapped_T> *current;
        if(this->node == 0)
//		return haveToReturn;
                current= findNum(this->root, this->root->num+1);
        else
                current = findNum(this->root, this->node->num-1);

        assign(current);
        return haveToReturn;
}
template<typename key_T, typename mapped_T>
const pair<key_T, mapped_T>& Map<key_T, mapped_T>::ConstIterator::operator*() const{
        return *node->data;
}
template<typename key_T, typename mapped_T>
const pair<key_T, mapped_T>* Map<key_T, mapped_T>::ConstIterator::operator->() const{
	return node->data;
}

//ReverseIterator
template<typename key_T, typename mapped_T>
Map<key_T, mapped_T>::ReverseIterator::ReverseIterator(treeNode<key_T, mapped_T> *Node, treeNode<key_T, mapped_T> *root){
        this->root = root;
        this->node = Node;
}
template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ReverseIterator& Map<key_T, mapped_T>::ReverseIterator::operator++(){ //since it is reverse, write code as pree decrement.
	if(this->node == 0)
		return *this;
	else{
		treeNode<key_T, mapped_T> *current = findNum(this->root, this->node->num-1);
		this->assign(current);
		return *this;
	}
}

template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ReverseIterator Map<key_T, mapped_T>::ReverseIterator::operator++(int x){//code as post decrement
        Map<key_T, mapped_T>::ReverseIterator haveToReturn(this->node, this->root);
	if(this->node == 0)
		return haveToReturn;
	else{
		treeNode<key_T, mapped_T> *current = findNum(this->root, this->node->num-1);
		this->assign(current);
		return haveToReturn;
	}
}
template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ReverseIterator& Map<key_T, mapped_T>::ReverseIterator::operator--(){ //since it is reverse, write code as pree decrement.
	if(this->node == 0)
		return *this;
	else{
	        treeNode<key_T, mapped_T> *current = findNum(this->root, this->node->num+1);
        	this->assign(current);
	        return *this;
	}
}

template<typename key_T, typename mapped_T>
typename Map<key_T, mapped_T>::ReverseIterator Map<key_T, mapped_T>::ReverseIterator::operator--(int x){//code as post decrement
        Map<key_T, mapped_T>::ReverseIterator haveToReturn(this->node, this->root);
	if(this->node == 0){
		treeNode<key_T, mapped_T> *current = findNum(this->root, this->root->num+1);
		this->assign(current);
		return haveToReturn;
	}
	else{
	        treeNode<key_T, mapped_T> *current = findNum(this->root, this->node->num+1);
        	this->assign(current);
	        return haveToReturn;
	}
}
template<class key_T, class mapped_T>
pair<key_T, mapped_T>& Map<key_T, mapped_T>::ReverseIterator::operator*() const{
        return *this->node->data;
}
template<typename key_T, typename mapped_T>
pair<key_T, mapped_T>* Map<key_T, mapped_T>::ReverseIterator::operator->() const{
        return this->node->data;
}

}//End of namespace
