//==============홀수 피라미드==================> 문제 찾아보기(영어로 됨)
//[문제]SWEA 문제
//[입력]
//[출력]
//[입력 예제]

#include <iostream>

typedef unsigned long long ull;

using namespace std;

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int test_case;
    int T;
    ull N;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        ull a, b;
        a = (N - 1) * (N - 1) * 2 + 1;
        b = N * N * 2 - 1;
        cout << "#" << test_case << " " << a << " " << b << endl;
    }
    return 0; //정상종료시 반드시 0을 리턴해야합니다.
}
