#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(pair<double,int> a, pair<double, int> b)
{
	//실패율 내림차순 정렬 (실패율이 같을 경우, 스테이지번호가 작은 순)
	if (a.first == b.first)
		return a.second < b.second;

	return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages)
{
	vector<int> stage; //각 스테이지마다의 클리어하지 못한 사용자 수
	vector<pair<double, int>> failure; // 실패율과 스테이지 번호 저장

	int playersNum = stages.size(); //stages의 크기

	stage.assign(N+1, 0); //크기가 5인 배열. n-1 까지 

	sort(stages.begin(), stages.end()); // stages 오름차순 정렬. [1, 2, 2, 2, 3, 3, 4, 6]

	for (int i = 1; i <= N; i++) //스테이지 개수: 1~5
	{
		stage[i] = count(stages.begin(), stages.end(), i); //각 스테이지 마다 클리어 하지 못한 사용자 수. [1,3, 2,1,0]
		
		//스테이지에 도달한 유저가 없는 경우, 해당 스테이지의 실패율은 0
		if (playersNum > 0)
		{
			double failRate = (double)stage[i] / playersNum; // 실패율. double로 전환. ex) 1/8
			failure.push_back({ failRate,i }); // 각 스테이지 번호마다 실패율 저장. ex) {1,1}
			playersNum -= stage[i]; // 패턴: stages의 개수 -= 클리어하지 못한 사용자 수
		}
		else
		{
			failure.push_back({ 0, i });
		}

	}
	
	sort(failure.begin(), failure.end(), compare);
	
	vector<int> answer;

	for (auto p : failure)
	{
		answer.push_back(p.second); // 스테이지 번호만
	}

	return answer;
}

int main()
{
	vector<int> stages = { 2, 1, 2, 6, 2, 4, 3, 3 };
	//vector<int> stages = { 4, 4, 4, 4 };

	auto result = solution(5, stages); // auto를 사용하여 자동 감지

	for (auto it = result.begin(); it != result.end(); it++) // 벡터 정렬된거 출력
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}