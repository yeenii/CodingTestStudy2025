#include<iostream>
#include <string>
#include <vector>
#include<unordered_map>

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;

    unordered_map<string, string> enroll_lst; //�Ǹſ� - �θ��Ǹſ�
    unordered_map<string, int> total; // �Ǹſ� - ���� ���ͱ�

    //1. �Ǹſ� - �θ��Ǹſ� �迭 ����
    for (int i = 0; i < enroll.size(); i++)
    {
        enroll_lst[enroll[i]] = referral[i]; //key: enroll �迭 - val: referral �迭
    }

    //2. �Ǹſ� - ���� ���ͱ� ���� �迭 ����. 0���� �ʱ�ȭ
    for (int i = 0; i < enroll.size(); i++)
    {
        total[enroll[i]] = 0;
    }

    //*3. �Ǹſ� Ʈ�� ����
    for (int i = 0; i < seller.size(); i++)
    {
        //seller ������ ���ͱ�
        string name = seller[i];
        int money = amount[i] * 100;

        while (name != "-" && money>0) //�̸��� "-" �� ���� �� ���� && *���ͱ��� 0�� ��� (-> testcase 11-13 ��Ÿ�ӿ���)
        {
            int disturb = money * 0.1; // ���ͱ��� 10% //12, 1
            total[name] += money - disturb;

            //�θ� �Ǹſ����� Ű ����
            if (enroll_lst.find(name) != enroll_lst.end())
            {
                name = enroll_lst[name];
            }

            money = disturb; //���ͱ��� 10% �Ѱ���
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