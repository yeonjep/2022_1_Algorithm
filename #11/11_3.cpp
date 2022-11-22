#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
//기사의 여행
using namespace std;
typedef vector<vector<int>> matrix;
typedef vector<int> ary;
ary node_s, mark;
matrix graph;
int n, m, T, x, s, next_i, next_j, cnt1, cnt2;
//인접리스트를 그래프를 구성할 수 있음
void makeGraph()
{
    int imove[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int jmove[8] = {1, 2, 2, 1, -1, -2, -2, -1}; //시계 방향 -> 8가지 move

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                next_i = i + imove[k];
                next_j = j + jmove[k];
                if (next_i >= 0 && next_i < n && next_j < m && next_j >= 0)
                    graph[i * m + j].push_back(next_i * m + next_j); //-> pair로 value 값으로 정해야 할지 고민
            }
        }
    }
}
void tour1(int k, int v) // closed(회로)-> 출발정점이 0이든 뭐든 상관없음
{
    if (k == n * m) //전체 다 돌았을때(다 찾은거)
    {
        ary arr = graph[v];
        if (find(arr.begin(), arr.end(), s) != arr.end()) //회로인지 체크
        {
            cnt1++; //해밀턴 회로의 수
        }
    }
    else
    {
        for (int u : graph[v])
            if (mark[u] == 0) //방문하지 않은 정점일때
            {
                mark[u] = k + 1; // k+1번째에 u노드를 방문하겠다.
                tour1(k + 1, u); //재귀호출
                mark[u] = 0;
            }
    }
}
void tour2(int k, int v) // open(경로)
{
    if (k == n * m) //전체 다 돌았을때
    {
        //  mark[v] = kth;
        cnt2++; //해밀턴 경로의 수
    }
    else
    {
        for (int u : graph[v])
            if (mark[u] == 0)
            {
                mark[u] = k + 1;
                tour2(k + 1, u);
                mark[u] = 0;
            }
    }
}

int main(void)
{
    cin >> n >> m; //행(n), 열(m)
    cin >> T;      //출발정점의 개수

    int row_s[50];
    int col_s[50];
    for (int i = 0; i < T; i++)
    {
        cin >> row_s[i] >> col_s[i];
    } // 출발 정점의 쌍
    //------입력 완료-------
    graph.resize(n * m, vector<int>(0));
    mark.resize(n * m, 0);
    mark[s] = 1;
    makeGraph();
    tour1(1, s); // s=0 (해밀턴 회로는 출발 정점이 중요하지 않음)
    // 1> 해밀턴 '회로'의 개수 출력
    cout << cnt1 << endl;
    // 2> 주어진 출발 정점에서 각각에 대해  해밀턴 '경로'의 수 출력

    for (int i = 0; i < T; i++)
    {
        cnt2 = 0;
        mark.resize(n * m, 0);
        fill(mark.begin(), mark.end(), 0);
        s = row_s[i] * m + col_s[i];
        mark[s] = 1; // mark starting vertex
        tour2(1, s);
        if (cnt2 >= 0)
            cout << cnt2;
        if (i != T - 1)
            cout << endl;
    }

    return 0;
}
