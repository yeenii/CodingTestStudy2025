#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

/* root, left, right, val(key)*/
class Node
{
public:
    Node* left;
    Node* right;
    int val;
    int x_val;
    int y_val;

    Node(int key, int x, int y) :val(key),x_val(x), y_val(y), left(nullptr), right(nullptr) {};

    
};

class Tree
{
public:
    Node* root;

    Tree() : root(nullptr) {};

    Node* insertTree(int key, int x, int y, Node* node)
    {
        //만약에 비어있다면 노드 추가
        if (node == nullptr)
            return new Node(key, x, y);

        if (node->x_val > x)
        {
            node->left = insertTree(key, x, y, node->left); //부모 노드 보다 작으면 왼쪽
        }
        else
        {
            node->right = insertTree(key, x, y, node->right); // 부모 노드 보다 크면 오른쪽
        }

        return node;
    }


    void insert(int key, int x, int y)
    {
        root = insertTree(key, x, y, root);
    }

};

bool compare(vector<int> a, vector<int> b)
{
    if (a[2] == b[2]) //y 값이 같다면
    {
        return a[1] < b[1]; //x는 오름 차순
    }

    return a[2] > b[2]; //y 내림차순
}

void preCompute(Node* node, vector<int>& pre_result)
{

    if (node == nullptr)
        return;

    pre_result.push_back(node->val);
    preCompute(node->left, pre_result);
    preCompute(node->right, pre_result);
    
}

void postCompute(Node* node, vector<int>& post_result)
{

    if (node == nullptr)
        return;

    postCompute(node->left, post_result);
    postCompute(node->right, post_result);
    post_result.push_back(node->val);

}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<vector<int>> nodes; // {노드값, x좌표, y 좌표}

    //1. 정렬
    //(1) 각 배열의 노드 값 추가
    for (int i = 0; i < nodeinfo.size(); i++)
    {
        nodes.push_back({i + 1, nodeinfo[i][0],nodeinfo[i][1]});
    }

    //(2) y좌표 기준 내림차순. y 좌표 값이 같다면 x는 오름차순
    sort(nodes.begin(),nodes.end(),compare);

    //2. 이진 탐색 트리 생성
    Tree tree;

    for (vector<int> node : nodes)
    {
        tree.insert(node[0],node[1],node[2]);
    }

   //3. 전위, 후위 순회
    vector<int> pre_result;
    vector<int> post_result;

    preCompute(tree.root,pre_result); //루트노드, 전위 순회 결과 담을 값
    postCompute(tree.root, post_result); //루트노드, 후위 순회 결과 담을 값

    answer.push_back(pre_result);
    answer.push_back(post_result);

    return answer;
}

int main()
{
    vector<vector<int>> nodeinfo = { {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2} };

    auto result = solution(nodeinfo);

    for (auto& row: result)
    {
        for (auto& val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    

	return 0;
}