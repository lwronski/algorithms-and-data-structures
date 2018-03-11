#include <iostream>
using namespace std;
long long int mandaty[10000+5];

struct parthia{
    long long int id;
    long long int level;
    long long numbervote;

    bool operator<(const parthia& rhs) const
    {
        if ( this->numbervote* rhs.level < this->level*rhs.numbervote  ){
            return true;
        }
        else return false;
    }
    bool operator>(const parthia& rhs) const
    {
        if ( this->numbervote* rhs.level > this->level*rhs.numbervote  ){
            return true;
        }
        else return false;
    }
    bool operator==(const parthia& rhs) const
    {
        if ( this->numbervote* rhs.level == this->level*rhs.numbervote  ){
            return true;
        }
        else return false;
    }
};

parthia heap[10000+5];

void setheap(long long int n);
void kopcuj( long long int i);
void obliczmandaty(long long int m);
void setdate(long long int n);

int main() {
    ios_base::sync_with_stdio(0);
    long long int z,n,m,d;
    cin >> z;
    while(z--) {
        cin >> n >> m;
        setdate(n); // wyzerowanie danych
        for ( long long int i = 1; i <= n ; i++ ) {
            cin >> heap[i].numbervote;
            heap[i].id = i;
            heap[i].level = 1;
        }
        setheap(n);
        obliczmandaty(m);
        for ( long long int i = 1; i <= n ; i++ ) {
            cout << mandaty[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

void setdate(long long int n) {
    for ( long long int i = n+1; i <= 5000 ; i++ ) {
        heap[i].numbervote = -1;
        heap[i].level = 1;
        heap[i].id = 0;
    }
    for (long long int i = 0; i <= 5000 ; i++ ) {
        mandaty[i] = 0;
    }
}

void obliczmandaty(long long int m) {
    while(m--) {
        mandaty[heap[1].id]++;
        heap[1].level++;
        kopcuj(1);
    }
}

void setheap(long long int n) {
    for( long long int i = n; i >= 1; i-- ) {
        kopcuj(i);
    }
}

void kopcuj(long long int i) {

    int largest;

    if ( heap[i*2] > heap[i]) {
        largest = i*2;
    }
    else {
        largest = i;
    }

    if ( heap[i*2+1] > heap[largest]) {
       largest = i*2+1;
    }

    if ( heap[i*2] == heap[largest]) {
        if ( heap[i*2].numbervote > heap[largest].numbervote ) {
            largest = i*2;
        }
        else if (  heap[i*2].numbervote == heap[largest].numbervote && heap[i*2].id < heap[largest].id ) {
           largest = i*2;
        }
    }

    if ( heap[i*2+1] == heap[largest] ) {
        if ( heap[i*2+1].numbervote > heap[largest].numbervote ) {
            largest = i*2+1;
        }
        else if (  heap[i*2+1].numbervote == heap[largest].numbervote && heap[i*2+1].id < heap[largest].id ) {
            largest = i*2+1;
        }
    }
    if( i != largest) {
        swap(heap[i], heap[largest]);
        kopcuj(largest);
    }

}