#include <iostream>
using namespace std;

template < typename T1 > class stackMin {

    T1 * tab;
    T1 * tabmini;
    int counter,maxsize, countermini;

    public:

        stackMin( int a = 4 ) { tab = new T1[a]; counter = 0; maxsize = a; tabmini = new T1[a]; countermini =0; }

        void push ( T1 x )
        {
            if(counter==maxsize)
            {
                resize(maxsize*2);
            }
            tab[counter] = x ;  // dodanie elementu do podstawowego stosu
            counter++;
            if(countermini==0) // dodanie elementu do mini stosu
            {
                tabmini[countermini] = x;
                countermini++;
            }
            else
            {
                if(tabmini[countermini-1]>=x)
                {
                    tabmini[countermini] = x;
                    countermini++;
                }
            }
        }

        bool pop()
        {
            if(counter==0) return false;
            else
            {
                if(tab[counter-1]==tabmini[countermini-1])
                {
                    countermini--;
                }
                counter--;
                return true;
            }
        }

        T1 top()
        {
            return tab[counter-1];
        }

        T1 min()
        {
            return tabmini[countermini-1];
        }

        void clear()
        {
            counter =0;
            countermini =0;
        }

        bool empty()
        {
            if(counter==0) return true;
            else return false;
        }

        void resize( int n )
        {
            if( n > 1000000 ) n = 1000000;
            T1 * tabcopy = new T1[n];
            T1 * tabcopymini = new T1[n];
            for( int i = 0; i<maxsize; i++) {
                tabcopy[i] = tab[i];
                tabcopymini[i] = tabmini[i];
            }
            maxsize = n;
            delete[] tab;
            delete[] tabmini;
            tab = tabcopy;
            tabmini = tabcopymini;
        }
        ~stackMin()
        {
            delete[] tab;
            delete[] tabmini;
        }

};

template < typename T1 > class myPair {

    public:
        T1 first;
        T1 second;


};

template < typename T1 > class queueMin {

    T1 * tab;
    stackMin<T1> F;
    stackMin<T1> S;

    int counter,maxsize,last,first;

    public:

        queueMin( int a = 4 ) { tab = new T1[a]; counter = 0; maxsize = a; last = 0, first = 0; }

        void prescribe()
         {
            if(S.empty())
            {
                while( !F.empty())
                {
                    S.push(F.top());
                    F.pop();
                }
            }
        }

        void enqueue( T1 x)
        {
            if(counter==maxsize) resize(maxsize*2);

            tab[first] = x;
            counter++;
            first = (first+1)%maxsize;
            if(F.empty())
            {
                F.push(x);
                if(S.empty()) prescribe();
            }
            else
            {
                int i = 0;
                while( !F.empty() && F.top() > x)
                {
                    F.pop();
                    i++;
                }
                F.push(x);
                if(S.empty()) prescribe();
            }

        }

        bool dequeue()
        {
            if(counter == 0)
            {
                return false;
            }
            else
            {
                if(tab[last] == S.top() ) S.pop();
                if(S.empty()) prescribe();
                last = (last+1)%maxsize;
                counter--;
                return true;
            }
        }

        T1 front()
        {
            return tab[last];
        }

        T1 min()
        {
            if( !F.empty() && F.min() < S.min() ) return F.min();
            else return S.min();
        }

        void clear()
        {
            counter =0;
            last =0;
            first =0;
            S.clear();
            F.clear();
        }

        bool empty()
        {
            return (counter == 0);
        }

        void resize(int n)
        {
            if( n > 1000000 ) n = 1000000;
            T1 * tabcopy =  new T1[n];
            int licznik = 0;
            for ( int i = last; licznik<counter; i = (i+1)%maxsize )
            {
                tabcopy[licznik] = tab[i];
                licznik++;
            }
            delete[] tab;
            tab = tabcopy;
            maxsize = n;
            last =0;
            first = counter;
        }

        ~queueMin()
        {
            delete[] tab;
        }

};

template <typename T1> void solveStack( stackMin<T1> & S, int n)
{
    string in;
    T1 value;

    while( n-- )
    {
        cin >> in;

        if(in=="push")
        {
            cin >> value;
            S.push(value);
        }
       if(in=="pop")
        {
            if( S.empty() )
            {
                cout << "ERROR" << endl;
            }
            else
            {
                cout << S.top() << endl;
                S.pop();
            }
        }
       if(in=="top")
        {
            if( S.empty() )
            {
                cout << "EMPTY" << endl;
            }
            else
            {
                cout << S.top() << endl;
            }
        }
        if(in=="min")
        {
            if( S.empty() )
            {
                cout << "EMPTY" << endl;
            }
            else
            {
                cout << S.min() << endl;
            }
        }
        if(in=="clear")
        {
            S.clear();
        }
        if(in=="empty")
        {
            if( S.empty() )
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}

template <typename T1> void solveQueue( queueMin<T1> & S, int n)
{
    string in;
    T1 value;

    while( n-- )
    {
        cin >> in;

        if(in=="enqueue")
        {
            cin >> value;
            S.enqueue(value);
        }
        if(in=="dequeue")
        {
            if( S.empty() )
            {
                cout << "ERROR" << endl;
            }
            else
            {
                cout << S.front() << endl;
                S.dequeue();
            }
        }
        if(in=="front")
        {
            if( S.empty() )
            {
                cout << "EMPTY" << endl;
            }
            else
            {
                cout << S.front() << endl;
            }
        }
        if(in=="min")
        {
            if( S.empty() )
            {
                cout << "EMPTY" << endl;
            }
            else
            {
                cout << S.min() << endl;
            }
        }
        if(in=="clear")
        {
            S.clear();
        }
        if(in=="empty")
        {
            if( S.empty() )
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
    }
}
