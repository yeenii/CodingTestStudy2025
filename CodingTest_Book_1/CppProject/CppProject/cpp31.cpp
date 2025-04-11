#include<iostream>
#include <string>
#include <vector>
#include<unordered_map>

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;

    unordered_map<string, string> enroll_lst; //판매원 - 부모판매원
    unordered_map<string, int> total; // 판매원 - 최종 이익금

    //1. 판매원 - 부모판매원 배열 생성
    for (int i = 0; i < enroll.size(); i++)
    {
        enroll_lst[enroll[i]] = referral[i]; //key: enroll 배열 - val: referral 배열
    }

    //2. 판매원 - 최종 이익금 담을 배열 생성. 0으로 초기화
    for (int i = 0; i < enroll.size(); i++)
    {
        total[enroll[i]] = 0;
    }

    //*3. 판매원 트리 생성
    for (int i = 0; i < seller.size(); i++)
    {
        //seller 마다의 이익금
        string name = seller[i];
        int money = amount[i] * 100;

        while (name != "-" && money>0) //이름이 "-" 가 나올 떄 까지 && *이익금이 0일 경우 (-> testcase 11-13 런타임에러)
        {
            int disturb = money * 0.1; // 이익금의 10% //12, 1
            total[name] += money - disturb;

            //부모 판매원으로 키 변경
            if (enroll_lst.find(name) != enroll_lst.end())
            {
                name = enroll_lst[name];
            }

            money = disturb; //이익금의 10% 넘겨줌
        }
    }

    for (int i=0; i<total.size();i++)
    {
        answer.push_back(total[enroll[i]]);
    }

    return answer;
}

int main()
{
    vector<string> enroll = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
    vector<string> referral = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
    vector<string> seller = { "young", "john", "tod", "emily", "mary" };
    vector<int> amount = { 12, 4, 2, 5, 10 };

    auto result = solution(enroll, referral,seller, amount);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

	return 0;
}