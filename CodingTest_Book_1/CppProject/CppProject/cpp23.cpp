#include<iostream>
#include <string>
#include <vector>
#include<unordered_map>

using namespace std;

/*
���� ��� X,  discount �迭�� ù �� ���� 10���� �˻�

1. want, number �� �ؽ����̺� wantMap ����
2. discount 10���� discountMap ����
3. �� ���� �ؽ����̺��� ��ġ�ϸ�, ȸ������ ������ ��. +1
*/


int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    unordered_map<string, int> wantMap;
    
    for (int i = 0; i < want.size(); i++)
    {
        wantMap[want[i]]+= number[i];
    }

    for (int j = 0; j < discount.size()-9; j++)
    {
        unordered_map<string, int> discountMap; //��� ���� �����Ǿ�� ��

        for (int k = j; k < j + 10; k++)
        {
            discountMap[discount[k]]++;
        }

        if (wantMap == discountMap)
            answer+=1;
    }

    return answer;
}

int main()
{
    vector<string> want = { "banana", "apple", "rice", "pork", "pot" };
    vector<int> number = { 3, 2, 2, 2, 1 };
    vector<string> discount = { "chicken", "apple", "apple", "banana", "rice", "apple", "pork", "banana", "pork", "rice", "pot", "banana", "apple", "banana" };
	
    int result = solution(want, number, discount);
    
    cout << result << endl;

    return 0;
}