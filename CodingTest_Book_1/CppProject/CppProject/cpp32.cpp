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
        //���࿡ ����ִٸ� ��� �߰�
        if (node == nullptr)
            return new Node(key, x, y);

        if (node->x_val > x)
        {
            node->left = insertTree(key, x, y, node->left); //�θ� ��� ���� ������ ����
        }
        else
        {
            node->right = insertTree(key, x, y, node->right); // �θ� ��� ���� ũ�� ������
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
    if (a[2] == b[2]) //y ���� ���ٸ�
    {
        return a[1] < b[1]; //x�� ���� ����
    }

    return a[2] > b[2]; //y ��������
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
    vector<vector<int>> nodes; // {��尪, x��ǥ, y ��ǥ}

    //1. ����
    //(1) �� �迭�� ��� �� �߰�
    for (int i = 0; i < nodeinfo.size(); i++)
    {
        nodes.push_back({i + 1, nodeinfo[i][0],nodeinfo[i][1]});
    }

    //(2) y��ǥ ���� ��������. y ��ǥ ���� ���ٸ� x�� ��������
    sort(nodes.begin(),nodes.end(),compare);

    //2. ���� Ž�� Ʈ�� ����
    Tree tree;

    for (vector<int> node : nodes)
    {
        tree.insert(node[0],node[1],node[2]);
    }

   //3. ����, ���� ��ȸ
    vector<int> pre_result;
    vector<int> post_result;

    preCompute(tree.root,pre_result); //��Ʈ���, ���� ��ȸ ��� ���� ��
    postCompute(tree.root, post_result); //��Ʈ���, ���� ��ȸ ��� ���� ��

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