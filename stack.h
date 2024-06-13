#ifndef STACK
#define STACK

#include <stdexcept>

template<typename T>
class nodestack {
public:
	T data;
	nodestack<T>* prev;
	nodestack<T>* next;
	nodestack(T data): data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class stackh {
private:
	nodestack<T>* head;
	nodestack<T>* tail;
	nodestack<T>* cur;
	int nodeCount;

public:
	stackh() {
		T newT;
		nodestack<T>* newData = new nodestack<T>(newT);
		head = newData;
		tail = newData;
		cur = newData;
		nodeCount = 1;
	}

	stackh(T newT) {
		nodestack<T>* newData = new nodestack<T>(newT);
		head = newData;
		tail = newData;
		cur = newData;
		nodeCount = 1;
	}

	~stackh() {
		while (head != tail) {
			nodestack<T>* tmp = head;
			head = head->next;
			delete tmp;
		}
		nodeCount = 0;
	}

	int size() {
		return nodeCount;
	}

	bool empty() {
		return nodeCount == 0;
	}

	void push_back(T data) {
		nodestack<T>* newData = new nodestack<T>(data);
		if (head == nullptr) {
			head = newData;
			tail = newData;
		}
		else {
			tail->next = newData;
			newData->prev = tail;
			tail = newData;
		}

		cur = newData;
		nodeCount++;
	}

	T current() {
		return cur->data;
	}

	bool go_foward() {
		if (cur == head) return false;
		cur = cur->prev;
		return true;
	}

	bool go_back() {
		if (cur == tail) return false;
		cur = cur->next;
		return true;
	}

	void remove() {
		while (tail != cur) {
			nodestack<T>* temp = tail;
			tail = tail->prev;
			delete temp;
		}
	}
};

#endif // !STACK
