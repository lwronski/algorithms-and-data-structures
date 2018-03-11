#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;
int previous[(int)10e5+5];
int color[(int)10e5+5];
int timestab[(int)10e5+5];
list<int> nodes[(int)10e5+5];
vector<int> times[(int)10e5+5];
stack<int>Q;

// 0 - nieodwiedzony, 1 - badany, 2 - przetworzony;
int dfs( int node) {
    if( color[node] == 1 ) return -1;
    if ( color[node] == 0) {
        color[node] = 1;
        for (std::list<int>::const_iterator iterator = nodes[node].begin(), end = nodes[node].end(); iterator != end; ++iterator) {
            if (dfs(iterator.operator*()) == -1) {
                return -1;
            }
        }
        color[node] = 2;
        Q.push(node);
    }
}

void settimes( int n) {
    for (std::list<int>::const_iterator iterator = nodes[n].begin(), end = nodes[n].end(); iterator != end; ++iterator) {
        if( timestab[iterator.operator*()] < timestab[n] + 1 ) timestab[iterator.operator*()] = timestab[n] + 1;
    }
}

void inserttime(int n ) {
    for ( int i = 1 ; i <= n; i++ ) {
        times[timestab[i]].push_back(i);
    }
}

int firstdfs(int n){

    for ( int i = 1 ; i<=n; i++ ) {
        if(color[i] == 0) {
            if(dfs(i)==-1) {
                return -1;
            }
        }
    }
    int maxlevel = -1;
    while(!Q.empty()) {
        settimes(Q.top());
        maxlevel = max(maxlevel, timestab[Q.top()]);
        Q.pop();
    }
    inserttime(n);
    return maxlevel;
}

void clearfunction( int n ) {
    for ( int i = 0; i <=n; i++ ) {
        previous[i] = 0;
        color[i] = 0;
        timestab[i] = 1;
    }

    while(!Q.empty()) {
        Q.pop();
    }

    for ( int i = 0; i<=n; i++ ) {
        while(!nodes[i].empty()) {
            nodes[i].pop_back();
        }
        while(!times[i].empty()){
            times[i].pop_back();
        }
    }
}

void print( int n ) {
    for ( int i = 1; i<=n; i++ ) {
        cout << times[i].size() << " ";
        while(times[i].size()) {
            cout << times[i].back() << " ";
            times[i].pop_back();
        }
        cout << endl;
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    int z,n,m,a,b;
    int levels;
    char sign[1];
    cin >> z;
    while(z--) {
        cin >> n >> m;
        clearfunction(n);
        for ( int i = 0; i < m;  i++ ) {
            cin >> a >> sign >> b;
            nodes[a].push_back(b);
            previous[b]++;
        }
        levels = firstdfs(n);
        if( levels == -1 ) cout << "NIE" << endl;
        else {
            cout << "TAK " << levels << endl;
            print(levels);
        }
    }
    return 0;
}
