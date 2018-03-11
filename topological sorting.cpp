#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;
int previous[(int)10e5+5];
list<int> nodes[(int)10e5+5];
vector<int> times[(int)10e5+5];
queue<int> Q;

int dfs(int n, int m ) {
    int level = 1, w, top, counteredge = 0;
    for ( int i = 1 ; i<=n; i++ ) {
        if(previous[i]==0) {
            Q.push(i);
        }
    }

    Q.push(-1);

    while(Q.size()!=1) {
        top = Q.front();
        Q.pop();
        if ( top == -1 ) { level++; Q.push(-1); }
        else {
            times[level].push_back(top);
            while(!nodes[top].empty()) {
                w = nodes[top].front();
                nodes[top].pop_front();
                previous[w]--;
                counteredge++;
                if(previous[w]==0){
                    Q.push(w);
                }
            }
        }
    }
    if( counteredge != m ) return -1;
    else return level;
}

void clearfunction( int n ) {
    for ( int i = 0; i <=n; i++ ) {
        previous[i] = 0;
    }
    while(!Q.empty()){
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
    int z,n,m,a,b,levels;
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
        levels = dfs(n,m);
        if( levels == -1 ) cout << "NIE" << endl;
        else {
            cout << "TAK " << levels << endl;
            print(levels);
        }
    }
    return 0;
}