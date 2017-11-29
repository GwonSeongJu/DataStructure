#include <iostream>

#define TEST_ETTREE 1

template <typename T>
struct ETNode{
	T n_data;
	ETNode* n_leftSide;
	ETNode* n_rightSide;
};

template <typename T> class ETree {
private:
	ETNode<T>* source;
	ETNode<T>* cur;
public:
	ETNode<T>* GetTopNode() {
		return source;
	}

	ETNode<T>* MakeETreeNode(){
		ETNode<T>* tmp = new ETNode<T>;
		tmp->n_leftSide = NULL;
		tmp->n_rightSide = NULL;
		return tmp;
	}
	void ETreeInit() {
		source = MakeETreeNode();
		source->n_leftSide = NULL;
		source->n_rightSide = NULL;
	}
	void DeleteETreeNode(ETNode<T> *node) {
		if (node == NULL)
			return;

		DeleteETreeNode(node->n_leftSide);
		DeleteETreeNode(node->n_rightSide);
		delete(node);
	}

	T GetData(ETNode<T> *node) {
		return node->n_data;
	}

	void SetData(ETNode<T> *node, T data) {
		node->n_data = data;
	}

	ETNode<T>* GetLeftSubTree(ETNode<T> *node) {
		
		return node->n_leftSide;
	}
	ETNode<T>* GetRightSubTree(ETNode<T> *node) {
		
		return node->n_rightSide;
	}
	void MakeLeftSubTree(ETNode<T> *main, ETNode<T>* sub) {
		if (main->n_leftSide != NULL)
			DeleteETreeNode(main->n_leftSide);
		main->n_leftSide = sub;
	}
	void MakeRIghtSubTree(ETNode<T> *main, ETNode<T>* sub) {
		if (main->n_rightSide != NULL)
			DeleteETreeNode(main->n_rightSide);
		main->n_rightSide = sub;
	}
	ETNode<T>* FindUpNode(ETNode<T>* top,ETNode<T>* node) {
		if (top == NULL)
			return NULL;

		if (top->n_leftSide == node || top->n_rightSide==node){
			return top;
		}

		if (!FindUpNode(top->n_leftSide, node)) {
			if (!FindUpNode(top->n_rightSide, node)) {
				return NULL;
			}
		}
		return NULL;
	}
	void ProcessE(char* eData) {
		int i = 0;
		char cdata;
		ETNode<T>* tmpN;
		cur = source;

		while ((cdata = eData[i])!='\0' ){
			if (cdata == ' ') {
				i++;
				continue;
			}
			if (cdata=='(') {
				
					if (cur->n_leftSide == NULL) {
						MakeLeftSubTree(cur, MakeETreeNode());
						cur = cur->n_leftSide;
					}
					else {
						MakeRIghtSubTree(cur, MakeETreeNode());
						cur = cur->n_rightSide;
					}
				
			
			}
			else if (cdata >= '0' && cdata <= '9') {
				int inputNumber;
				char tmp;
				inputNumber = atoi(&cdata);
				while (eData[i+1] >= '0' && eData[i+1] <= '9') {
					tmp = eData[i+1];
					inputNumber = inputNumber * 10 + atoi(&tmp);
					i++;
				}
				if (cur->n_leftSide == NULL) {
					MakeLeftSubTree(cur, MakeETreeNode());
					SetData(cur->n_leftSide, inputNumber);
				}
				else {
					MakeRIghtSubTree(cur, MakeETreeNode());
					SetData(cur->n_rightSide, inputNumber);
					
						source = MakeETreeNode();
						MakeLeftSubTree(source, cur);
						cur = source;
					
				}
			}
			else if (cdata == ')') {
			}
			else {
				cur->n_data = cdata;
			}
			i++;
		}
		source = GetLeftSubTree(source);
	}

	T GetENumber(ETNode<T>* node) {
		if (node == NULL)
			return 0;
		if (GetLeftSubTree(node)==NULL && GetRightSubTree(node)==NULL) {
			return node->n_data;
		}
	

		T lData, rData;
		lData = GetENumber(node->n_leftSide);
		rData = GetENumber(node->n_rightSide);

		switch (node->n_data)
		{
		case '+':
			return lData + rData;
		case '-':
			return lData - rData;
		case '*':
			return lData * rData;
		case '/':
			return lData / rData;
		}
	}
	char* ProcessEInit(char* exp) {
		
	}
};

#if TEST_ETTREE == 1
int main() {
	ETree<int>* test = new ETree<int>;
	test->ETreeInit();
	test->ProcessE("(1 + 55) * 30");
	test->GetENumber(test->GetTopNode());
}
#endif