#include<iostream>
#include <string>
#include <vector>
#include<unordered_map>

using namespace std;

/*
순서 상관 X,  discount 배열의 첫 날 부터 10개씩 검사

1. want, number 로 해시테이블 wantMap 생성
2. discount 10개씩 discountMap 생성
3. 두 개의 해시테이블이 일치하면, 회원가입 가능한 날. +1
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
        unordered_map<string, int> discountMap; //계속 새로 생성되어야 함

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