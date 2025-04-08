#include<iostream>
#include <string>
#include <vector>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    string uid;
    string BlockId;
    unordered_map<string, int> Signal_list;
    unordered_map<string, unordered_set<string>> dic_uid;

    answer.assign(id_list.size(),0); //*정지된 ID가 없는 경우, 메일을 받지 않음 -> 초기화 0 필요

    //1. 유저별 신고한 ID, 유저별 신고당한 횟수 해시테이블 생성
    for (int i = 0; i < report.size(); i++)
    {
        istringstream iss(report[i]);

        iss >> uid >> BlockId;

        //1. 유저별 신고한 유저
        if (!dic_uid[uid].insert(BlockId).second) //한 유저가 동일한 유저 신고하면 건너뛰기. 아니면 저장
            continue;

        //2. 유저별 신고당한 횟수
        Signal_list[BlockId] += 1;

        
    }
    
    //k 횟수 넘는 신고당한 ID
    unordered_set<string> block_list;
    for (auto p : Signal_list)
    {
        if (k <= p.second)
            block_list.insert(p.first);
    }
    
    // 유저별 처리 결과 메일 개수
    for (int i = 0; i < id_list.size(); i++) //유저마다
    {
        for (auto dic : dic_uid[id_list[i]]) //dic_uid에 유저가 신고한 ID 여러개 
        {
            if(block_list.count(dic)) //신고당한 ID일 경우 *count() 활용
                answer[i] += 1;
        }
    }

    return answer;
}

int main()
{
    vector<string> id_list = { "muzi", "frodo", "apeach", "neo" };
    vector<string> report = { "muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi" };
    int k = 2;

    auto result = solution(id_list,report,k);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

    return 0;
}

