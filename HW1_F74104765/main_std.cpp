#include <bits/stdc++.h>
using namespace std;
int main() {
    ///////////////////// Variables Declarations ////////////////////////
    int traMat[1000][1000] = {0};
    vector<tuple<int, int, int> > spaMat;
    int n, m, r, c, v;
    //////////////////////////// Input Data //////////////////////////////
    cin >> n >> m;
    while (cin >> r >> c >> v) {
        traMat[r][c] = v;
        spaMat.push_back(tuple<int, int, int>(r, c, v));
    }
    vector<tuple<int, int, int> > spaMatBackup(spaMat);
    ////////////////// Traditional Matrix Transformation //////////////////
    clock_t traT = clock();
    int traMatTmp[1000][1000] = {0};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            traMatTmp[j][i] = traMat[i][j];

    memcpy(traMat, traMatTmp, sizeof(traMatTmp));
    traT = clock() - traT;
    /////////////////////// End of Transformation ////////////////////////

    /////////////////////// Sparse Matrix Transformation /////////////////
    clock_t spaT = clock();
    vector<tuple<int, int, int> > spaMatTmp;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < spaMat.size(); j++)
            if (get<1>(spaMat.at(j)) == i)
                spaMatTmp.push_back(tuple<int, int, int>(get<1>(spaMat.at(j)), get<0>(spaMat.at(j)), get<2>(spaMat.at(j))));

    spaMat.assign(spaMatTmp.begin(), spaMatTmp.end());
    spaT = clock() - spaT;
    /////////////////////// End of Sparse Matrix Transformation /////////////////

    ////////////////////////// Output Result //////////////////////////////
    for_each(spaMatBackup.begin(), spaMatBackup.end(), [](auto& tuple) { cout << "(" << get<0>(tuple) << ", "
                                                                              << get<1>(tuple) << ", "
                                                                              << get<2>(tuple) << ") becomes ("
                                                                              << get<1>(tuple) << ", "
                                                                              << get<0>(tuple) << ", "
                                                                              << get<2>(tuple) << ") in the transpose" << endl; });
    cout << traT << "ms" << endl;
    cout << spaT << "ms" << endl;
}
