#include <bits/stdc++.h>

using namespace std;

typedef struct items {
    int i;
    int j;
    int dir;
} Items;

typedef struct vector2 {
    short a;
    short b;
} Vector2;

template <typename T>
ostream& operator<<(ostream& out, stack<T>& a) {
    vector<string> record;
    int i = 1;
    while (!a.empty()) {
        record.push_back(to_string(a.top().i - 1) + "," + to_string(a.top().j - 1));
        a.pop();
    }

    reverse(record.begin(), record.end());
    for (auto str : record)
        out << i++ << ":" << str << endl;
    return out;
}

const int mapSize = 17;
int maze[20][20] = {0};

void Path(const int m, const int p) {
    // (m, p) are target position
    ofstream out;
    out.open("output.txt");
    int mark[20][20] = {0};
    mark[2][1] = 1;
    Vector2 move[8] = {
        {.a = 0, .b = 1},    // E
        {.a = 1, .b = 1},    // SE
        {.a = 1, .b = 0},    // S
        {.a = 1, .b = -1},   // SW
        {.a = 0, .b = -1},   // W
        {.a = -1, .b = -1},  // NW
        {.a = -1, .b = 0},   // N
        {.a = -1, .b = 1}    // NE
    };
    stack<Items>
        stack;
    Items temp = {.i = 2, .j = 1, .dir = 0};
    int stepCount = 0;
    out << "0:1,0" << endl;
    // set temp.x, temp.y, and temp.dir
    stack.push(temp);
    while (!stack.empty()) {  // stack not empty
        temp = stack.top();
        stack.pop();  // unstack
        out << ++stepCount << ":" << temp.i - 1 << "," << temp.j - 1 << endl;
        while (temp.dir < 8)  // move forward
        {
            int g = temp.i + move[temp.dir].a;
            int h = temp.j + move[temp.dir].b;
            if ((g == m) && (h == p)) {  // reached exit
                // output path
                out << ++stepCount << ":" << temp.i - 1 << "," << temp.j - 1 << endl;
                out << ++stepCount << ":" << g - 1 << "," << h - 1 << endl;
                out << "successfully escaped!!" << endl;
                //////////////////////////////// De Bu G ////////////////////////////////
                // stack.push({.i = temp.i, .j = temp.j, .dir = 0});
                // stack.push({.i = m, .j = p, .dir = 0});
                // cout << stack;
                return;
            }
            if ((!maze[g][h]) && (!mark[g][h])) {  // new position
                mark[g][h] = 1;
                stack.push({.i = temp.i, .j = temp.j, .dir = temp.dir + 1});  // stack in
                temp.i = g;
                temp.j = h;
                temp.dir = 0;
                out << ++stepCount << ":" << g - 1 << "," << h - 1 << endl;
            } else {
                temp.dir++;  // try next direction
            }
        }
    }
    cout << "Failed to escaped." << endl;
}
int main(int argc, char** argv) {
    string filename;
    cout << "enter filename:";
    cin >> filename;
    ifstream fin(filename);
    fill_n((int*)maze, (20 * 20), 1);
    for (int i = 1; i <= mapSize; i++) {
        string line;
        getline(fin, line);
        for (int k = 1; auto c : line)
            maze[i][k++] = c - '0';
    }
    for (int i = 1; i <= mapSize; i++, cout << endl)
        for (int j = 1; j <= mapSize; j++)
            cout << maze[i][j];
    Path(16, 17);
}
