#include <iostream>
using namespace std;
pair<long, long> array[1000000+5];
pair<long,long> newarray[1000000+5];
long countarray[1000000+5];

void radixsort(long n);
void countsort(long level, long n);
void coutarray(long n);
void countime(long n);
long getnumber(long first, long n, long i);

int main() {
    ios_base::sync_with_stdio(0);
    long z,n;
    cin >> z;
    while(z--) {
        cin >> n;
        for ( int i = 0; i < n ; i++ ) {
            cin >> array[i].second >> array[i].first;
        }
        radixsort(n);
        coutarray(n);
        countime(n);
    }
    return 0;
}

void countime(long n) {
    long time = 0;
    long pause = 0;
    time = array[n-1].first - array[n-1].second;
    for ( int i = n-2; i >=0 ; i-- ) {
        if( time <= array[i].first) {
            time -= array[i].second;
        }
        else {
            pause += time - array[i].first;
            time = array[i].first - array[i].second;
        }
        if(time<0) {
            cout << "ERROR" << endl;
            return;
        }
    }
    cout << time << " " << pause << endl;
}

void coutarray(long n) {
    for ( int i = 0; i < n ; i++ ) {
        cout << array[i].first<< " ";
    }
    cout << endl;
}

void radixsort(long n) {
    int level = 0;
    while(level<=2){
        countsort(level,n);
        level++;
    }
}

long getnumber(long first, long n, long i) {

    long level = 0;
    while( first>0) {
        if(level == i )  return (first%n);
        first /= n;
        level ++;
    }
    return 0;
}

void countsort(long level, long n) {


    for ( int i = 0; i < n; i++) {
        countarray[i] = 0;
    }

    for ( int i = 0; i < n; i++) {
        ++countarray[getnumber(array[i].first,n,level)];
    }

    for ( int i = 1; i < n; i++) {
        countarray[i] += countarray[i-1];
    }

    for ( int i = n-1; i >= 0 ; i--) {
        newarray[--countarray[getnumber(array[i].first,n,level)]] = array[i];
    }
    for ( int i = n-1; i >= 0 ; i--) {
        array[i] = newarray[i];
    }

}