#include <iostream>
#include <vector>
using namespace std;
//동적 계획과 이항계수
//-> 변형 이항계수 문제의 최적화
#define MIN(x, y) ((x) > (y) ? (y) : (x))
int MAX;
int bin1(int n, int k)
{
    vector<int> B(n + 1, 0);
    // 일차원 벡터 배열 B정의& 0으로 초기화
    if (k > n / 2)
        k = n - k; // 이항계수의 성질

    B[0] = 1;

    for (int i = 0; i <= n; i++)
    {
        int j = MIN(i, k);
        while (j > 0)
        {
            B[j] = (B[j] + B[j - 1]) % MAX;
            j--; // j가 0이면 멈춤
        }
    }
    return B[k];
}
int main(void)
{
    int n, k;

    //입력 - 이항계수의 n과 k, 그리고 MAX 값이 주어진다.
    // 0<=k<=n<=200000
    // 10 <= MAX <= 10000000
    cin >> n;
    cin >> k;
    cin >> MAX;

    //출력 - 변형 이항계수의 값 B[n][k]를 출력한다.
    cout << bin1(n, k); // 이항계수 전체 값을 더한 결과 출력

    return 0;
}