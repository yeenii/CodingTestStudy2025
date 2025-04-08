#include<iostream>
#include<unordered_set>

using namespace std;


long long hash_method(string str)
{
	int p = 31;
	long m = 1000000007;
	long long hash_val=0;

	for (char c : str)
	{
		hash_val = (hash_val * p + c) % m;
	}

	return hash_val;
}

vector<bool> solution(vector<string> string_list, vector<string> query_list)
{
	vector<bool> result;
	unordered_set<long long> hash_table;

	for (string str : string_list)
	{
		hash_table.insert(hash_method(str));
		
	}

	for (string query_str : query_list)
	{
		long long query_c= hash_method(query_str);

		bool answer = (hash_table.find(query_c) != hash_table.end());

		result.push_back(answer);
	}

	return result;
}

int main()
{
	vector<string> string_list = {"apple", "banana", "cherry"};
	vector<string> query_list = {"banana", "kwi", "melon", "apple"};

	auto result = solution(string_list, query_list);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	//°á°ú: 1 0 0 1

	return 0;
}
