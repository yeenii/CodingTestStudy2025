#include <iostream>
#include<limits> //std::numeric_limits<int>::max()
#include<vector> //vector
#include<algorithm> //sort()
using namespace std;

const int MAX_CONTAINER = 20; //N
const int MAX_MICRO = 51; //Q

int containerSize; //8
int experimentCount; //4
int currentContainer[MAX_CONTAINER][MAX_CONTAINER]; //  {셀 위치, microId}
bool visited[MAX_CONTAINER][MAX_CONTAINER]; //방문 여부 T/F
int connectComponent[MAX_MICRO];

int r1, r2, c1, c2;

int drow[4] = { -1, 0, 1, 0 };
int dcol[4] = { 0, -1, 0, 1 };

//새로운 배양 용기 
int newContainer[MAX_CONTAINER][MAX_CONTAINER];
int microCellCount[MAX_MICRO]; //미생물 id 마다 영역 크기 저장
pair<int, int> BoundingBoxStart[MAX_MICRO]; //경계 박스 최소 {최소 행, 최소 열}
pair<int, int> BoundingBoxEnd[MAX_MICRO]; //경계 박스 최대 {최대 행, 최대 열}

//현재 미생물 무리의 연결 여부 dfs로 체크
void dfsConnect(int microId, int row, int col)
{
    // 현재 셀 방문 처리
    visited[row][col] = true;

    //현재 셀 상하좌우 이동하면서 같은 미생물 id 인지 확인
    for (int i = 0; i < 4; i++)
    {
        int neighRow = row + drow[i]; // -1, 0 , 1, 0
        int neighCol = col + dcol[i]; // 0, -1, 0, 1

        //영역 벗어나는지 체크
        if (neighRow >= containerSize || neighRow < 0 || neighCol >= containerSize || neighCol < 0)
            continue;

        //방문 여부 
        if (visited[neighRow][neighCol])
            continue;

        //현재 셀과 다른 id의 셀 
        if (currentContainer[neighRow][neighCol] != microId)
            continue;

        dfsConnect(microId, neighRow, neighCol); //재귀로 이웃 셀 방문

    }



}

void containerInput(int microId, int r1, int c1, int r2, int c2) // experimentCount  = microId = 미생물 무리 id
{
    //1. 전체 배양 용기 방문 여부 false로 초기화 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            visited[row][col] = false;
        }
    }

    //2. 미생물 무리 이어져 있는지 알 수 있는 연결 컴포넌트 초기화 
    // microId 만큼 크기로 배열 생성 -> 0으로 초기화
    for (int id = 1; id <= microId; id++)
    {
        connectComponent[id] = 0;

    }

    //3. (r1, c1), (r2, c2) 좌표 만큼 새로운 미생물로 덮음
    for (int row = r1; row < r2; row++) //2 ~ 5-1
    {
        for (int col = c1; col < c2; col++) // 3 ~ 8-1
        {
            currentContainer[row][col] = microId; //microId 2로 입력
        }
    }



    //4. 무리가 나눠져 있는지 확인 
    // 배양 용기 전체 순회 
    for (int row = 0; row < containerSize; row++) //8
    {
        for (int col = 0; col < containerSize; col++) //8
        {
            //배양 용기 안에 현재 셀의 id가 0일 경우 건너뛰기
            if (currentContainer[row][col] == 0)
            {
                continue;
            }

            //이미 방문한 셀이면 넘어가기
            if (visited[row][col])
            {
                continue;
            }

            int currentMicroId = currentContainer[row][col]; //현재 셀의 미생물 무리 id 
            connectComponent[currentMicroId]++; //현재 셀의 미생물 무리 id 연결 컴포넌트 1 증가

            dfsConnect(currentMicroId, row, col);

        }
    }

    //cout << "connectComponent: "<< connectComponent[1] <<endl;

    //5. 연결된 컴포넌트가 2 이상이면 해당 미생물 무리 제거
    for (int id = 1; id <= microId; id++) //전체 미생물 무리 순회
    {
        if (connectComponent[id] >= 2) //2 이상이면
        {
            //미생물 무리 제거
            //전체 배양용기 순회하면서
            for (int row = 0; row < containerSize; row++)
            {
                for (int col = 0; col < containerSize; col++)
                {
                    if (currentContainer[row][col] == id) //배양 용기에 들은 현재 셀의 id가 일치할 경우
                        currentContainer[row][col] = 0; //제거
                }
            }

        }

    }


}

