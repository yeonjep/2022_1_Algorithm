#include <iostream>
using namespace std;

typedef unsigned long long int uint;

unsigned long long int fib(unsigned long long int n, unsigned long long int max)
{
    if (n <= 1)
    {
        return n;
    }

    int a = 0, b = 1, c;

    for (int i = 2; i <= n; i++)
    {
        c = (a + b) % max;
        a = b;
        b = c;
    }
    return b;
}

int main()
{
    unsigned long long int n, max;
    cin >> n;
    cin >> max;
    cout << fib(n, max) << endl;
}