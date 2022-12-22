#include <bits/stdc++.h>

using namespace std;

ifstream in;
ofstream out;

const int N = 110, M = N * N;
int n;        // 點數
int m;        // 邊數
int G[N][N];  // 鄰接矩陣
bool st[N];   // st[i] 表示 i 是否在 MST 中
int dist[N];  // dist[i] 表示 i 到 MST 的最短距離
int pre[N];   // pre[i] 表示 i 的前驅節點

// 初始化
void init() {
    memset(G, 0x3f, sizeof G);
    memset(st, 0, sizeof st);
    for (int i = 0; i < n; i++) dist[i] = 0x3f3f3f3f;
    dist[0] = 0;  // 任意選擇一個點當作起點
}

// Prim 演算法
void prim() {
    for (int i = 0; i < n; i++) {
        int t = -1;
        // 找到與 MST 距離最近的點
        for (int j = 0; j < n; j++)
            if (!st[j] && (t == -1 || dist[j] < dist[t])) t = j;
        // 將 t 加入 MST
        st[t] = true;
        // 更新與 t 相鄰的點的距離
        for (int j = 0; j < n; j++)
            if (!st[j] && G[t][j] < dist[j]) {
                dist[j] = G[t][j];
                pre[j] = t;
            }
    }
}

int main() {
    // 輸入圖形信息

    in.open("sample.txt");
    out.open("output.txt");

    cout << "File name: ";
    cin >> filename;
    out << "File name: " << filename << "\n";
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a][b] = G[b][a] = c;
    }

    init();  // 初始化
    prim();  // 執行 Prim 演算法

    // 輸出結果
    int sum = 0;
    for (int i = 1; i < n; i++) sum += G[i][pre[i]];
    cout << sum << endl;

    return 0;
}