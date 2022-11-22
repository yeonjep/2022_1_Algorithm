#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;
// Haffman
typedef vector<int> matrixint;
typedef vector<char> matrixchar;
typedef map<char, vector<int>> mapping;

typedef struct node *node_ptr;
typedef struct node
{
    char symbol;
    int frequency;
    node_ptr left;
    node_ptr right;

} node_t;
struct compare
{
    bool operator()(node_ptr p, node_ptr q)
    { // 빈도수 기준으로 정렬
        return p->frequency > q->frequency;
    }
};

typedef priority_queue<node_ptr, vector<node_ptr>, compare> PriorityQueue;

int number_for_traversal = 0; //순회 띄어쓰기용 인덱스
node_ptr create_node(char _symbol, int _frequency)
{
    node_ptr newNode = (node_ptr)malloc(sizeof(node_t));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->symbol = _symbol;
    newNode->frequency = _frequency;
    number_for_traversal++;

    return newNode;
}

void sorting(PriorityQueue &PQ, int n, matrixchar characters, matrixint freq)
{
    for (int i = 0; i < n; i++)
    {
        node_ptr newNode = create_node(characters[i], freq[i]);
        PQ.push(newNode);
    }
}

node_ptr huffman(int n, matrixchar characters, matrixint freq)
{ //노드들로 tree 만들어서 "루트"를 리턴해주는 함수
    // n : 데이터 파일내 문자의 개수
    //  PQ: 빈도수가 낮은 노드를 먼저 리턴하는 (오름차순) 우선순위큐 (min heap)
    // 1. PQ 생성
    PriorityQueue PQ;
    sorting(PQ, n, characters, freq);
    // 2. 트리 생성
    for (int i = 0; i < n - 1; i++)
    {
        //제일 빈도 낮은 2개 노드(p,q) 꺼내서 r 만들고 / r의 frequency = p,q frequency 더한 값
        // r의 왼쪽 자식, 오른쪽 자식에 p,q 연결 후 (r,p,q로 subtree가 생성된 상태) PQ에 r 삽입
        node_ptr p = PQ.top();
        PQ.pop();
        node_ptr q = PQ.top();
        PQ.pop();
        node_ptr r = create_node('+', p->frequency + q->frequency);
        r->left = p;
        r->right = q;
        PQ.push(r);
    }
    // PQ의 가장 위에 남아있는 노드가 모든 노드들의 root
    return PQ.top();
}

void preorder(node_ptr ptr) //중위 순회
{
    static int cnt = 0;
    if (ptr)
    {
        cnt++;
        if (cnt == number_for_traversal)
            cout << ptr->symbol << ":" << ptr->frequency << endl;
        else
            cout << ptr->symbol << ":" << ptr->frequency << " ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void inorder(node_ptr ptr) //전위 순회
{
    static int cnt = 0;
    if (ptr)
    {
        inorder(ptr->left);
        cnt++;
        if (cnt == number_for_traversal)
            cout << ptr->symbol << ":" << ptr->frequency << endl;
        else
            cout << ptr->symbol << ":" << ptr->frequency << " ";
        inorder(ptr->right);
    }
}

void encode(node_ptr root, matrixint &code, mapping &encoder)
{ // encorder에 symbol이랑 그 symbol을 암호화한 코드 저장( 문자 -> 숫자 )

    // 실제로 문자가 저장된 노드인 경우(leaf node)
    if (root->symbol != '+')
    {
        matrixint ret;
        ret.resize(code.size());
        copy(code.begin(), code.end(), ret.begin());
        encoder.insert(make_pair(root->symbol, ret));
    }

    // 문자가 아니라 문자끼리 더한 게 저장된 노드인 경우
    // 왼쪽 노드에는 0, 오른쪽 노드에는 1 저장//구리
    else if (root != NULL)
    {
        code.push_back(0);
        encode(root->left, code, encoder);
        code.pop_back();
        code.push_back(1);
        encode(root->right, code, encoder);
        code.pop_back();
    }
}

void decode(node_ptr root, string S) //(숫자 -> 문자)
{
    // 문자열 S의 제일 첫 인덱스 (0)부터 탐색
    // 트리 따라 내려가다가 leaf node(문자가 저장된 노드) 만나면 문자 출력 후 다시 루트부터 탐색(1)
    // leaf node 아니고 symbol에 +가 저장된 노드라면
    // S에 0이 저장되었다면 그 노드의 왼쪽을,(2)
    // S에 1이 저장되었다면 그 노드의 오른쪽을 탐색(3)

    int i = 0;
    node_ptr curNode = root;
    while (S.length() > i)
    {
        if (S[i] == '0') //(2)
            curNode = curNode->left;
        else if (S[i] == '1') //(3)
            curNode = curNode->right;
        if (curNode->left == NULL && curNode->right == NULL) //(1)
        {
            cout << curNode->symbol;
            curNode = root;
        }
        i++;
    }
}

int main()
{
    // 입력 1 - 첫째 줄에 문자의 개수 n이 주어진다.
    int n;
    matrixchar characters(n + 1, 0);
    matrixint freq(n + 1, 0);
    cin >> n;

    // 입력 2 - 둘째 줄에 n개의 문자가 주어진다.
    for (int i = 0; i < n; i++)
        cin >> characters[i];

    // 입력 3 - 셋째 줄에 n개의 빈도값이 주어진다.
    for (int i = 0; i < n; i++)
        cin >> freq[i];

    // 입력 4 - 다음 줄에 문자열의 개수 T1이 주어진다.
    int T1, T2;
    string txt1[50], txt2[50];

    // 이후 T1개의 줄에 한 줄에 하나씩 텍스트 문자열이 주어진다.
    cin >> T1;
    for (int i = 0; i < T1; i++)
        cin >> txt1[i];

    cin >> T2;
    for (int i = 0; i < T2; i++)
        cin >> txt2[i];

    // // 출력 1 - 첫째 줄에 허프만 트리의 preorder traversal 결과를 쓴다.
    node_ptr root = huffman(n, characters, freq);
    preorder(root);
    // // 출력 2 -  둘째 줄에 허프만 트리의 inorder traversal 결과를 쓴다.
    inorder(root);

    // 출력 3 -  셋째 줄 이후로 T1개의 문자열을 인코딩한 허프만 코드를 한 줄에 하나씩 출력한다.
    matrixint codeEncoded;
    mapping encodingRes;
    encode(root, codeEncoded, encodingRes);

    for (int i = 0; i < T1; i++)
    {
        for (int j = 0; j < txt1[i].size(); j++)
        {
            mapping::iterator temp = encodingRes.find(txt1[i][j]); //구리
            for (int a : temp->second)
                cout << a;
        }
        cout << endl;
    }

    for (int i = 0; i < T2; i++)
    {
        decode(root, txt2[i]);
        if (i != T2 - 1)
            cout << endl;
    }
}