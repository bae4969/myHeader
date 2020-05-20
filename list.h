#ifndef LIST_H
#define LIST_H

template<typename T>
class ListNode {
private:
	T val;
	ListNode* pre;
	ListNode* next;

public:
	ListNode() {
		this->val = nullptr;
		this->pre = nullptr;
		this->next = nullptr;
	}
	ListNode(T value) {
		this->val = value;
		this->pre = nullptr;
		this->next = nullptr;
	}
	~ListNode() {

	}

	T getVal() { return this->val; }
	ListNode* getPre() { return this->pre; }
	ListNode* getNext() { return this->next; }

	void setVal(T value) { this->val = value; }
	void setPre(ListNode* pre) { this->pre = pre; }
	void setNext(ListNode* next) { this->next = next; }
};

template<typename T>
class List {
private:
	unsigned int size;
	ListNode<T>* head;
	ListNode<T>* tail;
	ListNode<T>* lastNodePtr;

public:
	List() {
		this->size = 0;
		this->head = new ListNode<T>;
		this->tail = new ListNode<T>;
		this->head->setNext(this->tail);
		this->tail->setPre(this->head);
		this->lastNodePtr = this->head;
	}
	List(int size) {
		this->size = 0;
		this->head = new ListNode<T>;
		this->tail = new ListNode<T>;
		this->head->setNext(this->tail);
		this->tail->setPre(this->head);
		this->lastNodePtr = this->head;

		for (int i = 0; i < size; i++)
			addNode(size, 0);
	}
	List(int size, T value) {
		this->size = 0;
		this->head = new ListNode<T>;
		this->tail = new ListNode<T>;
		this->head->setNext(this->tail);
		this->tail->setPre(this->head);
		this->lastNodePtr = this->head;

		for (int i = 0; i < size; i++)
			addNode(size, value);
	}
	~List() {
		ListNode<T>* ptr1 = head->getNext();
		ListNode<T>* ptr2 = ptr1;
		for (int i = 0; i < size; i++) {
			ptr2 = ptr1->getNext();
			delete ptr1;
			ptr1 = ptr2;
		}
		delete this->head;
		delete this->tail;
	}

	unsigned int getSize() { return this->size; }
	ListNode<T>* getLastNodePtr() { return this->lastNodePtr; }
	ListNode<T>* getNode(unsigned int index) {
		if (!(index < this->size))
			return nullptr;

		ListNode<T>* ptr = this->head->getNext();
		for (unsigned int i = 0; i < index; i++)
			ptr = ptr->getNext();
		this->lastNodePtr = ptr;
		return ptr;
	}
	ListNode<T>* getFirstNode() {
		if (!this->size)
			return nullptr;
		return this->head->getNext();
	}
	ListNode<T>* getEndNode() {
		if (!this->size)
			return nullptr;
		return this->tail->getPre();
	}
	T getNodeVal(int index) {
		ListNode<T>* ptr = this->getNode(index);
		if (!ptr)
			return 0;
		this->lastNodePtr = ptr;
		return ptr->getVal();
	}

	void setNode(unsigned int index, T value) {
		ListNode<T>* ptr = this->getNode(index);
		if (!ptr)
			return;

		ptr->setVal(value);
	}

	void addNode(ListNode<T>* loc, T value) {
		ListNode<T>* node = new ListNode<T>(value);
		node->setPre(loc);
		node->setNext(loc->getNext());
		loc->getNext()->setPre(node);
		loc->setNext(node);
		this->size++;
		this->lastNodePtr = node;
	}
	void addNode(unsigned int index, T value) {
		ListNode<T>* ptr;
		if (index == 0)
			ptr = this->head;
		else if (index >= size)
			ptr = this->tail->getPre();
		else {
			ptr = getNode(index - 1);
			if (!ptr) return;
		}

		ListNode<T>* node = new ListNode<T>(value);
		node->setPre(ptr);
		node->setNext(ptr->getNext());
		ptr->getNext()->setPre(node);
		ptr->setNext(node);
		this->size++;
		this->lastNodePtr = node;
	}
	void addNodeFront(T value) {
		ListNode<T>* ptr = head;
		ListNode<T>* node = new ListNode<T>(value);
		node->setPre(ptr);
		node->setNext(ptr->getNext());
		ptr->getNext()->setPre(node);
		ptr->setNext(node);
		this->size++;
		this->lastNodePtr = node;
	}
	void addNodeBack(T value) {
		ListNode<T>* ptr = tail->getPre();
		ListNode<T>* node = new ListNode<T>(value);
		node->setPre(ptr);
		node->setNext(ptr->getNext());
		ptr->getNext()->setPre(node);
		ptr->setNext(node);
		this->size++;
		this->lastNodePtr = node;
	}

	void deleteNode(unsigned int index) {
		ListNode<T>* ptr = this->getNode(index);
		if (!ptr)
			return;

		ListNode<T>* pre = ptr->getPre();
		ListNode<T>* next = ptr->getNext();
		pre->setNext(next);
		next->setPre(pre);
		delete ptr;
		this->size--;
	}
	void deleteFirstNode() {
		if (!size)
			return;

		ListNode<T>* ptr = this->head->getNext();
		this->head->setNext(ptr->getNext());
		delete ptr;
		this->size--;
	}
	void deleteEndNode() {
		if (!size)
			return;

		ListNode<T>* ptr = this->tail->getPre();
		ptr->getPre()->setNext(this->tail);
		this->tail->setPre(ptr->getPre());
		delete ptr;
		this->size--;
	}
};

#endif
