#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int pullout( string& tree, int start, int end) {
    int brace = 0;
    for ( int i = start; i<=end; i++) {
        if( tree[i] == '(' ) brace++;
        else brace--;
        if(brace==0) return i-start+1;
    }
}

unsigned long long hashf( string& tree, int& start) {

    unsigned long long hashtree;
    start++;
    vector<unsigned long long>tab;
    while ( true ) {
        if(tree[start]=='(') {
                tab.push_back(hashf(tree, start));
           }
        else {
             start++;
             break;
           }
    }

    sort(tab.begin(), tab.end());
    hashtree = 93407 ;
    unsigned long long P = 93407;
    for ( int i = 0; i<tab.size(); i++) {
        P *= 93407;
        hashtree *= (tab[i]*P)^98407;
    }
    return hashtree;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int z,n;
    unsigned long long * tab;
    string in;
    cin >> z;
    while(z--) {
        cin >> n; int i = n;
        tab = new unsigned long long[n];
        while(i--){
            cin >> in;
            int j = 0;
            tab[i] = hashf(in, j);
        }
        sort( tab, tab+n);
        int counter = 1;
         for ( int i = 1; i<n; i++) {
            if(tab[i]!=tab[i-1]) counter++;
        }
        cout << counter << endl;
        delete[] tab;
    }
    return 0;
}
