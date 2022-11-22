#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
// TSP 분기 한정
using namespace std;

#define INF 99999

typedef vector<int> ordered_set;
typedef vector<vector<int>> matrix2;

typedef struct node
{
    int level;
    ordered_set path;
    int bound;
} nodetype;

typedef struct node node_t;

struct compare
{
    bool operator()(node_t u, node_t v)
    {
        if (u.bound > v.bound)
            return true;
        return false;
    }
};

typedef priority_queue<node_t, vector<node_t>, compare>
    priority_queue_of_node;

int n, m;
matrix2 W;

bool isIn(int i, ordered_set path)
{
    for (int j = 0; j < path.size(); j++)
        if (path[j] == i)
            return true;
    return false;
}

int length(ordered_set path)
{
    vector<int>::iterator it;
    int len = 0;
    for (it = path.begin(); it != path.end(); it++)
        if (it != path.end() - 1)
            len += W[*it][*(it + 1)];
    return len;
}

bool hasOutgoing(int v, ordered_set path)
{
    vector<int>::iterator it;
    for (it = path.begin(); it != path.end() - 1; it++)
        if (*it == v)
            return true;
    return false;
}

bool hasIncoming(int v, ordered_set path)
{
    vector<int>::iterator it;
    for (it = path.begin() + 1; it != path.end(); it++)
        if (*it == v)
            return true;
    return false;
}

int bound(node_t v)
{
    int lower = length(v.path);
    for (int i = 1; i <= n; i++)
    {
        if (hasOutgoing(i, v.path))
            continue;
        int min = INF;
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            if (j == 1 && i == v.path[v.path.size() - 1])
                continue;
            if (hasIncoming(j, v.path))
                continue;
            if (min > W[i][j])
                min = W[i][j];
        }
        lower += min;
    }
    return lower;
}

node_t create_node(int level, ordered_set path)
{
    node_t v;

    v.level = level;

    for (int i = 0; i < path.size(); i++)
    {
        v.path.push_back(path[i]);
    }
    v.bound = bound(v);

    return v;
}

void copy(ordered_set path, ordered_set &opttour)
{
    opttour.clear();
    opttour.resize(path.size());
    for (int i = 0; i < path.size(); i++)
    {
        opttour[i] = path[i];
    }
}

void travel2(ordered_set &opttour, int &minlength)
{

    priority_queue_of_node PQ;
    node_t u, v;

    minlength = INF;

    ordered_set tmp(1, 1);
    v = create_node(0, tmp);

    cout << v.level << " ";
    if (bound(v) >= INF)
        cout << "INF ";
    else
        cout << bound(v) << " ";

    for (int k = 0; k < v.path.size(); k++)
    {
        cout << v.path[k];
        if (k != v.path.size() - 1)
            cout << " ";
    }
    cout << endl;

    PQ.push(v);

    while (!PQ.empty())
    {
        v = PQ.top();
        PQ.pop();
        if (v.bound < minlength)
        {
            for (int i = 2; i <= n; i++)
            {
                if (isIn(i, v.path))
                    continue;
                u = create_node(v.level + 1, v.path);
                u.path.push_back(i);

                if (u.level == n - 2)
                {
                    for (int j = 2; j <= n; j++)
                    {
                        if (!isIn(j, u.path))
                            u.path.push_back(j);
                    }
                    u.path.push_back(1);
                    if (length(u.path) < minlength)
                    {
                        minlength = length(u.path);
                        copy(u.path, opttour);
                    }
                    cout << u.level << " ";
                    if (bound(u) >= INF)
                        cout << "INF ";
                    else
                        cout << bound(u) << " ";

                    for (int k = 0; k < u.path.size(); k++)
                    {
                        cout << u.path[k];
                        if (k != u.path.size() - 1)
                            cout << " ";
                    }
                    cout << endl;
                }

                else
                {
                    u.bound = bound(u);

                    cout << u.level << " ";
                    if (bound(u) >= INF)
                        cout << "INF ";
                    else
                        cout << bound(u) << " ";

                    for (int k = 0; k < u.path.size(); k++)
                    {
                        cout << u.path[k];
                        if (k != u.path.size() - 1)
                            cout << " ";
                    }
                    cout << endl;

                    if (u.bound < minlength)
                        PQ.push(u);
                }
            }
        }
    }
}

int main()
{
    // 입력 1 - 첫 줄에 그래프의 정점 개수 n과 그래프의 간선 개수 m이 주어진다.
    cin >> n >> m;
    // 입력 2 - 둘째 줄부터 m개의 간선이 u, v, w의 형태로 주어진다.
    W.resize(n + 1, ordered_set(n + 1, INF));

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        W[u][v] = w;
    }

    // 출력 1 - 첫째 줄부터 분기한정법으로 방문하는 노드의 상태
    ordered_set optTour;
    int minlength;
    travel2(optTour, minlength);

    // 출력 2 - 다음 줄에 최적값 minlength를 출력한다.
    cout << minlength << endl;

    // 출력 3 - 다음 줄에는 1번 정점을 출발점으로 하는 최적 순회 경로를 출력한다.
    for (int i = 0; i < optTour.size(); i++)
    {
        cout << optTour[i];
        if (i != optTour.size() - 1)
            cout << " ";
    }
}