#include <iostream>

#define DLINKEDLIST_TEST 1
#define ERROR_SHOW 1
template <typename T>
struct Node
{
	T data;
	Node* next;
	Node* prev;
};

template <typename T> class DLinkedList {
private:
	Node<T>* head;
	Node<T>* cur;
	Node<T>* tail;
	int ListSize;
public:
	int getSize() { return Listsize; }
	void init() {
		head = new Node<T>;
		tail = new Node<T>;
		head->prev = head;
		head->next = tail;
		tail->prev = head;
		tail->next = tail;
		ListSize = 0;
	}
	Node<T>* getNode(Node<T>* _head, int index) {
		cur = _head;
		for (int i = 0; cur->next != cur->next->next && i<index; cur = cur->next, i++) {}
		return cur;
	}
	Node<T>* getNode(int index){
		cur = head;
		for (int i = 0; cur->next != cur->next->next && i<index; cur = cur->next, i++) {}
		return cur;
		
	}
	void PushNode(Node<T>* prev, Node<T>* data) {
		Node<T>* node_tmp = data;
		node_tmp->next = prev->next;
		node_tmp->prev = prev;

		prev->next = node_tmp;

		node_tmp->next->prev = node_tmp;
	}
	void PushData(Node<T>* prev, T data) {	//not increase Listsize 
		Node<T>* node_tmp = new Node<T>;
		node_tmp->data = data;
		PushNode(prev, node_tmp);

		
	}

	void PushData(T data, int index=-1) {
		Node<T>* node_tmp;
		if (index == -1)
			index = ListSize;
		index--;
		node_tmp = getNode(index);
		PushData(node_tmp, data);
		ListSize++;
	}

	

	Node<T>* PopNode(Node<T>* cur) {
		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
		return cur;
	}
	
	T PopData(Node<T>* cur) {	// not decrease Listsize
		T data_tmp;
		data_tmp = cur->data;

		PopNode(cur);

		delete(cur);

		return data_tmp;
	}

	T PopData(int index=-1) {
		if (index == -1)
			index = ListSize;
		if (index == 0) {
#if ERROR_SHOW == 1 
			std::cout << "ERROR(T PopData(int index = -1)): 헤드파일을 호출합니다" << std::endl;
#endif
			return (T)0;
		}
		ListSize--;
		return PopData(getNode(index));
	}

	void Exchange(Node<T>* A, Node<T>* B) {
		Node<T>* Ahead, *Bhead;
		Node<T>* Acur, *Bcur;

		int Aindex=0, Bindex=0;
		for (Acur = A->prev; Acur->prev != Acur; Acur = Acur->prev)
			Aindex++;
		for (Bcur = B->prev; Bcur->prev != Bcur; Bcur = Bcur->prev)
			Bindex++;
		Ahead = Acur;
		Bhead = Bcur;

		A=PopNode(A);
		PushNode(getNode(Bhead, Bindex), A);

		B=PopNode(B);
		PushNode(getNode(Ahead, Aindex), B);




	}

	void showAllData() {
		std::cout << "데이터 출력: ";
		for (cur = head->next; cur != tail; cur = cur->next) {
			std::cout << "[" << cur->data << "]" << "\t";
		}
		std::cout << std::endl;
	}

};

#if DLINKEDLIST_TEST == 1
int main() {
	DLinkedList<int>* ltest = new DLinkedList<int>;
	ltest->init();
	ltest->PushData(10);
	ltest->showAllData();
	ltest->PopData();
	ltest->showAllData();
	ltest->PushData(12);
	ltest->showAllData();
	ltest->PushData(24);
	ltest->showAllData();
	ltest->PushData(243,1);
	ltest->showAllData();
	ltest->PopData(1);
	ltest->showAllData();
	ltest->Exchange(ltest->getNode(2), ltest->getNode(1));
	ltest->showAllData();

	DLinkedList<int>* rtest = new DLinkedList<int>;
	rtest->init();
	rtest->PushData(25);
	rtest->Exchange(ltest->getNode(1), rtest->getNode(1));
	rtest->showAllData();
	ltest->showAllData();
	return 1;
}
#endif