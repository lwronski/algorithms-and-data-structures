#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
bool grade[(int)10e4+5];
int cost[2*(int)10e4+5];
int road[2*(int)10e4+5];
int cycle[2*(int)10e4+5];
vector<tuple<int,int,int,bool,int, int>> edges[(int)10e4+5];
// wierzcholek, dlugosc, iloscpiasku, czy odwiedzony, kolejnosc w sorcie
bool checkifhavecycle(int n);

void clearfunction(int n);

int DfsEuler(int node, int & counter);

void deleteedges(int x, int y, bool flag);

bool checksum(int n);

void roadcycle(int n);

void print(int x, int index, int n);

void findstart(int n, int &index, int &start, int & end);

int main() {
    int z,n,x,y,l,d;
    cin >> z;
    while(z--) {
        cin >> n;
        clearfunction(n);
        for( int i = 0; i < 2*n; i++ ) {
            cin >> x >> y >> l >> d;
            edges[x].push_back(make_tuple(y,l,d,false,0, i+1));
            edges[y].push_back(make_tuple(x,l,d,false,0, i+1));
            grade[x]++; grade[y]++;
        }

        if(!checkifhavecycle(n) || !checksum(n)) cout << "NIE" << endl;
        else {
            cout << "TAK" << endl << 2*n << endl;
            int counter = 0;
            DfsEuler(1 , counter );
            int start = -1, index =-1, end = -1;
            roadcycle(2*n);
            findstart(2*n, index, start, end);
//            cout << start << " " << end << " " << index  << endl;
            for( int i = 0; i < edges[start].size(); i++ ) {
                if ( get<4>(edges[start][i]) == index ) {
                    cout << get<5>(edges[start][i]) << " " << end << endl;
                }
            }
            print(end, (index+1)%(2*n+1), 2*n -1);
        }
    }
    return 0;
}

void findstart(int n, int &index, int &start, int & end) {

    int sumsand = 0, minsumsand = 10;
    start = 1;
    end = cycle[1];
    index = 1;

   for ( int i = 0; i < n ; i ++) {
        sumsand += cost[i] - (road[i]/2) - (road[(i+1)%n]/2);

        if ( sumsand < minsumsand) {
            index = (i+2)%n;
            start = cycle[i+1];
            end = cycle[(i+2)%n];
            minsumsand = sumsand;
        }
    }

}

void print(int x, int index, int n) {
    if(index==0) index = 1;
    for ( int i = 0; i < n; i++) {
        for ( int k = 0;  k < edges[x].size(); k++ ) {

            if ( get<4>(edges[x][k]) == index) {
                cout <<get<5>(edges[x][k]) << endl;
                x = get<0>(edges[x][k]);
                break;
            }
        }
        index = (index+1)%(n+2);
        if(index==0) index = 1;
    }

}

void roadcycle(int n) {
    int x,y;
    for ( int i = 0; i < n; i++) {
        x = cycle[i];
        y = cycle[(i+1)%n];
        for ( int j = 0; j < edges[x].size(); j++) {

            if ( get<3>(edges[x][j]) && get<0>(edges[x][j]) == y ) {
                cost[i] = get<2>(edges[x][j]);
                road[i] = get<1>(edges[x][j]);
                get<3>(edges[x][j]) = false;
                get<4>(edges[x][j]) = i+1;
                deleteedges(y,x,false);
                break;
            }
        }
    }
}

bool checksum(int n) {

    long suml = 0, sumd = 0;

    for( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j< edges[i].size(); j++ ) {
            suml += get<1>(edges[i][j]);
            sumd += get<2>(edges[i][j]);
        }
    }

    if ( suml <= sumd) return true;
    else return false;

}

int DfsEuler(int node, int & counter) {
    for( int i = 0; i < edges[node].size(); i++) {

        if(!get<3>(edges[node][i])) {
            deleteedges( get<0>(edges[node][i]),node, true);
            get<3>(edges[node][i]) = true;
            DfsEuler(get<0>(edges[node][i]), counter);
        }
    }
    cycle[counter++] = node;
}

void deleteedges(int x, int y, bool flag) {
    for ( int i = 0; i < edges[x].size(); i++) {
        if ( get<0>(edges[x][i]) == y && get<3>(edges[x][i]) == !flag ) {
            get<3>(edges[x][i]) = flag;
            return;
        }
    }
}

bool checkifhavecycle(int n) {
    for (int i = 1; i <= n; i++) {
        if (!grade[i]) return false;
    }
    return true;
}

void clearfunction(int n) {
    for ( int i = 0; i <= n ; i++ ) {
        grade[i] = 0;
    }
    for ( int i = 0; i<=n; i++ ) {
        while(!edges[i].empty()) {
            edges[i].pop_back();
        }
    }
}

/*
 1
 4
 1 2 4 6
 2 4 2 4
 3 2 4 2
 4 3 10 8
 2 1 8 7
 4 3 2 1
 1 4 2 6
 3 1 4 5
 */