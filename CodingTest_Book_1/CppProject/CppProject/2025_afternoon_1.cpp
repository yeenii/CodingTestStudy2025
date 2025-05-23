#include <iostream>
#include<limits> //std::numeric_limits<int>::max()
#include<vector> //vector
#include<algorithm> //sort()
using namespace std;

const int MAX_CONTAINER = 20; //N
const int MAX_MICRO = 51; //Q

int containerSize; //8
int experimentCount; //4
int currentContainer[MAX_CONTAINER][MAX_CONTAINER]; //  {�� ��ġ, microId}
bool visited[MAX_CONTAINER][MAX_CONTAINER]; //�湮 ���� T/F
int connectComponent[MAX_MICRO];

int r1, r2, c1, c2;

int drow[4] = { -1, 0, 1, 0 };
int dcol[4] = { 0, -1, 0, 1 };

//���ο� ��� ��� 
int newContainer[MAX_CONTAINER][MAX_CONTAINER];
int microCellCount[MAX_MICRO]; //�̻��� id ���� ���� ũ�� ����
pair<int, int> BoundingBoxStart[MAX_MICRO]; //��� �ڽ� �ּ� {�ּ� ��, �ּ� ��}
pair<int, int> BoundingBoxEnd[MAX_MICRO]; //��� �ڽ� �ִ� {�ִ� ��, �ִ� ��}

//���� �̻��� ������ ���� ���� dfs�� üũ
void dfsConnect(int microId, int row, int col)
{
    // ���� �� �湮 ó��
    visited[row][col] = true;

    //���� �� �����¿� �̵��ϸ鼭 ���� �̻��� id ���� Ȯ��
    for (int i = 0; i < 4; i++)
    {
        int neighRow = row + drow[i]; // -1, 0 , 1, 0
        int neighCol = col + dcol[i]; // 0, -1, 0, 1

        //���� ������� üũ
        if (neighRow >= containerSize || neighRow < 0 || neighCol >= containerSize || neighCol < 0)
            continue;

        //�湮 ���� 
        if (visited[neighRow][neighCol])
            continue;

        //���� ���� �ٸ� id�� �� 
        if (currentContainer[neighRow][neighCol] != microId)
            continue;

        dfsConnect(microId, neighRow, neighCol); //��ͷ� �̿� �� �湮

    }



}

void containerInput(int microId, int r1, int c1, int r2, int c2) // experimentCount  = microId = �̻��� ���� id
{
    //1. ��ü ��� ��� �湮 ���� false�� �ʱ�ȭ 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            visited[row][col] = false;
        }
    }

    //2. �̻��� ���� �̾��� �ִ��� �� �� �ִ� ���� ������Ʈ �ʱ�ȭ 
    // microId ��ŭ ũ��� �迭 ���� -> 0���� �ʱ�ȭ
    for (int id = 1; id <= microId; id++)
    {
        connectComponent[id] = 0;

    }

    //3. (r1, c1), (r2, c2) ��ǥ ��ŭ ���ο� �̻����� ����
    for (int row = r1; row < r2; row++) //2 ~ 5-1
    {
        for (int col = c1; col < c2; col++) // 3 ~ 8-1
        {
            currentContainer[row][col] = microId; //microId 2�� �Է�
        }
    }



    //4. ������ ������ �ִ��� Ȯ�� 
    // ��� ��� ��ü ��ȸ 
    for (int row = 0; row < containerSize; row++) //8
    {
        for (int col = 0; col < containerSize; col++) //8
        {
            //��� ��� �ȿ� ���� ���� id�� 0�� ��� �ǳʶٱ�
            if (currentContainer[row][col] == 0)
            {
                continue;
            }

            //�̹� �湮�� ���̸� �Ѿ��
            if (visited[row][col])
            {
                continue;
            }

            int currentMicroId = currentContainer[row][col]; //���� ���� �̻��� ���� id 
            connectComponent[currentMicroId]++; //���� ���� �̻��� ���� id ���� ������Ʈ 1 ����

            dfsConnect(currentMicroId, row, col);

        }
    }

    //cout << "connectComponent: "<< connectComponent[1] <<endl;

    //5. ����� ������Ʈ�� 2 �̻��̸� �ش� �̻��� ���� ����
    for (int id = 1; id <= microId; id++) //��ü �̻��� ���� ��ȸ
    {
        if (connectComponent[id] >= 2) //2 �̻��̸�
        {
            //�̻��� ���� ����
            //��ü ����� ��ȸ�ϸ鼭
            for (int row = 0; row < containerSize; row++)
            {
                for (int col = 0; col < containerSize; col++)
                {
                    if (currentContainer[row][col] == id) //��� ��⿡ ���� ���� ���� id�� ��ġ�� ���
                        currentContainer[row][col] = 0; //����
                }
            }

        }

    }


}

