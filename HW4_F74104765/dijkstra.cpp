#include <bits/stdc++.h>
using namespace std;

typedef struct edge {
    char from;
    char to;
    int weight;
} Edge;

const int N = 1005, INF = 0x3f3f3f3f;

// adjacency matrix to represent the graph
int adj[N][N];

// distances[i] stores the shortest distance from the source vertex to vertex i
int distances[N];

// priority queue to store the vertices, ordered by their distance from the source
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

ifstream in;
ofstream out;

int n, m; // n : number of vertex,  m : number of edge

map<char, int> mp;
map<int, char> rmp;

void dijkstra(int source) {
    // initialize distances to INF and set the source distance to 0
    memset(distances, 0x3f, sizeof(distances));
    distances[source] = 0;

    // insert the source vertex into the priority queue
    pq.emplace(0, source);

    while (!pq.empty()) {
        // get the vertex with the smallest distance
        int u = pq.top().second;
        pq.pop();

        // visit all the neighbors of u
        for (int v = 0; v < n; v++) {
            // if v is not a neighbor, skip it
            if (adj[u][v] == INF) continue;

            // calculate the distance to v through u
            int distance = distances[u] + adj[u][v];

            // if the distance to v through u is shorter than the current distance to v, update it
            if (distance < distances[v]) {
                distances[v] = distance;
                pq.emplace(distance, v);
            }
        }
    }
}

int main() {
    // 輸入圖形信息
    string filename = "sample_d.txt";
    cout << "File name: ";
    cin >> filename;

    in.open(filename);
    out.open("output_d.txt");

    in >> m;

    cin.ignore();

    bool check[N] = {0};

    // initialize the adjacency matrix to INF
    memset(adj, 0x3f, sizeof adj);

    for (int i = 0; i < m; i++) {
        char u, v;
        int c;
        // 你不能什麼都要阿!!!
        in >> u >> v >> c;
        if (mp.find(u) == mp.end()) {
            mp[u] = n++;
            rmp[mp[u]] = u;
        }
        if (mp.find(v) == mp.end()) {
            mp[v] = n++;
            rmp[mp[v]] = v;
        }
        adj[mp[u]][mp[v]] = c;
    }

    char source;
    in >> source;

    // run Dijkstra's algorithm
    dijkstra(mp[source]);
    vector<Edge> res;
    // print the distances to all the vertices
    for (int i = 0; i < n; i++) 
        res.push_back((Edge){.from = 0, .to = rmp[i], .weight = distances[i]});

    sort(res.begin(), res.end(), [](Edge const &lhs, Edge const &rhs) {
        return lhs.weight < rhs.weight;
    });

    for(int i = 0; i < n; i++) 
        if(res[i].weight != INF){
            cout << res[i].to << " " << res[i].weight << endl;
            out << res[i].to << " " << res[i].weight << endl;
        }
        
    return 0;
}
