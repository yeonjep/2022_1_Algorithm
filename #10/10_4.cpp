//해밀턴
//모든 정점을 방문

#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> matrix;
typedef vector<int> matrix1;
matrix W(100, matrix1(100, 0));
matrix1 vindex(100, 0);
int cnt = 0;
bool promising(int i, int n)
{
    int j;
    bool flag;
    if (i == n - 1 && !W[vindex[n - 1]][vindex[0]])
        flag = false;
    else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
        flag = false;
    else
    {
        flag = true;
        j = 1;
        while (j < i && flag)
        {
            if (vindex[i] == vindex[j])
                flag = false;
            j++;
        }
    }
    return flag;
}
void hamiltonian(int i, int n)
{
    int j;
    if (promising(i, n))
    {
        if (i == n - 1)
        {
            cnt++;
        }
        else
        {
            for (j = 2; j <= n; j++)
            {
                vindex[i + 1] = j;
                hamiltonian(i + 1, n);
            }
        }
    }
}
int main(void)
{
    int n, m;
    cin >> n >> m; // 정점, 간선
    int i = 1;
    vindex[0] = 1;
    //인접 행렬
    int x, y;
    while (i <= m)
    {
        cin >> x >> y;
        W[y][x] = W[x][y] = 1; //무방향 그래프
        i++;
    }
    hamiltonian(0, n);
    cout << cnt;
    return 0;
}