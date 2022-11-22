// m-coloring
#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> matrix;
typedef vector<int> matrix1;
matrix W(100, matrix1(100, 0));
int n, k;
int vcolor[50];
int cnt = 0;
bool promising(int i)
{
    int j = 1;
    bool flag = true;

    while (j < i && flag)
    {
        if (W[i][j] && vcolor[i] == vcolor[j]) //인접한 정점이 색이 같으면 false
            flag = false;
        j++;
    }
    return flag;
}
// int firstmincolor = 0;
void m_coloring(int i, int m)
{
    int color;
    if (promising(i))
    {
        if (i == n) // 모든 노드를 다 칠했으면 -> 1부터 n까지 다 출력
        {
            cnt++;
        }
        // cout<< vcolor[1]~i 번째까지 출력
        else
        {
            for (color = 1; color <= m; color++)
            {
                vcolor[i + 1] = color; // 그 컬러가 아니면 다른 컬러
                m_coloring(i + 1, m);
            }
        }
    }
}
int main(void)
{
    cin >> n >> k; // 정점, 간선의 수
    int i = 1;
    int x, y;
    int arr1[10];
    int arr2[10];
    int num = 0;
    while (i <= k)
    {
        cin >> x >> y;
        W[y][x] = W[x][y] = 1; //무방향 그래프
        i++;
    }

    for (int i = 1; i <= 4; i++)
    {
        cnt = 0;
        m_coloring(0, i);
        if (cnt >= 1)
        {
            arr1[num] = i;
            arr2[num] = cnt;
            num++;
        }
    }
    cout << arr1[0] << endl;
    cout << arr2[0];

    return 0;
}