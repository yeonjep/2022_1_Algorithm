#include <iostream>
#include <vector>
#include <queue>
// 0-1 냅색 백트래킹
using namespace std;

typedef vector<int> matrix1;
typedef vector<vector<int>> matrix2;
typedef vector<bool> matrixbool;

int n, W, maxprofit;
matrix1 w, p, sorted_w, sorted_p;
matrixbool include, bestset;

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

int save;
bool promising(int i, int profit, int weight)
{
    int j, k, totweight, bound;

    if (weight >= W)
    {
        cout << i << " " << weight << " " << profit << " " << save << " " << maxprofit << endl;
        return false;
    }
    else
    {
        j = i + 1;
        bound = profit;
        totweight = weight;

        while (j <= n && totweight + sorted_w[j] <= W)
        {
            totweight += sorted_w[j];
            bound += sorted_p[j];
            j++;
        }
        k = j;
        if (k <= n)
            bound += (W - totweight) * ((float)sorted_p[k] / sorted_w[k]);
        save = bound;
        cout << i << " " << weight << " " << profit << " " << bound << " " << maxprofit << endl;
        return bound > maxprofit;
    }
}

void array_copy(matrixbool include, matrixbool &bestset)
{
    for (int i = 1; i <= n; i++)
    {
        bestset[i] = include[i];
    }
}

void knapsack4(int i, int profit, int weight)

{

    if (weight <= W && profit > maxprofit)
    {
        maxprofit = profit;
        array_copy(include, bestset);
    }
    if (promising(i, profit, weight))
    {
        include[i + 1] = true;
        knapsack4(i + 1, profit + sorted_p[i + 1], weight + sorted_w[i + 1]);
        include[i + 1] = false;
        knapsack4(i + 1, profit, weight);
    }
}

int main()
{
    // 입력 1 - 첫번째 줄에 아이템의 개수 n과 배낭의 무게 W가 주어진다.
    cin >> n >> W;
    // 입력 2 - 두번째 줄에 n개의 아이템 무게 w[i]가 주어진다.
    w.resize(n + 1);
    sorted_w.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    // 입력 3 - 세번째 줄에 n개의 아이템 이익 p[i]가 주어진다.
    p.resize(n + 1);
    sorted_p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    include.resize(n + 1);
    bestset.resize(n + 1);

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

    // 출력 1 - 첫 번째 줄부터 한 줄에 하나씩 상태공간트리를 방문하는 노드의 상태를 출력하시오.
    // i weight profit bound maxprofit 순서로 노드를 출력한다
    maxprofit = 0;
    knapsack4(0, 0, 0);

    // 출력 2 - 노드의 상태 출력이 끝나는 다음 줄에 최대이익을 출력한다.
    cout << maxprofit << endl;
    // 출력 3 - 이후로 배낭에 담은 아이템을 한 줄에 하나씩 무게와 이익 순서로 출력한다.
    // 아이템을 출력하는 순서는 처음에 단위무게당 이익으로 정렬한 순서대로 출력함에 주의할 것.
    for (int i = 1; i <= n; i++)
        if (bestset[i])
            cout << sorted_w[i] << " " << sorted_p[i] << endl;
}