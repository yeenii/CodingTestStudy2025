#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

int looser1(vector<int> answer)
{
    vector<int> pattern = {1, 2, 3, 4, 5}; //패턴 배열에 작성
    int count = 0;

    for (int i = 0; i < answer.size(); i++)
    {
        if (answer[i] == pattern[i % pattern.size()]) // 패턴 반복
            count++;
    }

    return count;
}

int looser2(vector<int> answer)
{
    vector<int> pattern = {2,1,2,3,2,4,2,5};
    int count = 0;

    for (int i = 0; i < answer.size(); i++)
    {
        if (answer[i] == pattern[i % pattern.size()])
            count++;
    }

    return count;
}

int looser3(vector<int> answer)
{
    vector<int> pattern = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    int count = 0;

    for (int i = 0; i < answer.size(); i++)
    {
        if (answer[i] == pattern[i % pattern.size()])
            count++;
    }

    return count;
}
vector<int> solution(vector<int> answers) {
   

    
    int a = looser1(answers);
    int b = looser2(answers);
    int c = looser3(answers);

    vector<int> result = { a, b, c };
    vector<int> r;

    int maxVal = *max_element(result.begin(), result.end()); // 최댓값 위치를 반환하는 max_element()에 *(역참조)를 붙여 값을 반환

    for (int i = 0;i < result.size(); i++)
    {
        if (result[i] == maxVal) 
        {
            r.push_back(i + 1);
        }
    }
    return r;
}

int main()
{
    vector<int> answers = {1, 3, 2, 4, 2};

    auto result = solution(answers); // auto를 사용하여 자동 감지

    for (auto it = result.begin(); it != result.end(); it++) // 벡터 정렬된거 출력
    {
        cout << *it << " ";
    }
    cout << endl;

	return 0;
}