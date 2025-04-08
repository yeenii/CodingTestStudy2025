#include<iostream>
#include<vector>
#include<cmath> //ceil() : ������ �ݿø�

using namespace std;

/*
1. �� porgresses���� speed�� ���� �󸶳� �ɸ����� ���ϰ�, �迭�� ����
2. �迭�� ù��°�� ���� ���� �ɸ��� ���� ����(max_day)
3. max_day�� �迭�� ���ؼ�, max_day�� ��� �� ũ�ų� ������ cnt++, 
   ������ answer�迭�� cnt �����ϰ�, cnt �ʱ�ȭ�Ѵ���, max_day�� ���� ���ҷ� ������Ʈ
4. *���̻� ���� ���Ұ� ���� ���, ���� cnt�� answer �迭�� ����*
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