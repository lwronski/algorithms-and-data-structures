#include <iostream>
using namespace std;
long long tree[20*1000000];

long long setvalueintree(long long n);
void reserve(long long a, long long size);
void cancel(long long a, long long size);
void sum(long long a, long long b, long long size);

int main() {
    ios_base::sync_with_stdio(0);
    long long z,n,k,size,a,b;
    string in;
    cin >> z;
    while( z-- ) {
        cin >> n >> k;
        size = setvalueintree(n);
        while( k-- ) {

            cin >> in;
            if ( in == "RESERVE") {
                cin >> a;
                reserve(a, size);
            }
            if ( in == "CANCEL") {
                cin >> a;
                cancel(a, size);
            }
            if ( in == "SUM") {
                cin >> a >> b;
                sum(a,b, size);
            }
        }
        cout << endl;
    }
    return 0;
}

void sum(long long a, long long b, long long size) {
    long long ia = size + a -1;
    long long ib = size + b - 1;
    long long suma = tree[ia];
    if ( a != b ) suma += tree[ib];
    while( ia/2 != ib/2 ) {
        if ( ia % 2 == 0 ) suma += tree[ia+1];
        if ( ib %2 == 1 ) suma += tree[ib - 1];
        ia /= 2;
        ib /= 2;
    }
    cout << suma << endl;
}

void cancel(long long a, long long size) {
    long long i = size + a - 1;
    if ( tree[i] == 0 ) {
        cout << "ERROR" << endl;
        return;
    }
    tree[i] = 0;
    while(i>1){
        i /= 2;
        tree[i] = tree[i*2] + tree[i*2+1];
    }
}


void reserve(long long a, long long size) {
        long long i = size + a - 1;
        if ( tree[i] != 0 ) {
        cout << "ERROR" << endl;
        return;
    }
    tree[i]++;
    while(i>1){
        i /= 2;
        tree[i] = tree[i*2] + tree[i*2+1];
    }
}

long long setvalueintree(long long n) {

    long long power = 1;
    while( power < n ) {
        power *= 2;
    }
    for ( int i = 0; i < power*2+5; i++) {
        tree[i] = 0;
    }
    return power;
}