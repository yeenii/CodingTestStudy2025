#include<iostream>
#include <string>
#include <vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

bool compareGenre(pair<string, int> v1, pair<string, int> v2)
{
    return v1.second > v2.second; //내림차순

}

bool compareSongs(pair<int, int> v1, pair<int, int> v2)
{
    // 장르 내 재생 횟수가 같은 노래 중 고유 번호가 낮은 노래 부터
    if (v1.second == v2.second)
        v1.first < v2.first; //오름차순
    return v1.second > v2.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    unordered_map<string, int> album; //1. 속한 노래가 가장 많이 재생된 장르

    //1. 속한 노래가 가장 많이 재생된 장르
    for (int i = 0; i < genres.size(); i++)
    {
        album[genres[i]] += plays[i];
    }

    vector<pair<string, int>> album_vec(album.begin(), album.end()); //map은 순서가 없음. 정렬을 위해 vector로 변경
   
    sort(album_vec.begin(), album_vec.end(),compareGenre);
    
    //2. 장르 내 가장 많이 재생된 노래
    unordered_map<string, vector<pair<int, int>>> dic_play;

    for (int j = 0; j < genres.size(); j++)
    {
        dic_play[genres[j]].push_back({j,plays[j]});
    }

    for (auto album_v : album_vec) //장르별로
    {
        auto songs = dic_play[album_v.first]; //songs에 {고유번호, plays} 저장
        sort(songs.begin(), songs.end(), compareSongs); // 장르 내 가장 많이 재생된 노래. 장르내 재생 횟수가 같은 노래 중 고유 번호가 낮은 노래 부터
    
        //3. 장르에 속한 곡이 하나라면 하나의 곡 선택. -> 최대 2곡인데, 한곡만 있으면 한곡 선택 - min(2,(int)songs.size()) 사용
        for (int i = 0; i < min(2,(int)songs.size()); i++)
        {
            answer.push_back(songs[i].first);
        }
    }


    return answer;
}

int main()
{
    vector<string> genres = { "classic", "pop", "classic", "classic", "pop" };
    vector<int> plays = { 500, 600, 150, 800, 2500 };

    auto result = solution(genres, plays);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

	return 0;
}