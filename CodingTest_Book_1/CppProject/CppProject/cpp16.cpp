#include<iostream>
#include<vector>
#include<cmath> //ceil() : 무조건 반올림

using namespace std;

/*
1. 각 porgresses마다 speed에 따라 얼마나 걸리는지 구하고, 배열에 저장
2. 배열의 첫번째를 가장 오래 걸리는 날로 지정(max_day)
3. max_day와 배열을 비교해서, max_day가 계속 더 크거나 같으면 cnt++, 
   작으면 answer배열에 cnt 저장하고, cnt 초기화한다음, max_day도 현재 원소로 업데이트
4. *더이상 비교할 원소가 없는 경우, 현재 cnt를 answer 배열에 저장*
*/

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> workDay;
    vector<int> answer;
    int cnt = 0;

    //1.
    for (int i = 0; i < progresses.size(); i++)
    {
        int n = 100 - progresses[i];
        double s = (double)n / speeds[i];
        int work = (int)ceil(s);
        workDay.push_back(work);
    }

    int max_day = workDay[0]; //2.

    //3.
    for (int i = 0; i < workDay.size(); i++)
    {
        
        if (max_day >= workDay[i])
        {
            cnt += 1;
        }
        else
        {
            answer.push_back(cnt);
            cnt = 1;
            max_day = workDay[i];
            
        }
            
    }
    answer.push_back(cnt); //4.

    return answer;
}

int main()
{
    vector<int> progresses = { 95, 90, 99, 99, 80, 99 };
    vector<int> speeds = { 1, 1, 1, 1, 1, 1 };

    auto result = solution(progresses, speeds);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i <<" ";
    }
    cout << endl;
	return 0;
}