#include <iostream>
using namespace std;
int array[5000000+5];

int median(int left, int right, int k);

void setmedianinmiddle(int left, int right);

bool setvalue( int piwot, int & i, int & q, int & p );

void quicksort(int left, int right);

int main() {
    int z,n,k;
    cin >> z;
    while(z--) {
        cin >> n >> k;
        for ( int i = 0; i < n; i++ ) {
            cin >> array[i];
        }
       cout << median(0, n-1,k-1) << endl;
    }
    return 0;
}

int median(int left, int right, int k)
{
    if( right - left <= 10 ) {
        quicksort(left,right);
        return array[k];
    }

    setmedianinmiddle(left,right);

    int split = (right-left+1)/5;
    int piwot = median(left + split*2, left + split*3-1, left + (split*2+ split*3-1)/2);

    int i = left, q = 0, p = right;

    setvalue(piwot,i,q,p);

    if( k <= i-q-1 ) return median(left, i-q-1, k);
    if( k >= i ) return median(i, right,k);
    return array[k];
}

bool setvalue( int piwot, int & i, int & q, int & p) {

    while( i <= p ) {
        if ( array[i] > piwot){
            swap(array[i], array[p--]);
        }
        else if ( array[i] == piwot) {q++; i++;}
        else { swap( array[i-q], array[i]); i++; }
    }

}

void setmedianinmiddle(int left, int right) {

    int countsplit = (right-left+1)/5;
    int modulo = (right-left+1)%5;

    for ( int i = 0; i < countsplit; i++ ) {

        for ( int j = 0; j < 5;  j++ ) {
            for ( int k = left + i+countsplit; k <=right-modulo - countsplit*j; k += countsplit ) {
                if( array[k-countsplit] > array[k] ) {
                    swap(array[k-countsplit], array[k]);
                }
            }
        }
    }
}


void quicksort(int left, int right) {

    if(left>=right) return;

    int raand = rand()%(right-left+1) + left;
    int piwot = array[raand];

    int i = left, k = 0, p = right;
    while( i <= p ) {
        if ( array[i] > piwot){
            swap(array[i], array[p--]);
        }
        else if ( array[i] == piwot) {k++; i++;}
        else { swap( array[i-k], array[i]); i++; }
    }

    if( right - i + 1 < i -k - left ) {
        quicksort(i,  right);
        quicksort(left,i -k-1);
    }
    else {
        quicksort(left, i -k-1);
        quicksort(i, right);
    }
}
