#include <iostream>
#include <vector>
#include <queue>
// knapsack algorithm (분할 가능한 배낭문제)
using namespace std;
typedef struct item *item_ptr;
typedef struct item
{
    int id;
    int weight;
    int profit;
    float profit_per_unit; //= profit/weight

} item_t;
int x[100];
int y[100];

vector<item_t> items;
struct compare //단위무게당 이익으로 정렬되도록 비교 함수
{
    bool operator()(item_t *i, item_t *j)
    {
        if (i->profit_per_unit < j->profit_per_unit)
            return true; //내림차순 정렬
        return false;
    }
};
typedef priority_queue<item_ptr, vector<item_ptr>, compare> PriorityQueue;

void initialize(PriorityQueue &PQ, int n, int w[], int p[])
{
    for (int i = 1; i <= n; i++)
    {
        item_ptr item = (item_ptr)malloc(sizeof(item_t));
        item->id = i;
        item->weight = w[i];
        item->profit = p[i];
        item->profit_per_unit = (float)p[i] / (float)w[i];
        PQ.push(item);
    }
}
void knapsack1(int n, int limit, int w[], int p[])
{ // n: 아이템의 개수/ W:배낭의 용량(무게)/ w[]:weight/ p[]:profit
    PriorityQueue PQ;
    initialize(PQ, n, w, p);
    int total_weight = 0;
    int profitsum = 0;
    int h = 1;
    int diff, profit;
    while (!PQ.empty())
    {
        item_ptr i = PQ.top();
        PQ.pop(); // PQ에서 꺼냄
        x[h] = i->weight;
        y[h] = i->profit;
        total_weight += x[h]; //배낭에 담음
        profitsum += y[h];
        h++;

        if (total_weight >= limit)                     //배낭무게를 넘어서지 않았으면 건너뛰기.
        {                                              //넘어섰으면 아래 실행
            diff = i->weight - (total_weight - limit); // 담은 무게
            profit = diff * (i->profit_per_unit);
            profitsum = profitsum - (i->profit) + profit;

            break;
        }
    }

    cout << profitsum << endl;
    for (int k = 1; k < h - 1; k++)
    {
        cout << x[k] << " " << y[k] << endl;
    }
    if (total_weight > limit)
        cout << diff << " " << profit;
    else
        cout << x[h - 1] << " " << y[h - 1];
}

int main(void)
{
    int n;
    cin >> n;

    int w[100];
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
    }

    int p[100];
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }

    int T;
    cin >> T;
    int limit[100];
    for (int i = 1; i <= T; i++)
    {
        cin >> limit[i];
    }

    for (int i = 1; i <= T; i++)
    {
        knapsack1(n, limit[i], w, p);
        if (i != T)
        {
            cout << endl;
        }
    }

    return 0;
}