void newContainerMove(int microId)
{
    //1. 영역이 큰 미생물 무리 부터 정렬
    //새로운 배양 용기 초기화 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            newContainer[row][col] = 0;
        }
    }

    //2. 기존 용기 순회하며 미생물 무리마다 영역 카운트
    //*미생물 무리 마다의 영역 모양 유지해야 함 -> 경계 박스 설정 

    // 각 미생물 무리의 셀 개수 초기화 & 경계 박스 초기화 
    for (int id = 1; id <= microId; id++)
    {
        //각 미생물 무리의 셀 개수 초기화
        microCellCount[id] = 0;

        //경계 박스 초기화 
        BoundingBoxStart[id] = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() }; //최소 좌표를 최댓값으로 초기화
        BoundingBoxEnd[id] = { std::numeric_limits<int>::min(), std::numeric_limits<int>::min() }; //최대 좌표에 최솟값으로 초기화

    }

    //전체 순회
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {

            int currentMicroId = currentContainer[row][col]; //현재 미생물 무리의 id

            //빈 셀은 건너뛰기
            if (currentContainer[row][col] == 0)
                continue;

            //현재 미생물 무리의 셀 개수를 1 증가 
            microCellCount[currentMicroId]++;

            //경계 박스의 최소 좌표/ 최대 좌표 업데이트
            BoundingBoxStart[currentMicroId].first = min(BoundingBoxStart[currentMicroId].first, row); //최소 행
            BoundingBoxStart[currentMicroId].second = min(BoundingBoxStart[currentMicroId].second, col); //최소 열
            BoundingBoxEnd[currentMicroId].first = max(BoundingBoxEnd[currentMicroId].first, row); //최대 행
            BoundingBoxEnd[currentMicroId].second = max(BoundingBoxEnd[currentMicroId].second, col); //최대 열 

        }
    }
    //cout << "microcellCount:"<< microCellCount[2] <<endl;
    //cout << "최소행:"<< BoundingBoxStart[2].first <<endl;
    //cout << "최소열:"<< BoundingBoxStart[2].second <<endl;
    //cout << "최대행:"<< BoundingBoxEnd[2].first <<endl;
    //cout << "최대열:"<< BoundingBoxEnd[2].second <<endl;

    //3. 미생물 무리 배치 순서 정하기 - 기존 용기 
    vector<pair<int, int>> relocationMicro; //{-미생물 크기, id}

    for (int id = 1; id <= microId; id++)
    {
        //** 세번째 실험에서 microCellCount[0]인 미생물 무리가 제거되면서 다 빈 셀이 되는데, 이를 다 microCellCount[0]에 저장하려 하면 런타임에러 남.
        //빈 셀은 건너뛰기 
        if (microCellCount[id] == 0)
            continue;

        relocationMicro.push_back({ -microCellCount[id],id }); //정렬 쉽게 하기 위해서 -미생물 크기 //**매번 다른 미생물 무리 id 넣어줬어야 했는데, microId를 넣어버려 오류 생김
    }
    sort(relocationMicro.begin(), relocationMicro.end()); //정렬


    //4. 정렬된 순서에 따라 / 미생물 id에 따라 미생물 무리의 행, 열 크기 구함 
    for (auto locMicro : relocationMicro)
    {
        int currentMicroId = locMicro.second;

        //행, 열 칸 수 구하기 
        int MicroRow = BoundingBoxEnd[currentMicroId].first - BoundingBoxStart[currentMicroId].first + 1; //ex) (2, 3)과 (4,6)일 때, 3칸이므로, 4-2+1 = 3
        int MicroCol = BoundingBoxEnd[currentMicroId].second - BoundingBoxStart[currentMicroId].second + 1;

        //cout << "row:"<< MicroRow << "col:" << MicroCol <<endl;

        //5. 새 배양 용기에 현재 미생물 무리 배치할 위치 탐색 

        //배치 가능한 가장 작은 x, y 좌표 
        // x, y 좌표에서 가장 작은 위치 = row<= cotainerSize - MicroRow
        for (int newRow = 0; newRow <= containerSize - MicroRow; newRow++)
        {
            bool placeCurrentMicroFinish = false; //현재 미생물 무리 배치 완료했는지

            for (int newCol = 0; newCol <= containerSize - MicroCol; newCol++)
            {
                bool canPlace = true; //현재 위치에 배치할 수 있는지 

                //현재 미생물 무리의 모양을 유지하며 해당 위치에 배치할 수 있는지 확인 
                // 조건: 원래 배양용기에서 현재 위치가 다른 미생물의 위치가 아닌지, 새 배양용기가 비어있지 않다면 
                for (int dr = 0; dr < MicroRow; dr++)
                {
                    for (int dc = 0; dc < MicroCol; dc++)
                    {
                        int originalRow = BoundingBoxStart[currentMicroId].first + dr;
                        int originalCol = BoundingBoxStart[currentMicroId].second + dc;

                        if (currentContainer[originalRow][originalCol] != currentMicroId)
                            continue;

                        if (newContainer[newRow + dr][newCol + dc] != 0) //빈셀이 아니라면
                        {
                            canPlace = false;
                            break;

                        }
                    }

                    if (!canPlace)
                        break;
                }


                if (canPlace)
                {
                    //현재 위치에 배치 가능한 경우, 이 위치에 복사 
                    for (int dr = 0; dr < MicroRow; dr++)
                    {
                        for (int dc = 0; dc < MicroCol; dc++)
                        {
                            //경계 박스의 최소, 최대 좌표서 부터 복붙 
                            int originalRow = BoundingBoxStart[currentMicroId].first + dr;
                            int originalCol = BoundingBoxStart[currentMicroId].second + dc;

                            //만약 현재 미생물 무리가 아닐 경우 건너뛰기
                            if (currentContainer[originalRow][originalCol] != currentMicroId)
                                continue;

                            //**배치 가능한 위치에 현재 미생물 무리 복사 
                            newContainer[newRow + dr][newCol + dc] = currentMicroId;

                        }
                    }

                    //현재 미생물 무리가 다 배치되었으므로 반복문 탈.출. 
                    placeCurrentMicroFinish = true;
                    break;

                }
            }

            //현재 행에서 미생물 무리 배치 다 했다면, 현재 행 탐색하지 않음 
            if (placeCurrentMicroFinish)
                break;

        }
    }

    //새로운 배양 용기를 기존 용기로 업데이트
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            currentContainer[row][col] = newContainer[row][col];
        }
    }

}

