#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

/*
1. 가격이 떨어지는 구간이 나올 때 까지 push(), 떨어지는 구간에서 pop()하고 answer에 가격 떨어진 몇초 저장
2. 더이상 가격이 떨어지는 구간이 나오지 않는다면, 스택에 남아있는 부분에 대한 계산 수행
*/

vector<int> solution(vector<int> prices) {

    vector<int> answer; //가격이 떨어지지 않은 기간은 몇초인지 저장
    stack<int> st;

    answer.assign(prices.size(),0) ; //0으로 초기화

    int n = prices.size();

    for (int i = 0; i < prices.size(); i++)
    {
        while (!st.empty() && prices[st.top()] > prices[i]) //1. top 값이 prices보다 크다면, 가격이 떨어지는 구간
        {
            answer[st.top()] = i - st.top(); //index - top위치
            st.pop();
        }

        //2. 가격이 떨어지지 않는 구간 -> push()
        st.push(i); //*인덱스를 push()해야 함 //* 위치 중요..! 가격이 떨어지는 구간 다 구하고 나서 나머지 구간도 push()해야 하므로
    }

    //가격이 떨어지는 구간이 더이상 없는 경우
    //스택에 남은 부분 계산
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