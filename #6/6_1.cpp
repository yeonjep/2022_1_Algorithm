//연쇄행렬 곱셈문제   (행렬 여러개 곱하기)
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define INF 999999
typedef vector<vector<int>> matrix_t;
string s;

int minValue;
int diagonal;
int n;
int mink;
vector<int> d(n + 1);
matrix_t M(n + 1, vector<int>(n + 1, 0));
matrix_t P(n + 1, vector<int>(n + 1, 0));

// algorithm 3.6_2
int minimum(int i, int j, int &mink, vector<int> &d, matrix_t &M)
{
    int minValue = INF;
    int value;
    for (int k = i; k <= j - 1; k++)
    {
        value = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
        if (minValue > value)
        {
            minValue = value;
            mink = k;
        }
    }
    return minValue;
}

// algorithm 3.6_1
void minmult(int n, vector<int> &d, matrix_t &M, matrix_t &P)
{

    for (int i = 1; i <= n; i++)
    {
        M[i][i] = 0; // 0 으로 초기화
    }
    for (diagonal = 1; diagonal <= n - 1; diagonal++)
    {
        for (int i = 1; i <= n - diagonal; i++)
        {
            int j = i + diagonal;
            int k;
            M[i][j] = minimum(i, j, k, d, M);
            P[i][j] = k;
        }
    }
}
void print_M(int n, matrix_t &MAT)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            cout << MAT[i][j];
            if (j != n)
            {
                printf(" ");
            }
        }
        cout << endl;
    }
}
void order(int i, int j, matrix_t &P, string &s)
{

    if (i == j)
    {
        s += string("(A") + to_string(i) + string(")");
    }
    else
    {
        int k = P[i][j];
        s += string("(");
        order(i, k, P, s);
        order(k + 1, j, P, s);
        s += string(")");
    }
}

int main()
{
    int n; // 곱할 행렬의 개수
    cin >> n;
    printf("");

    for (int i = 0; i < n + 1; i++)
    {
        cin >> d[i]; // 행렬의 크기 값 배열
    }
    //---------------Input종료----------------------
    minmult(n, d, M, P);

    print_M(n, M);
    print_M(n, P);

    cout << M[1][n] << endl; // 최적값 출력

    order(1, n, P, s);
    cout << s << endl;

    return 0;
}
//벡터 사용