#include<iostream>
#include<string>
using namespace std;

class vector{

public:

    string *tab;
    int capacity;
    int size;


        vector( int a = 4, int b = 0, string c = "") {
            tab = new string[a]; capacity =a; size = b;
            for( int i =0; i<b; i++) tab[i] = c;
        }

        vector( vector & k) { // konstruktor kopiujcy

            tab = new string[k.capacity];
            capacity = k.capacity;
            size = k.size;
            for ( int i =0; i < k.size; i++) tab[i] = k.tab[i];
        }

        void doublingtab() {
            string *tabcopy;
            tabcopy = new string[capacity*2];

            for ( int i =0; i<size; i++) tabcopy[i] = tab[i];

            delete[] tab;
            tab = tabcopy;
            capacity =  capacity * 2;
        }

        void add ( string x) {

                if(size== capacity) doublingtab();
                tab[size] = x;
                size++;
        }

        int getSize() {
            return size;
        }

        void resize ( int s) {

            while(s>capacity) doublingtab();

            for ( int i = size; i<s; i++) tab[i] = "";
            size = s;
        }

        void clear() {
            size = 0;
        }

        void insert ( int i, string x) {

            if(i<=size &&  i>=0) {

            if (size == capacity) doublingtab();
            for ( int j = size-1; j>=i; j--) tab[j+1] = tab[j];
            tab[i] = x;
            size++;

            }
        }

        void erase ( int i) {

            if(i<size && i>=0 ) {

            for ( int j = i; j<size-1; j++) tab[j] = tab[j+1];
            size--;

            }
        }

        string& operator [] (int i) {

            if(i>=size) return tab[size-1];
            else return tab[i];
        }

        void operator = ( vector &k) {

        if ( this == &k) return;
            capacity = k.capacity;
            size = k.size;

            delete[] tab;
            tab = new string[capacity];

            for ( int i =0; i<size; i++) tab[i] = k.tab[i];
        }

        friend ostream& operator << (ostream&s, vector &k) {

            for ( int i =0; i<k.size; i++) s << k.tab[i] << " ";
            return s;
        }

        friend istream& operator >> (istream&s, vector &k) {

            for ( int i =0; i<k.size; i++) s >> k.tab[i];
            return s;

        }
        ~vector(){
            delete[] tab;
        }
};


void sortbucket( vector &dane, int counter) {

    vector letter[28];
    int countletter; // kod asci danej litery

     if( dane.getSize() <= 30) {

                string copy;
                // sortowanie przez wstawianie
                    for( int v= 1; v<dane.getSize(); v++)
                    {
                        for( int b = v; b>=1; b--)
                        {
                            if(dane[b-1]>dane[b]) {

                                copy = dane[b-1];
                                dane[b-1] = dane[b];
                                dane[b] = copy;

                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                cout << dane;
                return;
            }


    for( int i =0; i<dane.getSize(); i++) {

        if(dane[i].size()>counter) {

            countletter = dane[i][counter] - 65;
            letter[countletter].add(dane[i]);

        }
        else
        {
            if(dane[i].size()== counter) cout << dane[i] << " ";
        }
    }


    for( int i = 0; i<28; i++)
    {

        if(letter[i].getSize()>0) {
            sortbucket( letter[i], counter+1);
        }

    }
}

vector dane;

int main()
{
    ios_base::sync_with_stdio(0);

    int z,n;
    string in;
    cin >> z;
    while(z--) {

        dane.clear();
        cin >> n;
        while(n--) {
            cin >> in;
            dane.add(in);
        }
        sortbucket(dane,0);
        cout << endl;
    }
}
