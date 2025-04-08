/* 문제 28: 이진탐색트리 - 전위순회, 중위순회, 후위순회 

1. 전위, 중위, 후위에 대한 함수 생성
2. 노드 배열과 인덱스 번호 0 넘겨줌
3. 만약 인덱스 번호 보다 노드 배열 크기가 크다면
4. 왼쪽, 오른쪽 각 순회하도록 인덱스 계산 & 재귀 함수 활용
5. 결과는 string으로 저장

6. 맨 뒤에 " " 공백을 제거
7. result 배열에 전위, 중위, 후위 순회 결과를 저장 및 출력

*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


string postCompute(vector<int> nodes, int idx)
{
	if (idx < nodes.size())
	{
		string ret = postCompute(nodes, idx * 2 + 1);
		ret += postCompute(nodes, idx * 2 + 2);
		ret += to_string(nodes[idx]) + " ";

		return ret;
	}

	return "";
}

string midCompute(vector<int> nodes, int idx)
{
	if (idx < nodes.size())
	{
		string ret = midCompute(nodes, idx * 2 + 1);
		ret +=  to_string(nodes[idx]) + " ";
		ret += midCompute(nodes, idx * 2 + 2);

		return ret;
	}

	return "";
}

string preCompute(vector<int> nodes, int idx)
{
	if (idx < nodes.size())
	{
		string ret = to_string(nodes[idx]) + " ";
		ret += preCompute(nodes, idx * 2 + 1);
		ret += preCompute(nodes, idx * 2 + 2);

		return ret;
	}

	return "";
}


vector<string> solution(vector<int> nodes)
{
	vector<string> result;
	
	string pre = preCompute(nodes, 0); //0부터 인덱스 시작
	string mid = midCompute(nodes, 0);
	string post = postCompute(nodes, 0);

	//맨마지막 " " 삭제
	pre.pop_back();
	mid.pop_back();
	post.pop_back();

	//result 배열에 결과 저장
	result.push_back(pre);
	result.push_back(mid);
	result.push_back(post);


	return result;
}

int main()
{
	vector<int> nodes = {1, 2, 3, 4, 5, 6, 7};

	auto result = solution(nodes);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << endl;
	}


	return 0;
}