void draweExperimentResult(int microId)
{

    bool isAdjacent[MAX_MICRO][MAX_MICRO] = { false }; //다차원 배열이므로 {}로 초기화해줘야 함. //두 미생물 무리의 인접 확인하는 변수 

    //전체 순회하며 인접한지 확인 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            //현재 셀이 빈 셀일 경우 건너뛰기 
            if (currentContainer[row][col] == 0)
                continue;

            //4방향 인접 셀 확인 
            for (int i = 0; i < 4; i++)
            {
                int neighRow = row + drow[i]; // -1, 0 , 1, 0
                int neighCol = col + dcol[i]; // 0, -1, 0, 1

                //영역 벗어나는지 체크
                if (neighRow >= containerSize || neighRow < 0 || neighCol >= containerSize || neighCol < 0) //**containerSize부터 큰 좌표가 안됨. 0부터 7까지 영역 설정했으니까
                    continue;

                //인접 셀이 빈셀일 경우 건너뛰기
                if (currentContainer[neighRow][neighCol] == 0)
                    continue;

                //현재 셀과 이웃 셀이 다른 미생물 무리일 경우 
                if (currentContainer[row][col] != currentContainer[neighRow][neighCol])
                {
                    int diffA = currentContainer[row][col];
                    int diffB = currentContainer[neighRow][neighCol];

                    //미생물 무리 A-B, B-A 인접한 것 확인 
                    isAdjacent[diffA][diffB] = true;
                    isAdjacent[diffB][diffA] = true;
                }

            }

        }
    }


    int experimentResult = 0; // 곱한 결과 
    //인접한 미생물 무리 끼리의 곱 구하기 
    // 각 미생물 무리 id마다 한번씩만 계산하도록 diffA , diffB = diffA+1 에서 시작 
    for (int diffA = 1; diffA <= microId; diffA++)
    {
        for (int diffB = diffA + 1; diffB <= microId; diffB++) //**diffB++ 까먹음
        {
            if (isAdjacent[diffA][diffB])
            {
                experimentResult += microCellCount[diffA] * microCellCount[diffB];

            }

        }
    }

    cout << experimentResult << endl;

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> containerSize >> experimentCount; //N, Q /8, 4

    //NXN 배양용기 초기화 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            currentContainer[row][col] = 0;

        }
    }

    // 실험 횟수 만큼 
    //미생물 무리 투입 / 배양 용기 이동 / 실험 결과
    for (int i = 1; i <= experimentCount; i++) //1~ 4
    {
        cin >> r1 >> c1 >> r2 >> c2; // 투입되는 미생물 무리 모양 좌표 r1, r2, c1, c2 입력 // 2, 2, 5, 6 

        // 1. 미생물 투입
        containerInput(i, r1, c1, r2, c2); //1, 2, 2, 5, 6

        //2. 배양 용기 이동 
        newContainerMove(i);

        //3. 실험 결과 
        draweExperimentResult(i);

    }

    return 0;
}
