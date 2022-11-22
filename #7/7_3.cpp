#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int value[10];

int main()
{
    int N, end, begin;
    int a[50];
    int b[50];

    vector<pair<int, int>> schedule;

    cin >> N; //회의의 수

    for (int i = 0; i < N; i++)
    {
        cin >> begin >> end;
        schedule.push_back(make_pair(end, begin));
    }

    sort(schedule.begin(), schedule.end()); //시간순 정렬함.

    int time = a[0] = schedule[0].first; //제일 처음 회의 시작시간
    b[0] = schedule[0].second;
    int count = 1;
    int x = 1, y = 1;
    for (int i = 1; i < N; i++)
    {
        if (time <= schedule[i].second)
        {
            count++;
            time = a[x++] = schedule[i].first;
            b[y++] = schedule[i].second;
        }
    }

    cout << count << endl; //첫번째 출력
    for (int i = 0; i < count; i++)
    {
        cout << b[i] << " " << a[i] << endl;
    }
}