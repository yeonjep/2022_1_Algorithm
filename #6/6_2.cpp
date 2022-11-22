//최적 이진탐색트리
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define INF 999
typedef struct node *node_ptr;
typedef struct node
{
    node_ptr left;
    node_ptr right;
    int value;

} Node;
int mink;

int r, g;
typedef vector<vector<int>> matrix_t;
matrix_t A(INF, vector<int>(INF));
matrix_t R(INF, vector<int>(INF));

vector<int> keys(INF, 0); //키
vector<int> p(INF, 0);    //빈도값
node_ptr createNode(int n)
{
    node_ptr newnode = (node_ptr)malloc(sizeof(Node));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->value = n;
    return newnode;
}
node_ptr bintree(int i, int j, matrix_t &R, vector<int> &p)
{
    int k = R[i][j];
    if (k == 0)
        return NULL;
    else
    {
        node_ptr Node = createNode(p[k]);
        Node->left = bintree(i, k - 1, R, p);
        Node->right = bintree(k + 1, j, R, p);
        return Node;
    }
}

int minimum(int i, int j, int &mink, vector<int> &p, matrix_t &A) // minValue, mink 사용
{
    int value, minValue = INF;
    for (int k = i; k <= j; k++)
    {
        value = A[i][k - 1] + A[k + 1][j];
        for (int m = i; m <= j; m++)
        {
            value += p[m];
        }
        if (minValue > value)
        {
            minValue = value;
            mink = k;
        }
    }
    return minValue;
}
// Algorithm 3.10

// Algorithm 3.9
void optsearchtree(int n, vector<int> &p, matrix_t &A, matrix_t &R)
{
    for (int i = 1; i <= n; i++) // n까지
    {
        // A, R->(n+1)x(n+1)정방행렬 (1부터 시작해서)
        A[i][i - 1] = 0;
        A[i][i] = p[i]; // 확률p
        R[i][i - 1] = 0;
        R[i][i] = i; // R: 루트노드 저장
    }
    A[n + 1][n] = R[n + 1][n] = 0;

    for (int diagonal = 1; diagonal <= n - 1; diagonal++)
    {
        for (int i = 1; i <= n - diagonal; i++)
        {
            int j = i + diagonal, k;

            A[i][j] = minimum(i, j, k, p, A);
            R[i][j] = k;
        }
    }
}
void preorder(int n, node_ptr cas) //전위순회 출력
{
    static int tmp = 0;
    if (cas)
    {
        tmp++;
        (tmp == n) ? cout << cas->value << endl : cout << cas->value << " ";
        preorder(n, cas->left);
        preorder(n, cas->right);
    }
}
void inorder(int n, node_ptr cas) //중위순회
{
    static int tmp = 0;
    if (cas)
    {
        inorder(n, cas->left);
        tmp++;
        (tmp == n) ? cout << cas->value << endl : cout << cas->value << " ";
        inorder(n, cas->right);
    }
}
void print_M(int n, matrix_t MAT)
{
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = i - 1; j <= n; j++)
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
void makeMatrix(int n, matrix_t A, matrix_t R)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            A[i][j] = 0;
            R[i][j] = 0;
        }
    }
}
int main(void)
{
    // Input 1 : 키의 개수 입력
    int n;
    cin >> n; //키의 개수
    printf("");

    // Input2 : 키의 값 순서대로 입력
    for (int i = 1; i <= n; i++)
    {
        cin >> keys[i];
    } // key의 값
    printf("");
    // Input 3 : 빈도 값 입력
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    } // 빈도값(확률)

    // -----------input 종료-------------

    makeMatrix(n + 1, A, R);   // (n+1)X(n+1)정방행렬 0으로 초기화(인덱스 1부터)
    optsearchtree(n, p, A, R); //최적 이진 탐색트리 실행

    print_M(n, A); // A 출력
    printf("");
    print_M(n, R); // R 출력

    cout << A[1][n] << endl; //평균검색시간의 최적값

    node_ptr N = bintree(1, n, R, keys);
    preorder(n, N); // 전위순회
    inorder(n, N);  // 중위순회

    return 0;
}