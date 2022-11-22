// Prim's Algorithm
#include <iostream>
#include <vector>
#include <utility>

#define INF 0xffff

using namespace std;
typedef vector<int> matrix1;
typedef vector<vector<int>> matrix_t;
typedef pair<int, int> edge_t;
typedef vector<pair<int, int>> set_of_edge;
set_of_edge F;

void prim(int n, matrix_t &W, set_of_edge &F)
{
    int vnear, minValue;
    vector<int> nearest(n + 1), distance(n + 1);

    F.clear(); // F를 공집합으로 선언

    for (int i = 2; i <= n; i++) // n-1개의 노드가 있고 이미 처음에 v1이 포함되어 있으므로 총 n-2번
    {
        nearest[i] = 1;
        distance[i] = W[1][i];
    }
    for (int d = 2; d <= n; d++)
    {

        (d == n) ? cout << nearest[d] << endl : cout << nearest[d] << " ";
    }
    for (int i = 1; i <= n - 1; i++)
    {
        minValue = INF;

        for (int j = 2; j <= n; j++)
            if (0 <= distance[j] && distance[j] < minValue)
            {
                minValue = distance[j];
                vnear = j; //간선의 가중치가 가장 작아지는 해당 정점의 인덱스
            }
        // e=edge connecting vertices indexed by vnear and nearest[vnear];
        // add e to F
        F.push_back(make_pair(vnear, nearest[vnear]));

        distance[vnear] = -1;

        for (int k = 2; k <= n; k++)
            if (distance[k] > W[k][vnear])
            {
                distance[k] = W[k][vnear];
                nearest[k] = vnear;
            }
        for (int d = 2; d <= n; d++)
        {

            (d == n) ? cout << nearest[d] << endl : cout << nearest[d] << " ";
        }
    }
}

int main()
{

    int n, m;      // 첫줄에 정점과 간선의 갯수가 주어진다.
    cin >> n >> m; // n : 정점의 개수, m : 간선의 개수
    vector<int> u(50, 0);
    vector<int> v(50, 0);
    vector<int> w(50, 0);
    // 두번째 줄부터 m개의 간선정보가 주어진다.
    // u v w / u와 v는 정점이고, w는 (u,v)즉 두 정점사이의 가중치이다.
    matrix_t W(100, matrix1(100, INF));
    for (int i = 0; i < m; i++)
    {
        cin >> u[i] >> v[i] >> w[i];
    }

    for (int h = 0; h < m; h++)
    {
        W[u[h]][v[h]] = W[v[h]][u[h]] = w[h];
    }

    prim(n, W, F);
    int p, q;
    for (edge_t e : F)
    {
        p = e.first;
        q = e.second;
        cout << p << " " << q << " " << W[p][q] << endl;
    }
    return 0;
}