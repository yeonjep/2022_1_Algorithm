//외판원 순회 문제와 동적계획법(TSP, DP)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define INF 999

using namespace std;

typedef vector<vector<int>> matrix;
typedef vector<int> ary;

int n, m, minlength;
matrix D, P;
// W : 인접행렬
// V : 정점 집합
// A : V의 부분집합
// D[vi][A] : A라는 부분집합을 한번씩만 거쳐 지나가는 && vi에서 v1(출발점) 으로 가는 가장 짧은 length
// A가 공집합이면 아무것도 거치지 않고 v1으로 감 (W[vi][1]과 같음)

int diff(int A, int j)
{
    return (A & ~(1 << (j - 2)));
}
int count(int A) // 1이 몇개인지
{
    int cnt = 0;
    for (; A != 0; A >>= 1)
        if (A & 1)
            cnt++;
    return cnt;
}
bool isIn(int i, int A) // 1이 포함되어 있는지를 탐색
{
    return (A & (1 << (i - 2))) != 0;
}
int minimum(int n, int i, int &minJ, int A, matrix &W, matrix &D) // minimum & Set difference
{                                                                 //-> 참조 int 형 변수는 뭐가 다른거?
    int minV = INF, value;
    for (int j = 2; j <= n; j++)
    {
        if (!isIn(j, A))
            continue;
        int value = W[i][j] + D[j][diff(A, j)];
        if (minV > value)
        {
            minV = value;
            minJ = j;
        }
    }
    return minV;
}

void travel(int n, matrix &W, matrix &P, matrix &D, int &minlength) // D 추가함
{                                                                   // P : optimal path를 담음
    int i, j, k, A;

    int subset_size = pow(2, n - 1);
    for (i = 2; i <= n; i++)
    {
        D[i][0] = W[i][1]; //복사 해줌
    }

    for (k = 1; k <= n - 2; k++) // v1과 vj를 제외
        for (A = 0; A < subset_size; A++)
        {
            if (count(A) != k) // A가 가진 1의 개수 count ->  함수 구현
                continue;
            for (i = 2; i <= n; i++)
            {
                if (isIn(i, A)) //포함 되어 있으면
                    continue;
                D[i][A] = minimum(n, i, j, A, W, D); //마지막->optimal value를 담고 있음
                P[i][A] = j;                         // optimal tour를 담고 있음.
            }
        }
    A = subset_size - 1;
    D[1][A] = minimum(n, 1, j, A, W, D);
    P[1][A] = j;
    minlength = D[1][A];
}

void tour(int v, int A, matrix &P)
{
    int k = P[v][A];
    if (A == 0)
        cout << "1";
    else
    {
        cout << k << " ";
        tour(k, diff(A, k), P);
    }
}

int main(void)
{
    cin >> n >> m; //그래프 정점, 간선의 개수
    int u, v, w;

    matrix W(n + 1, ary(n + 1, INF));
    matrix D(n + 1, ary(n + 1, INF));

    matrix P(n + 1, ary(n + 1, INF));

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        W[u][v] = w;
    }
    travel(n, W, P, D, minlength);

    cout << minlength << endl;
    cout << "1 ";
    tour(1, pow(2, n - 1) - 1, P);
    cout << endl;
    // 최적 경로 출력

    // i,j,D[i][j]( * 무한대가 아닌 D[i][j]) 출력
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < pow(2, n - 1); j++)
        {
            if (D[i][j] != INF && D[i][j] > 0)
            {
                cout << i << " " << j << " " << D[i][j] << endl;
            }
        }
    }

    return 0;
}