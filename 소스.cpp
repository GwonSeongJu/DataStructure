/*
2017-11-26 ����
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

	void AddPPrev(Node<T>* prev, T data) {			//���� ��带�������� ���� �־��ش�. (input data point prev node, not increase m_listsize)
		Node<T>* addNode = new Node<T>;
		addNode->data = data;

		addNode->next = prev->next;
		addNode->prev = prev;

		addNode->next->prev = addNode;
		addNode->prev->next = addNode;
	}


	T ReturnPData(Node<T>* p) {			//����Ʈ�ϴ� ��带 �����ϰ� �����͸� ��ȯ�Ѵ�. (delete Pointed node and return data in Nd)
		T data;

		p->prev->next = p->next;
		p->next->prev = p->prev;

		data = p->data;

		delete(p);

		return data;
	}

public:
	void DequeInit(Deque *pdeq = this) {		//�� �ʱ�ȭ(init deque,)
		pdeq->m_head = new Node<T>;
		pdeq->m_tail = new Node<T>;
		pdeq->m_listSize = 0;
	}

	int DQIsEmpty(Deque *pdeq = this) {		//���� ����ִ� üũ(empty is 1. not e is 0)
		if (pdeq->m_listSize == 0)
			return 0;
		else
			return 1;
	}



	void DQAddFirst(T data, Deque *pdeq = this) {		//�Ǿտ� ���� �߰��Ѵ�. (input data in front)
		AddPPrev(pdeq->m_head, data);
		pdeq->m_listSize++;
	}

	void DQAddLast(T data, Deque *pdeq = this) {		//���� �ǵڿ� ���� �߰��Ѵ�. (input data in last)
		AddPPrev(pdeq->m_tail->prev, data);
		pdeq->m_listSize++;
	}




	T DQRemoveFirst(Deque *pdeq = this) { //ù��° ���� ���� ��带 �����ϰ� ���� �����Ѵ� ( del first dataNode, and return data)
		T data;
		data = ReturnPData(pdeq->m_head->next);
		pdeq->m_listSize--;
		return data;
	}
	T DQRemoveLast(Deque *pdeq = this) {		//������ ���� ���� ��带 �����ϰ� ���� �����Ѵ�. (del last dataNode, and return data)
		T data;
		data = ReturnPData(pdeq->m_tail->prev);
		pdeq->m_listSize--;
		return data;
	}




	T DQGetFirst(Deque *pdeq = this) {		//ù��° ���� ���� ���� �����Ѵ�. ��带 ������ �ʴ´�.(return first data)
		T data;
		data = pdeq->m_head->next->data;
		return data;
	}

	T DQGetLast(Deque *pdeq = this) {		//������ ���� ���� ���� �����Ѵ�. ��带 ������ �ʴ´�.(return last data)
		T data;
		data = pdeq->m_tail->prev->data;
		return data;
	}




	void ShowAllData(Deque *pdeq = this) {  //���� ���� ��� ���� �����ش�. ( showAlldata have list)
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

