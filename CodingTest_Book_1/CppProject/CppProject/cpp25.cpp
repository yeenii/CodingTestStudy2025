#include<iostream>
#include <string>
#include <vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

bool compareGenre(pair<string, int> v1, pair<string, int> v2)
{
    return v1.second > v2.second; //��������

}

bool compareSongs(pair<int, int> v1, pair<int, int> v2)
{
    // �帣 �� ��� Ƚ���� ���� �뷡 �� ���� ��ȣ�� ���� �뷡 ����
    if (v1.second == v2.second)
        v1.first < v2.first; //��������
    return v1.second > v2.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    unordered_map<string, int> album; //1. ���� �뷡�� ���� ���� ����� �帣

    //1. ���� �뷡�� ���� ���� ����� �帣
    for (int i = 0; i < genres.size(); i++)
    {
        album[genres[i]] += plays[i];
    }

    vector<pair<string, int>> album_vec(album.begin(), album.end()); //map�� ������ ����. ������ ���� vector�� ����
   
    sort(album_vec.begin(), album_vec.end(),compareGenre);
    
    //2. �帣 �� ���� ���� ����� �뷡
    unordered_map<string, vector<pair<int, int>>> dic_play;

    for (int j = 0; j < genres.size(); j++)
    {
        dic_play[genres[j]].push_back({j,plays[j]});
    }

    for (auto album_v : album_vec) //�帣����
    {
        auto songs = dic_play[album_v.first]; //songs�� {������ȣ, plays} ����
        sort(songs.begin(), songs.end(), compareSongs); // �帣 �� ���� ���� ����� �뷡. �帣�� ��� Ƚ���� ���� �뷡 �� ���� ��ȣ�� ���� �뷡 ����
    
        //3. �帣�� ���� ���� �ϳ���� �ϳ��� �� ����. -> �ִ� 2���ε�, �Ѱ ������ �Ѱ� ���� - min(2,(int)songs.size()) ���
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