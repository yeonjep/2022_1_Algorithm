// sum of subset(부분집합의 합)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<bool> arr_bool;
typedef vector<vector<int>> matrix;
typedef vector<int> arr;

int n, W;
int k = 0;
int cnt = 0;
arr_bool include;
arr w;         // 1차원
matrix subset; // 2차원

bool promising(int i, int weight, int total)
{
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}
void sum_of_subset(int i, int weight, int total)
{ // weight: i레벨 까지 왔을때 담긴 합
    if (promising(i, weight, total))
    {
        if (weight == W) // solution
        {
            arr guri;
            for (int a = 0; a <= i; a++)
            {
                if (include[a] == true)
                    guri.push_back(w[a]);
            }
            subset.push_back(guri);

            cnt++;
        }
        else //(weight + total >= W) && (weight + w[i + 1] <= W)
        {
            include[i + 1] = true; //포함O
            sum_of_subset(i + 1, weight + w[i + 1], total - w[i + 1]);
            include[i + 1] = false; //포함X
            sum_of_subset(i + 1, weight, total - w[i + 1]);
        }
    }
}
int main(void)
{
    int input;
    int total = 0;

    cin >> n >> W;

    for (int i = 0; i < n; i++)
    {
        cin >> input;
        w.push_back(input);
    }

    for (int i = 0; i < w.size(); i++)
        total += w[i];

    include.resize(n);

    sum_of_subset(-1, 0, total);
    cout << cnt;

    if (cnt != 0)
        cout << endl;
    //--------cnt 까지 출력---------

    for (int i = 0; i < cnt; i++)
    {
        for (int j = 0; j < subset[i].size(); j++)
        {
            cout << subset[i][j];
            if (i != cnt - 1 && j == subset[i].size() - 1)
                cout << endl;
            else
                cout << " ";
        }
    }

    return 0;
}