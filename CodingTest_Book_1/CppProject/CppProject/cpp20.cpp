#include<iostream>
#include<vector>
#include <string>
#include<unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    //string answer = "";
   
    unordered_map<string, int> hash;

    //* �ߺ� ������ ��� -> ������ �� ��ŭ �� ����
    //1. �ؽ����̺� �ʱ�ȭ
    for (int i = 0; i < participant.size(); i++)
    {
        hash[participant[i]]++;
    }
   
    //2. �ؽ����̺� completion ���� key�� �ִ� ���, ����  --
    for (int j = 0; j < completion.size(); j++)
    {
         hash[completion[j]]--; //�����ڰ� �ؽ����̺� �ִ� ��� ����
    }

    //3. �ؽ����̺� second�� 0�� ��� return
    for (auto h : hash)
    {
        if (h.second > 0)
            return h.first;

    }
}

int main()
{
    vector<string> participant = { "mislav", "stanko", "mislav", "ana" };
    vector<string> completion = { "stanko", "ana", "mislav" };

    //vector<string> participant = { "marina", "josipa", "nikola", "vinko", "filipa" };
    //vector<string> completion = { "josipa", "filipa", "marina", "nikola" };
    
    string result;

    result = solution(participant, completion);

    cout << result << endl;
	return 0;
}