#include <bits/stdc++.h>

using namespace std;

ifstream in;
ofstream out;

typedef struct edge {
    char from;
    char to;
    int weight;
} Edge;

const int N = 256;
int n = 0;    // 點數
int m;        // 邊數
int G[N][N];  // 鄰接矩陣
bool st[N];    // st[i] 表示 i 是否在 MST 中
int dist[N];  // dist[i] 表示 i 到 MST 的最短距離
int pre[N];   // pre[i] 表示 i 的前驅節點


map<char, int> mp;
map<int, char> rmp;

char r; // root 

// 初始化 dist
void initDist() {
    for (int i = 0; i < n; i++) 
        if (G[mp[r]][i] < dist[i]) 
            dist[i] = G[mp[r]][i];
}

// Prim 演算法
void prim() {
    for (int i = 0; i < n; i++) {
        int t = 0;
        while(st[t]) {t++;}
        // 找到與 MST 距離最近的點
        for (int j = 0; j < n; j++)
            if (!st[j] && dist[j] < dist[t]) t = j;
        // 將 t 加入 MST
        st[t] = 1;
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
    string filename="sample_p.txt";
    cout << "File name: ";
    cin >> filename;

    in.open(filename);
    out.open("output_p.txt");

    in >> m;

    cin.ignore();

    bool check[N] = {0};

    memset(G, 0x3f, sizeof G);
    memset(st, 0, sizeof st);
    for (int i = 0; i < m; i++) {
        char a, b;
        int c;
        // 你不能什麼都要阿!!! 
        in >> a >> b >> c;
        if (mp.find(a) == mp.end()) {
            mp[a] = n++;
            rmp[mp[a]] = a;
        }
        if (mp.find(b) == mp.end()) {
            mp[b] = n++;
            rmp[mp[b]] = b;
        }
        G[mp[a]][mp[b]] = G[mp[b]][mp[a]] = c;
    }

    in >> r;

    memset(dist, 0x3f, sizeof dist);

    dist[mp[r]] = 0;  // 選擇 r 點當作起點
    st[mp[r]] = true;
    initDist();

    prim();  // 執行 Prim 演算法

    // 輸出結果

    vector<Edge> res;
    for (int i = 0; i <n;i++) {
        if (i == mp[r]) continue;
        res.push_back((Edge){.from = rmp[pre[i]] < rmp[i] ? rmp[pre[i]] : rmp[i], .to = rmp[pre[i]] > rmp[i] ? rmp[pre[i]] : rmp[i], .weight = dist[i]});  // C99 Syntax
    }

    sort(res.begin(), res.end(), [](Edge const &lhs, Edge const &rhs) {
        return lhs.weight < rhs.weight;
    });


    for (vector<Edge>::iterator iter = res.begin(); iter != res.end(); iter++) {
        cout << iter->from << " " << iter->to << " " << iter->weight <<endl;
        out << iter->from << " " << iter->to << " " << iter->weight << endl;
    }

    return 0;
}