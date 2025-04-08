#include <string>
#include <vector>
#include<unordered_set>
#include <iostream>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;

    unordered_set<string> hash;

    answer.assign(2,0); //0���� �ʱ�ȭ

    /*for (int i = 0; i < words.size(); i++)
    {
        hash.insert(words[i]);
    }*/

    hash.insert(words[0]);

    for (int i = 1; i < words.size(); i++)
    {
        //�ߺ��� ���
        if (!hash.insert(words[i]).second) // true -> ó�� ���� �ܾ�, false -> �ߺ� �ܾ�. !�� �� �ٿ��� ��
        {
            answer[0] = i % n + 1;
            answer[1] = i / n + 1;
            break;
        }

        //�����ձ�
        if (words[i-1].back() != words[i].front()) //i+1���� ���� �� �ֱ� ������, i-1�� �ϴ°� ����
        {
            answer[0] = i % n + 1;
            answer[1] = i / n + 1;
            break;
        }

        //�ߺ�����, �����ձ⸦ ������ ����� �� ��� [0,0] return

    }
    

    return answer;
}


int main()
{
    int n=3;
    vector<string> words = { "tank", "kick", "know", "wheel", "land", "dream", "mother", "robot", "tank" };

    auto result = solution(n, words);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

	return 0;
}