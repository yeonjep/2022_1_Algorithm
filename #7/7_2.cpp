#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 0xffff

/*
출력값은 그리디 알고리즘의 각 단계별로 touch 배열의 변화를 출력하고,

F 집합에 추가되는 간선을 순서대로 출력한다.

단, 출발 정점은 1번 정점으로 가정하였으므로,
이후로 주어지는 정점 번호에 대해서 1번 정점으로부터 해당 정점으로 가능 최단 경로를 출력한다

*/
typedef vector<vector<int>> matrix_t;
// typedef vector<int> matrix1;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;
set_of_edges F;
edge_t pa;
void dijkstra(int n, matrix_t &W, set_of_edges &F)
{
    int vnear, minValue;
    vector<int> touch(n + 1), length(n + 1);
    F.clear();
    for (int i = 2; i <= n; i++)
    {
        touch[i] = 1;
        length[i] = W[1][i];
    }

    for (int d = 2; d <= n; d++)
    {

        (d == n) ? cout << touch[d] << endl : cout << touch[d] << " ";
    }
    for (int h = 1; h <= n - 1; h++)
    {
        minValue = INF;
        for (int i = 2; i <= n; i++)
            if (0 <= length[i] && length[i] < minValue)
            {
                minValue = length[i];
                vnear = i;
            }
        // e= edge from vertex indexed by touch
        // add e to F
        F.push_back(make_pair(touch[vnear], vnear));

        for (int i = 2; i <= n; i++)
            if (length[i] > length[vnear] + W[vnear][i])
            {
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        length[vnear] = -1;

        for (int d = 2; d <= n; d++)
        {

            (d == n) ? cout << touch[d] << endl : cout << touch[d] << " ";
        }
    }
}

void print2(int a, set_of_edges &P)
{
}
void print1(int T, vector<int> &Tvec)
{
    set_of_edges P;
    int g = 0;
    while (g < T)
    {
        P.clear();

        print2(Tvec[g], P);

        for (edge_t e : P)
        {
            (e.second == Tvec[g]) ? cout << e.first << " " << e.second << endl : cout << e.first << " ";
        }
        g++;
    }
}
int main()
{

    int n, m; //정점의 개수, 간선의 개수
    cin >> n >> m;

    matrix_t W(100, vector<int>(100, INF));

    vector<int> x(50, 0);
    vector<int> y(50, 0);
    vector<int> z(50, 0);
    for (int i = 0; i < m; i++)
    {
        cin >> x[i] >> y[i] >> z[i];
        W[x[i]][y[i]] = z[i];
    }

    // 정점의 개수 T
    int T;
    cin >> T;
    vector<int> Tvec(100, 0);
    for (int i = 0; i < T; i++)
    {
        cin >> Tvec[i];
    }

    dijkstra(n, W, F); //-> touch 값 출력

    for (edge_t e : F)
    {
        cout << e.first << " " << e.second << " " << W[e.first][e.second] << endl;
    }
    int g = 0;

    print1(T, Tvec);

    return 0;
}