
//플로이드 알고리즘의 구현
#include <iostream>
using namespace std;
/*첫 번째 줄에 정점의 개수 N과 간선의 개수 M이 주어진다.

정점의 번호는 1번부터 N번까지로 가정한다.

두 번째 줄부터 M개의 간선의 정보가 주어진다.

각 간선의 정보 u v w는 각각 간선의 출발 정점 u, 도착 정점 v, 해당 간선의 가중치 w로 주어진다.

모든 간선의 정보가 주어진 후에 다음 줄에 출발/도착 정점의 쌍의 개수 T가 주어진다.

그 다음 줄부터 T개의 출발/도착 정점의 쌍이 주어진다.*/
#define INF 999

int W[INF][INF];
int D[INF][INF];
int P[INF][INF];
int ta[INF];
int ts[INF];
int path[INF][INF];

void init(int N) // dist 배열 초기화
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            D[i][j] = i == j ? 0 : INF;
            P[i][j] = 0;
        }
    }
}
void floyd2(int N, int (*D)[INF])
{

    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (D[i][j] > D[i][k] + D[k][j])
                {
                    P[i][j] = k; //이때의 k를 p에 저장함
                    D[i][j] = D[i][k] + D[k][j];
                } // min 함수 사용 대체
}

void print_path(int i, int j)
{
    int k = P[i][j];
    if (k)
    {
        print_path(i, k);
        cout << k;
        printf(" ");
        print_path(k, j);
    }
}

int main()
{

    int x, y, z;
    int N, M, T;
    // Input
    cin >> N; //정점의 개수
    cin >> M; //간선의 개수

    init(N);
    // Input : 간선의 수만큼 간선과 연결된 정점과 해당 간선의 가중치 입력
    for (int i = 0; i < M; i++)
    {
        cin >> x; // 간선의 출발정점
        cin >> y; // 간선의 도착정점
        cin >> z; // 해당 간선의 가중치

        if (D[x][y] > z)
            D[x][y] = z;
    }

    cin >> T; // 출발/도착 정점의 쌍의 개수

    for (int i = 0; i < T; i++)
    {
        cin >> ts[i];
        cin >> ta[i]; // 출발 /도착 정점의 쌍
    }

    // =============== input 종료 =====================

    floyd2(N, D);

    // D 출력
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cout << D[i][j];
            //  printf(" ");
        }

        cout << endl;
    }
    // P 출력
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cout << P[i][j];
            // printf(" ");
            if (j != N)
            {
                printf(" ");
            }
        }
        cout << endl;
    }

    //최단 경로 출력하기(T개)
    for (int i = 0; i < T; i++)
    {
        if (D[ts[i]][ta[i]] == INF)
        {
            cout << "NONE" << endl;
            continue;
        } //최단 경로가 없으면 none출력
        cout << ts[i] << " ";

        print_path(ts[i], ta[i]); //최단경로 출력 함수
        cout << ta[i];
        cout << endl;
    }
}