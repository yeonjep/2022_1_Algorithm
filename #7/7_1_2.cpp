// Kruskal Algorithm
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// typedef vector<vector<int>> matrix;
typedef struct edge
{
    int u, v, w;
} edge_t;

vector<int> dset; // disjoint 된 set 형성(n만큼)
struct edge_compare
{
    bool operator()(edge_t e1, edge_t e2)
    {
        if (e1.w > e2.w)
            return true;
        else
            return false;
    }
};
typedef vector<edge_t> set_of_edges;
typedef priority_queue<edge_t, vector<edge_t>, edge_compare> PriorityQueue;
set_of_edges E, F;
void dset_init(int n)
{
    dset.resize(n + 1);
    for (int i = 1; i <= n; i++)
        dset[i] = i;
}
int dset_find(int i)
{
    while (dset[i] != i)
        i = dset[i];
    return i;
}
void dset_merge(int p, int q)
{
    dset[p] = q;
}
void kruskal(int n, int m, set_of_edges &E, set_of_edges &F)
{
    int p, q;
    edge_t e;
    PriorityQueue PQ;
    // sort the m edge in E by weight in nondecreasing order;-> sorting해줘야 함
    for (edge_t e : E)
        PQ.push(e);

    F.clear();
    dset_init(n);
    // for (int k = 1; k < n; k++)
    int k = 1;
    while (k < n) //-> while(으로)
    {
        e = PQ.top();
        PQ.pop();
        p = dset_find(e.u);
        q = dset_find(e.v);

        if (p != q) //같으면 사이클이 형성됨
        {
            dset_merge(p, q);
            F.push_back(e); // add e to F-> F엔 minimum tree에서 사용할 edge들만 남아 있음
        }
        k++;
    }
    for (int k = 1; k <= n - 1; k++)
    {
        e = PQ.top();
        PQ.pop();
        p = dset_find(e.u);
        q = dset_find(e.v);

        if (p != q)
        {
            dset_merge(p, q);
            F.push_back(e);
        }
    }
}
int main()
{

    int n, m; // 정점의 개수: n, 간선의 개수:m
    cin >> n >> m;

    int x[100];
    int y[100];
    int z[100];

    edge_t value;
    for (int i = 0; i < m; i++)
    {
        cin >> x[i] >> y[i] >> z[i];
    }
    for (int i = 0; i < m; i++)
    {
        value.u = x[i];
        value.v = y[i];
        value.w = z[i];
        E.push_back(value);
    }

    kruskal(n, m, E, F);

    for (edge_t e : F)
    {
        cout << e.u << " " << e.v << " " << e.w << endl;
    }

    return 0;
}