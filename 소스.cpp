/*
2017-11-26 시작
*/

#include <iostream>

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
};

template <typename T> class Deque {
private:
	Node<T> *m_head;
	Node<T> *m_tail;
	int m_listSize;

	void AddPPrev(Node<T>* prev, T data) {			//이전 노드를기준으로 값을 넣어준다. (input data point prev node, not increase m_listsize)
		Node<T>* addNode = new Node<T>;
		addNode->data = data;

		addNode->next = prev->next;
		addNode->prev = prev;

		addNode->next->prev = addNode;
		addNode->prev->next = addNode;
	}


	T ReturnPData(Node<T>* p) {			//포인트하는 노드를 제거하고 데이터를 반환한다. (delete Pointed node and return data in Nd)
		T data;

		p->prev->next = p->next;
		p->next->prev = p->prev;

		data = p->data;

		delete(p);

		return data;
	}

public:
	void DequeInit(Deque *pdeq = this) {		//덱 초기화(init deque,)
		pdeq->m_head = new Node<T>;
		pdeq->m_tail = new Node<T>;
		pdeq->m_listSize = 0;
	}

	int DQIsEmpty(Deque *pdeq = this) {		//덱이 비어있는 체크(empty is 1. not e is 0)
		if (pdeq->m_listSize == 0)
			return 0;
		else
			return 1;
	}



	void DQAddFirst(T data, Deque *pdeq = this) {		//맨앞에 값을 추가한다. (input data in front)
		AddPPrev(pdeq->m_head, data);
		pdeq->m_listSize++;
	}

	void DQAddLast(T data, Deque *pdeq = this) {		//덱의 맨뒤에 값을 추가한다. (input data in last)
		AddPPrev(pdeq->m_tail->prev, data);
		pdeq->m_listSize++;
	}




	T DQRemoveFirst(Deque *pdeq = this) { //첫번째 값을 가진 노드를 제거하고 값을 리턴한다 ( del first dataNode, and return data)
		T data;
		data = ReturnPData(pdeq->m_head->next);
		pdeq->m_listSize--;
		return data;
	}
	T DQRemoveLast(Deque *pdeq = this) {		//마지막 값을 가진 노드를 제거하고 값을 리턴한다. (del last dataNode, and return data)
		T data;
		data = ReturnPData(pdeq->m_tail->prev);
		pdeq->m_listSize--;
		return data;
	}




	T DQGetFirst(Deque *pdeq = this) {		//첫번째 값을 가진 값을 리턴한다. 노드를 지우지 않는다.(return first data)
		T data;
		data = pdeq->m_head->next->data;
		return data;
	}

	T DQGetLast(Deque *pdeq = this) {		//마지막 값을 가진 값을 리턴한다. 노드를 지우지 않는다.(return last data)
		T data;
		data = pdeq->m_tail->prev->data;
		return data;
	}




	void ShowAllData(Deque *pdeq = this) {  //덱이 가진 모든 값을 보여준다. ( showAlldata have list)
		for (Node<T> *cur = pdeq->m_head->next; cur != pdeq->m_tail; cur = cur->next) {
			std::cout << cur->data << std::endl;
		}
	}

};

int main()
{
	Deque<int>* test = new Deque<int>;
	test->DequeInit();
	test->DQAddFirst(10);
	test->DQAddFirst(20);
	test->ShowAllData();

	return 0;
}

