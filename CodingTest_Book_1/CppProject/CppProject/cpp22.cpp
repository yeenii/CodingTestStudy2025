#include<iostream>
#include <string>
#include <vector>
#include<algorithm> //sort

using namespace std;


bool solution(vector<string> phone_book) {
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());

    for (int i = 1; i < phone_book.size(); i++)
    {
        if (phone_book[i-1] == phone_book[i].substr(0, phone_book[i-1].size()))
            return answer = false;
    }

    return answer = true;
}

int main()
{
    vector<string> phone_book = { "119", "97674223", "1195524421" };

    //vector<string> phone_book = { "123","456","789" };

    bool result = solution(phone_book);

    cout << result << endl;

	return 0;
}