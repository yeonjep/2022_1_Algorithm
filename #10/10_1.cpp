// n-Queens
#include <iostream>
//n-queens
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef vector<unsigned long long> ary_ull;
// col[i]: i번째 행(row)에서 퀸이 놓여 있는 열(col)의 위치
int col[100];
int cnt = 0; //배치 가능한 보드의 개수 카운트
int h = 0;
string str1[50000];
string str2[50000]; //-> 벡터로   push_back으로 넣어줘도됨
bool promising(int i)
{
    int k = 1;
    bool flag = true;
    while (k < i && flag)
    {
        if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k)) //열이 같거나 대각선 조건
            flag = false;
        k++;
    }
    return flag;
}
void queens(int i, int n)
{
    int j;
    if (promising(i)) // true 일때 실행
    {
        if (i == n)
        {
            cnt++;
            for (int q = 1; q <= n; q++)
            {
                str1[q] = to_string(col[q]);
            }
            for (int q = 1; q <= n; q++)
            {
                str2[h] += str1[q];
            }
            h++;
        }
        else
        {
            for (j = 1; j <= n; j++)
            {
                col[i + 1] = j; //열
                queens(i + 1, n);
            }
        }
    }
}
bool compare(unsigned long long i, unsigned long long j)
{
    return j < i;
}
int main(void)
{
    // n의 값이 주어질때 (nxn matrix) 퀸이 적절히 배치될수 있는 보드가 몇개인지 카운트
    //  col 배열의 값을 숫자의 문자열로 취급했을 때 가장 큰 값을 출력

    int n;
    cin >> n; // n > 4
    queens(0, n);
    cout << cnt << endl; // 가능한 보드의 배치 개수
    ary_ull str_int;

    for (int k = 0; k < h; k++)
    {
        str_int.push_back(stoull(str2[k]));
    } // string -> int 변환

    sort(str_int.begin(), str_int.end(), compare);
    cout << str_int[0];

    return 0;
}