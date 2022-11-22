
//삼각형위의 최대경로
#include <iostream>
using namespace std;

int n;
int triangle[100][100], cost[100][100], record[100];
int cnt = 0;

void init() // cost 배열 -1로 초기화
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cost[i][j] = -1;
}

int path2(int x, int y) //최대 경로의 합 리턴
{
    if (y == n - 1)
        return triangle[x][y];
    int &ret = cost[x][y];

    //이미 접근해서 계산된 경로라면 그 값을 리턴
    if (ret != -1)
        return ret;

    //아래 행 바로 오른쪽 원소와 바로 아래 원소 비교

    ret = triangle[x][y] + max(path2(x + 1, y + 1), path2(x + 1, y));
    return ret;
}

void calc() //경로 출력
{
    int num = 0; //행 계산
    for (int i = 0; i < n; i++)
    {
        // i번째 행에서 바로 아래 원소랑 오른쪽대각선 아래 원소 비교
        record[cnt] = triangle[i][num];
        if ((num + 1 <= i) && (cost[i][num] <= cost[i][num + 1]))
        {
            num++;
            record[cnt] = triangle[i][num];
        }
        cnt++;
    }
}

int main()
{
    //입력1-첫 번째 줄에는 삼각형의 높이 n이 주어진다.
    cin >> n;

    //입력2-두 번째 줄부터 n개의 줄에 각각 삼각형의 숫자들이 주어진다.
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> triangle[i][j];
    init();

    //입력 예시
    /*
    4
    3
    7 4
    2 4 6
    8 5 9 3
    */

    //출력1-첫 번째 줄에 최대 경로의 합을 출력한다.
    cout << path2(0, 0) << endl;

    //출력2-두 번째 줄에 최대 경로를 출력한다.
    cost[n - 1][n - 1] = triangle[n - 1][n - 1];
    calc();
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << record[i] << " ";
        else
            cout << record[i] << endl;
    } // 기록된 순서대로 경로를 출력함.

    return 0;
}