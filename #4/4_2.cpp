//큰 정수의 곱셈 분할정복
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> LargeInteger; //벡터 1차원 배열로 큰 수가 주어짐

int threshold, cnt = 0;

void roundup_carry(LargeInteger &v)
{
    int carry = 0;
    for (int i = 0; i < v.size(); i++)
    {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] = v[i] % 10;
    }
    if (carry != 0)
        v.push_back(carry);
}

void lmult(LargeInteger a, LargeInteger b, LargeInteger &c)
{
    c.resize(a.size() + b.size() - 1);
    fill(c.begin(), c.end(), 0);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    }
    roundup_carry(c);
}

void ladd(LargeInteger a, LargeInteger b, LargeInteger &c)
{
    c.resize(max(a.size(), b.size()));
    fill(c.begin(), c.end(), 0);
    for (int i = 0; i < c.size(); i++)
    {
        if (i < a.size())
            c[i] += a[i];
        if (i < b.size())
            c[i] += b[i];
    }
    roundup_carry(c);
}

void pow_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    if (u.size() == 0)
        v.resize(0);
    else
    {
        v.resize(u.size() + m);
        fill(v.begin(), v.end(), 0);
        copy(u.begin(), u.end(), v.begin() + m);
    }
}

void remove_leading_zeros(LargeInteger &v)
{
    while (v.size() != 0 && v.back() == 0)
        v.pop_back();
}

void div_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    if (u.size() == 0)
        v.resize(0);
    else
    {

        int k = m < u.size() ? m : u.size();
        v.resize(k);

        copy(u.begin() + m, u.begin() + u.size(), v.begin());

        remove_leading_zeros(v);
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    if (u.size() == 0)
        v.resize(0);
    else
    {
        int k = m < u.size() ? m : u.size();
        v.resize(k);

        copy(u.begin(), u.begin() + k, v.begin());
        remove_leading_zeros(v);
    }
}

void prod(LargeInteger u, LargeInteger v, LargeInteger &r)
{
    cnt++;
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8; // ppt참고
    int n = max(u.size(), v.size());
    if (u.size() == 0 || v.size() == 0)
        r.resize(0);
    else if (n <= threshold)
        lmult(u, v, r); //한계값 보다 작으면 그냥 곱하기
    else
    {
        int m = n / 2;
        div_by_exp(u, m, x);
        rem_by_exp(u, m, y);
        div_by_exp(v, m, w);
        rem_by_exp(v, m, z);

        prod(x, w, t1);
        pow_by_exp(t1, 2 * m, t2);

        prod(x, z, t3);
        prod(w, y, t4);
        ladd(t3, t4, t5);
        pow_by_exp(t5, m, t6);

        prod(y, z, t7);
        ladd(t2, t6, t8);
        ladd(t8, t7, r);
    }
}

int main(void)
{
    int x;
    // 입력1) 첫 번째 줄에 threshold의 값이 주어진다.
    cin >> threshold;

    // 입력2) 두 번째 줄에 정수 A가 주어진다.
    LargeInteger A, B;
    string strA, strB;
    cin >> strA;
    cin >> strB; //문자열로 큰수 2개를 받음

    //문자열로 받은 수 a,b를 정수 형으로 백터배열에 받아 넣음
    for (int i = 0; i < strA.length(); i++)
    {
        x = strA[i] - '0';
        A.push_back(x);
    }

    for (int i = 0; i < strB.length(); i++)
    {
        x = strB[i] - '0';
        B.push_back(x);
    }

    LargeInteger C;

    prod(A, B, C); // 큰수 곱셈 결괏 값을 C에 저장

    cout << cnt << endl; // 실행 횟수 출력

    for (int i = 0; i < C.size(); i++)
        cout << C[i]; // 결과 값 출력
    cout << endl;
}