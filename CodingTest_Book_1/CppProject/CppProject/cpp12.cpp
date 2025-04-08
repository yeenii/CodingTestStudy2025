#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

/*
1. ������ �������� ������ ���� �� ���� push(), �������� �������� pop()�ϰ� answer�� ���� ������ ���� ����
2. ���̻� ������ �������� ������ ������ �ʴ´ٸ�, ���ÿ� �����ִ� �κп� ���� ��� ����
*/

vector<int> solution(vector<int> prices) {

    vector<int> answer; //������ �������� ���� �Ⱓ�� �������� ����
    stack<int> st;

    answer.assign(prices.size(),0) ; //0���� �ʱ�ȭ

    int n = prices.size();

    for (int i = 0; i < prices.size(); i++)
    {
        while (!st.empty() && prices[st.top()] > prices[i]) //1. top ���� prices���� ũ�ٸ�, ������ �������� ����
        {
            answer[st.top()] = i - st.top(); //index - top��ġ
            st.pop();
        }

        //2. ������ �������� �ʴ� ���� -> push()
        st.push(i); //*�ε����� push()�ؾ� �� //* ��ġ �߿�..! ������ �������� ���� �� ���ϰ� ���� ������ ������ push()�ؾ� �ϹǷ�
    }

    //������ �������� ������ ���̻� ���� ���
    //���ÿ� ���� �κ� ���
    while (!st.empty())
    {
        answer[st.top()] = n - st.top() - 1;
        st.pop();
    }


    return answer;
}

int main()
{
    vector<int> prices = {1, 6, 9, 5};

    auto result = solution(prices);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

	return 0;
}