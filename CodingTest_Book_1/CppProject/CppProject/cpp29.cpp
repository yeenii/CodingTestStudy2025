/*포인터와 클래스를 활용한 이진탐색트리*/


/*클래스

1. 클래스 정의
- 멤버 변수
- 멤버 함수
- 생성자 (&소멸자) : 멤버변수 초기화{};

2. 호출
- 객체 정의: 클래스명* 클래스객체명
- 클래스 객체->멤버변수

*/


#include<iostream>
#include<vector>

using namespace std;

class Node {

public:
	//멤버변수
	int val; //현재 노드 값
	Node* left;
	Node* right;

	//멤버 함수
	Node(int key): val(key), left(nullptr), right(nullptr){}; //생성자
};

class Tree {
public:
	Node* root;

	Tree() : root(nullptr) {}; //생성자

	Node* insertTree(int key, Node* node)
	{
		//노드에 값 추가
		if (node == nullptr)
			return new Node(key);

		//부모 노드보다 값이 작으면 왼쪽 서브트리, 값이 크면 오른쪽 서브트리
		if (key < node->val)
			node->left = insertTree(key, node->left); //*반드시 node->left에 값을 넘겨줘야 함
		else
			node->right = insertTree(key, node->right); //*반드시 node->right에 값을 넘겨줘야 함

		return node; //루트 노드 5 반환 //위 블록이 아래 블록을 계속 붙잡고 있어야 트리 형태가 유지되므로, root 반환
	}

	bool searchTree(int key, Node* node)
	{
		//트리에 탐색하는 값이 없을 때
		if (node == nullptr)
			return false;

		//트리에 탐색하는 값이 있을 때
		if (key == node->val)
			return true;

		//탐색
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

	//1. 이진 탐색 트리 생성
	for (int lst_val : lst)
	{
		tree.insert(lst_val);
	}
	
	
	//2. 트리 탐색
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