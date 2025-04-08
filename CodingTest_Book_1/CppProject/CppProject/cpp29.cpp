/*�����Ϳ� Ŭ������ Ȱ���� ����Ž��Ʈ��*/


/*Ŭ����

1. Ŭ���� ����
- ��� ����
- ��� �Լ�
- ������ (&�Ҹ���) : ������� �ʱ�ȭ{};

2. ȣ��
- ��ü ����: Ŭ������* Ŭ������ü��
- Ŭ���� ��ü->�������

*/


#include<iostream>
#include<vector>

using namespace std;

class Node {

public:
	//�������
	int val; //���� ��� ��
	Node* left;
	Node* right;

	//��� �Լ�
	Node(int key): val(key), left(nullptr), right(nullptr){}; //������
};

class Tree {
public:
	Node* root;

	Tree() : root(nullptr) {}; //������

	Node* insertTree(int key, Node* node)
	{
		//��忡 �� �߰�
		if (node == nullptr)
			return new Node(key);

		//�θ� ��庸�� ���� ������ ���� ����Ʈ��, ���� ũ�� ������ ����Ʈ��
		if (key < node->val)
			node->left = insertTree(key, node->left); //*�ݵ�� node->left�� ���� �Ѱ���� ��
		else
			node->right = insertTree(key, node->right); //*�ݵ�� node->right�� ���� �Ѱ���� ��

		return node; //��Ʈ ��� 5 ��ȯ //�� ����� �Ʒ� ����� ��� ����� �־�� Ʈ�� ���°� �����ǹǷ�, root ��ȯ
	}

	bool searchTree(int key, Node* node)
	{
		//Ʈ���� Ž���ϴ� ���� ���� ��
		if (node == nullptr)
			return false;

		//Ʈ���� Ž���ϴ� ���� ���� ��
		if (key == node->val)
			return true;

		//Ž��
		if (key < node->val)
			searchTree(key, node->left);
		else
			searchTree(key, node->right);

	}

	void insert(int key)
	{
		root = insertTree(key, root);
	}

	bool Search(int key)
	{
		return searchTree(key, root);
	}
};

vector<bool> solution(vector<int> lst, vector<int> search_lst)
{
	Tree tree;
	vector<bool> result;

	//1. ���� Ž�� Ʈ�� ����
	for (int lst_val : lst)
	{
		tree.insert(lst_val);
	}
	
	
	//2. Ʈ�� Ž��
	for (int val : search_lst)
	{
		result.push_back(tree.Search(val));
	}

	return result;

}

int main()
{
	vector<int> lst = {5,3,8,4,2,1,7,10};
	vector<int> search_lst = {1,2,5,6};

	//vector<int> lst = { 1, 3, 5, 7, 9};
	//vector<int> search_lst = { 2, 4, 6, 8,10 };

	auto result = solution(lst, search_lst);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return 0;
}