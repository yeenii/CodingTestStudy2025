#include <string>
#include <vector>
#include<unordered_set>
#include <iostream>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;

    unordered_set<string> hash;

    answer.assign(2,0); //0으로 초기화

    /*for (int i = 0; i < words.size(); i++)
    {
        hash.insert(words[i]);
    }*/

    hash.insert(words[0]);

    for (int i = 1; i < words.size(); i++)
    {
        //중복인 경우
        if (!hash.insert(words[i]).second) // true -> 처음 보는 단어, false -> 중복 단어. !를 꼭 붙여야 함
        {
            answer[0] = i % n + 1;
            answer[1] = i / n + 1;
            break;
        }

        //끝말잇기
        if (words[i-1].back() != words[i].front()) //i+1에서 터질 수 있기 때문에, i-1로 하는게 좋음
        {
            answer[0] = i % n + 1;
            answer[1] = i / n + 1;
            break;
        }

        //중복없고, 끝말잇기를 끝까지 제대로 한 경우 [0,0] return

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