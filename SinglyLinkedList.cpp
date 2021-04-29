#include <iostream>

template <typename Type>
class SinglyLinkedList;

template <typename Type>
class Node {
private:
	Type value{};
	Node<Type>* next{};
	Node() {}
	friend class SinglyLinkedList<Type>;
};

template <typename Type>
class SinglyLinkedList {
private:
	Node<Type>* head;
	Node<Type>* tail;
	int size;

public:
	SinglyLinkedList() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	void add(Type value) {
		Node<Type> *node = new Node<Type>();
		node->value = value;
		node->next = NULL;
		if (head == NULL) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
		size++;
	}

	bool add(Type value, int index) {
		if (index > size || index < 0) {
			return false;
		}
		Node<Type>* node = new Node<Type>();
		node->value = value;
		Node<Type>* curr = head;
		if (index == 0) {
			node->next = curr;
			if (head == NULL) {
				tail = node;
			}
			head = node;
			size++;
			return true;
		}
		Node<Type>* last = curr;
		for (int i = 0; i < index; i++) {
			last = curr;
			curr = curr->next;
		}
		node->next = curr;
		last->next = node;
		size++;
		return true;
	}

	Type getLast() {
		return tail->value;
	}

	Type get(int index) {
		if (index > size || index < 0 || size == 0) {
			return tail->value;
		}
		Node<Type>* tmp = head;
		for (int i = 0; i < index; i++) {
			tmp = tmp->next;
		}
		return tmp->value;
	}
	
	int getIndex(Type value) {
		Node<Type>* tmp = head;
		int size = 0;
		while (tmp != NULL) {
			if (tmp->value == value) {
				return size;
			}
			tmp = tmp->next;
			size++;
		}
		return -1;
	}

	bool removeLast() {
		if (size == 0) {
			return false;
		}
		if (size == 1) {
			delete head;
			head = NULL;
			tail = NULL;
			size--;
			return true;
		}
		Node<Type>* last = head;
		for (int i = 0; i < size - 2; i++) {
			last = last->next;
		}
		delete last->next;
		last->next = NULL;
		tail = last;
		size--;
		return true;
	}

	bool remove(int index) {
		if (index > size || index < 0 || size == 0) {
			return false;
		}
		if (index == size - 1) {
			return removeLast();
		}
		Node<Type>* last = head;
		if (index == 0) {
			head = head->next;
			delete last;
			size--;
			return true;
		}
		for (int i = 0; i < index - 1; i++) {
			last = last->next;
		}
		Node<Type>* curr = last->next;
		last->next = curr->next;
		delete curr;
		size--;
		return true;
	}

	bool removeElement(Type value) {
		if (getIndex(value) != -1) {
			remove(getIndex(value));
			return true;
		}
		return false;
	}

	void removeElementAll(Type value) {
		if (getIndex(value) != -1) {
			removeElement(value);
			removeElementAll(value);
		}
	}
	
	void removeAll() {
		if (size == 0) {
			return;
		}
		Node<Type>* tmp = head;
		while (tmp != NULL) {
			head = head->next;
			delete tmp;
			tmp = head;
		}
		size = 0;
	}

	void printAll() {
		Node<Type>* tmp = head;
		while (tmp != NULL) {
			std::cout << tmp->value << " ";
			tmp = tmp->next;
		}
	}

	int getSize() {
		return size;
	}
};

int main() {
	SinglyLinkedList<int> test;
	test.add(5, 0);
	test.add(50);
	test.add(7);
	test.add(3);
	test.removeLast();
	test.add(2);
	test.remove(2);
	test.remove(2);
	test.remove(0);
	test.add(5, 0);
	test.printAll();
	test.removeAll();
	test.printAll();
	test.add(5);
	test.add(10);
	test.add(15, 1);
	test.add(5);
	test.add(6);
	test.add(5);
	std::cout << "\n";
	test.removeElement(15);
	test.removeElementAll(5);
	test.printAll();
	std::cout << "\n" << test.getLast();
	std::cout << "\n" << test.get(0);
	std::cout << "\n" << test.getIndex(15);
	std::cout << "\n" << test.getSize();
}