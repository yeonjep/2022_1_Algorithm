#include <iostream>
#include <vector>
#include <map>
#include <queue>
// 0-1 냅색 동적계획법(DP)
using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;

int n;
matrix1 p, w, W, sorted_p, sorted_w;

typedef struct item *item_ptr;
typedef struct item
{
    int id;
    int weight;
    int profit;
    int profit_per_unit;
} item_t;

struct compare
{
    bool operator()(item_t *i, item_t *j)
    {
        if (i->profit_per_unit < j->profit_per_unit)
            return true;
        return false;
    }
};

typedef priority_queue<item_ptr, vector<item_ptr>, compare> PriorityQueue;

item_ptr create_node(int i, int w, int p)
{
    item_ptr item = (item_ptr)malloc(sizeof(item_t));
    item->id = i;
    item->weight = w;
    item->profit = p;
    item->profit_per_unit = p / w;
    return item;
}

void sorting(PriorityQueue &PQ, int n, matrix1 &w, matrix1 &p)
{
    for (int i = 1; i <= n; i++)
    {
        item_ptr item = create_node(i, w[i], p[i]);
        PQ.push(item);
    }
}

int knapsack3(int n, int W, matrix1 w, matrix1 p, map<pair<int, int>, int> &P)
{
    if (n == 0 || W <= 0)
    {
        P[make_pair(n, W)] = 0;
        return 0;
    }
    int lvalue = (P.find(make_pair(n - 1, W)) != P.end()) ? P[make_pair(n - 1, W)] : knapsack3(n - 1, W, w, p, P);
    int rvalue = (P.find(make_pair(n - 1, W - w[n])) != P.end()) ? P[make_pair(n - 1, W)] : knapsack3(n - 1, W - w[n], w, p, P);
    P[make_pair(n, W)] = (w[n] > W) ? lvalue : max(lvalue, p[n] + rvalue);
    return P[make_pair(n, W)];
}

int main()
{
    // 입력 1 -  첫 번째 줄에 아이템의 개수 n이 주어진다.
    cin >> n;

    // 입력 2 -  두 번째 줄에 n개의 무게 w[i]가 주어진다.
    w.resize(n + 1);
    sorted_w.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    // 입력 3 -  세 번째 줄에 n개의 이익 p[i]가 주어진다.
    p.resize(n + 1);
    sorted_p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    PriorityQueue PQ;
    sorting(PQ, n, w, p);
    int i = 1;
    while (!PQ.empty())
    {
        item_ptr ptr = PQ.top();
        sorted_w[i] = ptr->weight;
        sorted_p[i++] = ptr->profit;
        PQ.pop();
    }

    // 입력 4 -  네 번째 줄에 배낭 무게의 개수 T가 주어진다.
    int T;
    cin >> T;

    // 입력 5 -  이후로 T개의 줄에 한 줄에 하나씩 배낭 무게 W가 주어진다.
    W.resize(T + 1, 0);
    for (int i = 1; i <= T; i++)
        cin >> W[i];

    for (int i = 1; i <= T; i++)
    {
        map<pair<int, int>, int> P;
        P[make_pair(0, 0)] = 0;
        // 출력 1 -  첫 줄에 최대 이익 maxprofit을 출력한다.
        int res = knapsack3(n, W[i], sorted_w, sorted_p, P);
        cout << res << endl;
        // 출력 2 -  이후로 알고리즘의 실행과정에서 결과 테이블 P에 저장한
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= W[i]; k++)
            {
                if (P.count(make_pair(j, k)) != 0)
                    cout << j << " " << k << " " << P[make_pair(j, k)] << endl;
            }
        }
    }
}