void newContainerMove(int microId)
{
    //1. ������ ū �̻��� ���� ���� ����
    //���ο� ��� ��� �ʱ�ȭ 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            newContainer[row][col] = 0;
        }
    }

    //2. ���� ��� ��ȸ�ϸ� �̻��� �������� ���� ī��Ʈ
    //*�̻��� ���� ������ ���� ��� �����ؾ� �� -> ��� �ڽ� ���� 

    // �� �̻��� ������ �� ���� �ʱ�ȭ & ��� �ڽ� �ʱ�ȭ 
    for (int id = 1; id <= microId; id++)
    {
        //�� �̻��� ������ �� ���� �ʱ�ȭ
        microCellCount[id] = 0;

        //��� �ڽ� �ʱ�ȭ 
        BoundingBoxStart[id] = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() }; //�ּ� ��ǥ�� �ִ����� �ʱ�ȭ
        BoundingBoxEnd[id] = { std::numeric_limits<int>::min(), std::numeric_limits<int>::min() }; //�ִ� ��ǥ�� �ּڰ����� �ʱ�ȭ

    }

    //��ü ��ȸ
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {

            int currentMicroId = currentContainer[row][col]; //���� �̻��� ������ id

            //�� ���� �ǳʶٱ�
            if (currentContainer[row][col] == 0)
                continue;

            //���� �̻��� ������ �� ������ 1 ���� 
            microCellCount[currentMicroId]++;

            //��� �ڽ��� �ּ� ��ǥ/ �ִ� ��ǥ ������Ʈ
            BoundingBoxStart[currentMicroId].first = min(BoundingBoxStart[currentMicroId].first, row); //�ּ� ��
            BoundingBoxStart[currentMicroId].second = min(BoundingBoxStart[currentMicroId].second, col); //�ּ� ��
            BoundingBoxEnd[currentMicroId].first = max(BoundingBoxEnd[currentMicroId].first, row); //�ִ� ��
            BoundingBoxEnd[currentMicroId].second = max(BoundingBoxEnd[currentMicroId].second, col); //�ִ� �� 

        }
    }
    //cout << "microcellCount:"<< microCellCount[2] <<endl;
    //cout << "�ּ���:"<< BoundingBoxStart[2].first <<endl;
    //cout << "�ּҿ�:"<< BoundingBoxStart[2].second <<endl;
    //cout << "�ִ���:"<< BoundingBoxEnd[2].first <<endl;
    //cout << "�ִ뿭:"<< BoundingBoxEnd[2].second <<endl;

    //3. �̻��� ���� ��ġ ���� ���ϱ� - ���� ��� 
    vector<pair<int, int>> relocationMicro; //{-�̻��� ũ��, id}

    for (int id = 1; id <= microId; id++)
    {
        //** ����° ���迡�� microCellCount[0]�� �̻��� ������ ���ŵǸ鼭 �� �� ���� �Ǵµ�, �̸� �� microCellCount[0]�� �����Ϸ� �ϸ� ��Ÿ�ӿ��� ��.
        //�� ���� �ǳʶٱ� 
        if (microCellCount[id] == 0)
            continue;

        relocationMicro.push_back({ -microCellCount[id],id }); //���� ���� �ϱ� ���ؼ� -�̻��� ũ�� //**�Ź� �ٸ� �̻��� ���� id �־����� �ߴµ�, microId�� �־���� ���� ����
    }
    sort(relocationMicro.begin(), relocationMicro.end()); //����


    //4. ���ĵ� ������ ���� / �̻��� id�� ���� �̻��� ������ ��, �� ũ�� ���� 
    for (auto locMicro : relocationMicro)
    {
        int currentMicroId = locMicro.second;

        //��, �� ĭ �� ���ϱ� 
        int MicroRow = BoundingBoxEnd[currentMicroId].first - BoundingBoxStart[currentMicroId].first + 1; //ex) (2, 3)�� (4,6)�� ��, 3ĭ�̹Ƿ�, 4-2+1 = 3
        int MicroCol = BoundingBoxEnd[currentMicroId].second - BoundingBoxStart[currentMicroId].second + 1;

        //cout << "row:"<< MicroRow << "col:" << MicroCol <<endl;

        //5. �� ��� ��⿡ ���� �̻��� ���� ��ġ�� ��ġ Ž�� 

        //��ġ ������ ���� ���� x, y ��ǥ 
        // x, y ��ǥ���� ���� ���� ��ġ = row<= cotainerSize - MicroRow
        for (int newRow = 0; newRow <= containerSize - MicroRow; newRow++)
        {
            bool placeCurrentMicroFinish = false; //���� �̻��� ���� ��ġ �Ϸ��ߴ���

            for (int newCol = 0; newCol <= containerSize - MicroCol; newCol++)
            {
                bool canPlace = true; //���� ��ġ�� ��ġ�� �� �ִ��� 

                //���� �̻��� ������ ����� �����ϸ� �ش� ��ġ�� ��ġ�� �� �ִ��� Ȯ�� 
                // ����: ���� ����⿡�� ���� ��ġ�� �ٸ� �̻����� ��ġ�� �ƴ���, �� ����Ⱑ ������� �ʴٸ� 
                for (int dr = 0; dr < MicroRow; dr++)
                {
                    for (int dc = 0; dc < MicroCol; dc++)
                    {
                        int originalRow = BoundingBoxStart[currentMicroId].first + dr;
                        int originalCol = BoundingBoxStart[currentMicroId].second + dc;

                        if (currentContainer[originalRow][originalCol] != currentMicroId)
                            continue;

                        if (newContainer[newRow + dr][newCol + dc] != 0) //���� �ƴ϶��
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
                    //���� ��ġ�� ��ġ ������ ���, �� ��ġ�� ���� 
                    for (int dr = 0; dr < MicroRow; dr++)
                    {
                        for (int dc = 0; dc < MicroCol; dc++)
                        {
                            //��� �ڽ��� �ּ�, �ִ� ��ǥ�� ���� ���� 
                            int originalRow = BoundingBoxStart[currentMicroId].first + dr;
                            int originalCol = BoundingBoxStart[currentMicroId].second + dc;

                            //���� ���� �̻��� ������ �ƴ� ��� �ǳʶٱ�
                            if (currentContainer[originalRow][originalCol] != currentMicroId)
                                continue;

                            //**��ġ ������ ��ġ�� ���� �̻��� ���� ���� 
                            newContainer[newRow + dr][newCol + dc] = currentMicroId;

                        }
                    }

                    //���� �̻��� ������ �� ��ġ�Ǿ����Ƿ� �ݺ��� Ż.��. 
                    placeCurrentMicroFinish = true;
                    break;

                }
            }

            //���� �࿡�� �̻��� ���� ��ġ �� �ߴٸ�, ���� �� Ž������ ���� 
            if (placeCurrentMicroFinish)
                break;

        }
    }

    //���ο� ��� ��⸦ ���� ���� ������Ʈ
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

    bool isAdjacent[MAX_MICRO][MAX_MICRO] = { false }; //������ �迭�̹Ƿ� {}�� �ʱ�ȭ����� ��. //�� �̻��� ������ ���� Ȯ���ϴ� ���� 

    //��ü ��ȸ�ϸ� �������� Ȯ�� 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            //���� ���� �� ���� ��� �ǳʶٱ� 
            if (currentContainer[row][col] == 0)
                continue;

            //4���� ���� �� Ȯ�� 
            for (int i = 0; i < 4; i++)
            {
                int neighRow = row + drow[i]; // -1, 0 , 1, 0
                int neighCol = col + dcol[i]; // 0, -1, 0, 1

                //���� ������� üũ
                if (neighRow >= containerSize || neighRow < 0 || neighCol >= containerSize || neighCol < 0) //**containerSize���� ū ��ǥ�� �ȵ�. 0���� 7���� ���� ���������ϱ�
                    continue;

                //���� ���� ���� ��� �ǳʶٱ�
                if (currentContainer[neighRow][neighCol] == 0)
                    continue;

                //���� ���� �̿� ���� �ٸ� �̻��� ������ ��� 
                if (currentContainer[row][col] != currentContainer[neighRow][neighCol])
                {
                    int diffA = currentContainer[row][col];
                    int diffB = currentContainer[neighRow][neighCol];

                    //�̻��� ���� A-B, B-A ������ �� Ȯ�� 
                    isAdjacent[diffA][diffB] = true;
                    isAdjacent[diffB][diffA] = true;
                }

            }

        }
    }


    int experimentResult = 0; // ���� ��� 
    //������ �̻��� ���� ������ �� ���ϱ� 
    // �� �̻��� ���� id���� �ѹ����� ����ϵ��� diffA , diffB = diffA+1 ���� ���� 
    for (int diffA = 1; diffA <= microId; diffA++)
    {
        for (int diffB = diffA + 1; diffB <= microId; diffB++) //**diffB++ �����
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

    //NXN ����� �ʱ�ȭ 
    for (int row = 0; row < containerSize; row++)
    {
        for (int col = 0; col < containerSize; col++)
        {
            currentContainer[row][col] = 0;

        }
    }

    // ���� Ƚ�� ��ŭ 
    //�̻��� ���� ���� / ��� ��� �̵� / ���� ���
    for (int i = 1; i <= experimentCount; i++) //1~ 4
    {
        cin >> r1 >> c1 >> r2 >> c2; // ���ԵǴ� �̻��� ���� ��� ��ǥ r1, r2, c1, c2 �Է� // 2, 2, 5, 6 

        // 1. �̻��� ����
        containerInput(i, r1, c1, r2, c2); //1, 2, 2, 5, 6

        //2. ��� ��� �̵� 
        newContainerMove(i);

        //3. ���� ��� 
        draweExperimentResult(i);

    }

    return 0;
}
