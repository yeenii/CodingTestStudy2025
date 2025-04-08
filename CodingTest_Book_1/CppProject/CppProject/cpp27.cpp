#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 조합을 만드는 재귀 함수
void makeCombinations(const string& order, int courseLen, int start, string curr, unordered_map<string, int>& counter) {
    if (curr.length() == courseLen) {
        counter[curr]++;
        return;
    }
    for (int i = start; i < order.size(); ++i) {
        makeCombinations(order, courseLen, i + 1, curr + order[i], counter);
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;

    for (int len : course) {
        unordered_map<string, int> counter;
        int maxCount = 0;

        for (string order : orders) {
            sort(order.begin(), order.end()); // 알파벳 순 정렬
            makeCombinations(order, len, 0, "", counter);
        }

        for (auto& p : counter) {
            if (p.second >= 2) {
                maxCount = max(maxCount, p.second);
            }
        }

        for (auto& p : counter) {
            if (p.second == maxCount && maxCount >= 2) {
                answer.push_back(p.first);
            }
        }
    }

    sort(answer.begin(), answer.end()); // 사전순 정렬
    return answer;
}

int main() {
    vector<string> orders = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
    vector<int> course = { 2, 3, 4 };

    vector<string> result = solution(orders, course);

    for (const string& s : result) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}
