// 0-1 배낭문제와 분기한정법
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int maxprofit, weight, n, packWeight;

typedef vector<vector<int>> matrix;
typedef vector<int> ary;

ary w, p;

typedef struct node *node_pointer;
typedef struct node
{
    int level;
    int weight;
    int profit;
    int bound;

} nodetype;
struct compare
{
    bool operator()(node_pointer u, node_pointer v)
    {
        if (u->bound < v->bound)
            return true;
        return false;
    }
};
typedef priority_queue<node_pointer, vector<node_pointer>, compare> priority_queue_of_node;
int bound(node_pointer u)
{
    int j, k, totweight;
    int result;
    if (u->weight >= packWeight)
        return 0;

    else
    {
        result = u->profit;
        j = u->level + 1;
        totweight = u->weight;
        while (j <= n && totweight + w[j] <= packWeight)
        {
            totweight += w[j];
            result += p[j];
            j++;
        }
        k = j;
        if (k <= n)
            result += (packWeight - totweight) * p[k] / w[k];
        return result;
    }
}
node_pointer create_node(int level, int weight, int profit)
{
    node_pointer v = (node_pointer)malloc(sizeof(nodetype));
    v->level = level;
    v->weight = weight;
    v->profit = profit;
    v->bound = bound(v);
    cout << v->level << " " << v->weight << " " << v->profit << " " << v->bound << endl;
    return v;
}
void knapsack6()
{
    priority_queue_of_node PQ;
    node_pointer u, v;
    maxprofit = 0;
    PQ.push(create_node(0, 0, 0));
    while (!PQ.empty())
    {
        v = PQ.top();
        PQ.pop();
        // cout << v->level << " " << v->weight << " " << v->profit << " " << v->bound << endl;
        if (v->bound > maxprofit)
        {
            u = create_node(v->level + 1,
                            v->weight + w[v->level + 1],
                            v->profit + p[v->level + 1]);
            if (u->weight <= packWeight && u->profit > maxprofit)
                maxprofit = u->profit;
            //   cout << u->level << " " << u->weight << " " << u->profit << " " << u->bound << endl;
            if (u->bound > maxprofit)
                PQ.push(u);
            u = create_node(v->level + 1, v->weight, v->profit);
            // cout << u->level << " " << u->weight << " " << u->profit << " " << u->bound << endl;
            if (u->bound > maxprofit)
                PQ.push(u);
        }
    }
}
int main(void)
{
    cin >> n >> packWeight;
    int weight, profit;
    // n > w
    w.push_back(0);
    p.push_back(0);
    for (int i = 0; i < n; i++)
    {
        cin >> weight;
        w.push_back(weight);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> profit;
        p.push_back(profit);
    }
    ary temp;
    temp.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        temp.push_back(p[i] / w[i]);
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = i + 1; j < n + 1; j++)
        {
            if (temp[i] < temp[j])
            {
                int tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;

                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;

                tmp = w[i];
                w[i] = w[j];
                w[j] = tmp;
            }
        }
    }

    //================input 완료=====================//
    knapsack6();
    cout << maxprofit;

    return 0;
}