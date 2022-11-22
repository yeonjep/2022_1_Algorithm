#include <iostream>
#include <vector>
using namespace std;
// scheduling problem
typedef vector<int> sequence_of_integer;
bool is_feasible(sequence_of_integer &K, sequence_of_integer &deadline)
{
    for (int i = 1; i < K.size(); i++)
    {
        if (i > deadline[K[i]])
        {
            return false;
        }
    }
    return true;
} // 가능한 case 인지 확인
void schedule(int n, sequence_of_integer &deadline, sequence_of_integer &J)
{ // J-job list

    sequence_of_integer K;
    J.clear();
    J.push_back(0);
    J.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        K.resize(J.size());
        copy(J.begin(), J.end(), K.begin()); // K에 Job list 를 담음
        int j = 1;
        while (j < K.size() && deadline[K[i]] <= deadline[i])
        {
            j++;
        } // 몇번째 까지 되는지 세는거

        K.insert(K.begin() + j, i);   // deadline의 오름차순 정렬 순대로 들어가짐
        if (is_feasible(K, deadline)) // true 일때만 실행
        {                             // K가 feasible 하면 k를 J에 담아넣기
            J.resize(K.size());
            copy(K.begin(), K.end(), J.begin());
        }
    }
} // J 에는 feasible job set(숫자-순서) 만 담겨 있는 상태(첫번째는 제외)
int main()
{

    // input1: 첫째 줄에 job의 개수 n이 주어진다.
    int n;
    cin >> n;
    // input2: 둘째 줄에 n개의 deadline이 주어진다.
    sequence_of_integer deadline(n + 1); // 1차원 벡터

    for (int i = 1; i <= n; i++)
    {
        cin >> deadline[i];
    }

    // input 3:셋째 줄에 n개의 profit이 주어진다.(profit은 내림차순으로 정리되어 주어진다.)
    sequence_of_integer profit(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> profit[i];
    }

    //---------------input 종료-----------------//
    sequence_of_integer Job;

    schedule(n, deadline, Job);

    int profitsum = 0;
    for (int i = 1; i < Job.size(); i++)
    {
        profitsum += profit[Job[i]];
    }
    // output1: 최대 이익 출력
    cout << profitsum << endl;
    cout << profit[0] << " ";
    // output2: feasible sequence의 profit을 순서대로 출력
    for (int i = 1; i < Job.size(); i++)
    {
        (i == Job.size() - 1) ? cout << profit[Job[i]] << endl : cout << profit[Job[i]] << " ";
    }

    return 0;
}