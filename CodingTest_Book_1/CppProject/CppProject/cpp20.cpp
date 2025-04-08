#include<iostream>
#include<vector>
#include <string>
#include<unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    //string answer = "";
   
    unordered_map<string, int> hash;

    //* 중복 참가자 고려 -> 참가자 수 만큼 수 증가
    //1. 해시테이블 초기화
    for (int i = 0; i < participant.size(); i++)
    {
        hash[participant[i]]++;
    }
   
    //2. 해시테이블에 completion 값이 key로 있는 경우, 값을  --
    for (int j = 0; j < completion.size(); j++)
    {
         hash[completion[j]]--; //완주자가 해시테이블에 있는 경우 감소
    }

    //3. 해시테이블 second가 0일 경우 return
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