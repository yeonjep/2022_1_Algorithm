//최장공통부분서열(LSC)
/*
예를 들어, 두 개의 문자열 X = "ABCBDAB", Y = "BDCABA"에 대해서

공통부분서열의 최대값은 4이고, 해당하는 부분서열은 BCBA이다.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define N 100

using namespace std;
typedef vector<vector<int>> matrix;
string s1, s2;

string get_lcs(int i, int j, matrix b, string x)
{
    int k = b[i][j];

    if (i == 0 || j == 0)
        return "";

    else
    {
        if (k == 1)                                    //대각선
            return get_lcs(i - 1, j - 1, b, x) + x[i]; // 1일때 대각선 이동했다는 뜻이므로 x[i]출력됨
        else if (k == 2)                               //왼쪽
            return get_lcs(i, j - 1, b, x);
        else if (k == 3) //위로
            return get_lcs(i - 1, j, b, x);
    }
}
int main(void)
{

    cin >> s1;
    cin >> s2;

    matrix b(100, vector<int>(100));
    matrix c(100, vector<int>(100)); //-> 최장공통부분서열의 길이

    s1 = " " + s1;
    s2 = " " + s2; //문자열 2개 받아서 배열에 넣고 정렬

    for (int i = 0; i < s1.size(); i++)
    {
        for (int j = 0; j < s2.size(); j++)
        {
            b[i][j] = 0;
            c[i][j] = 0;
        }
    }

    for (int i = 1; i < s1.size(); i++)
    {
        for (int j = 1; j < s2.size(); j++)
        {
            if (s1[i] == s2[j])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else
            {
                c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                b[i][j] = c[i][j - 1] > c[i - 1][j] ? 2 : 3;
            }
        }
    }

    cout << c[s1.size() - 1][s2.size() - 1] << endl;
    cout << get_lcs(s1.size() - 1, s2.size() - 1, b, s1) << endl;

    return 0;
}