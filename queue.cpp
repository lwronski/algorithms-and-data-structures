#include <iostream>
using namespace std;
char tab[2001][2001];
int out[2001][2001];

class point
{
    int x,y;

    public:
        point() { x = 0; y =0;}
        point(int xx, int yy) { x = xx; y =yy;}

        int getX() {
           return x;
        }
        int getY() {
           return y;
        }
        void print() {
           cout << x << " " << y << endl;
        }

};

class queue
 {
     int counter,maxsize,last,first,licznik;
     point* tab;

    public:
        queue() { tab = new point[15]; counter =0; last =0; first =0 ; maxsize=15;}
        queue( int n ) { tab = new point[n]; counter =0; last =0; first = 0;maxsize=n;}

        void enqueue( point& x) {
                if(counter<maxsize)
                {
                    point A(x.getX(), x.getY() );
                    tab[first] = A;
                    counter++;
                    first = (first+1)%maxsize;
                }
        }

        point dequeue() {
                if(counter!=0) {

                        int last1;
                        last1 = last;
                        last = (last+1)%maxsize;
                        counter--;
                        return tab[last1];
                }
                else {

                    point A(0,0);
                    return A;
                }
        }

        point front() {
                if(counter!=0) {

                    return tab[last];


                }
                else {
                    point A(0,0);
                    return A;
                }
        }

        bool empty() {

            return (counter==0);

        }

        bool full() {
            return (counter==maxsize);

        }

        void clear() {

            counter =0;
            last =0;
            first =0;
        }

        int size () {

           return counter;
        }

        void resize(int n) {

            if(n>maxsize) {

                point* tabcopy = new point[n];
                licznik =0;
                for( int i =last; licznik<counter; i = (i+1)%maxsize) {
                    tabcopy[licznik] = tab[i];
                    licznik++;
                }

                delete[] tab;
                tab = tabcopy;
                maxsize = n;
                last =0;
                first = counter;
            }
        }

 };

 queue Q(4000009);


 int bfs(int n, int m)
 {
        int counter =1, x, y, sizeQ;

        for ( int j =0; j<n; j++) {
            for ( int l =0; l<m; l++)
            {
                out[j][l] =0;
                if(tab[j][l]==1) {
                    point p(j,l);
                    Q.enqueue(p);
                    tab[j][l] = 3;
                    out[j][l] = 1;
                }
            }

        }

        while(Q.size()>0)
        {

            counter++;
            sizeQ = Q.size();

            for ( int i =0; i<sizeQ; i++) {
            point p = Q.dequeue();
            x = p.getX(); y = p.getY();
            if(x-1>=0) {

                if (tab[x-1][y]==0) {
                    tab[x-1][y] = 3;
                    out[x-1][y] = counter;
                    point p(x-1,y);
                    Q.enqueue(p);
                }
                if (tab[x-1][y]==2) {
                    tab[x-1][y] = 3;
                    out[x-1][y] = counter;
                }
            }

              if(x+1<n) {

                if (tab[x+1][y]==0) {
                    tab[x+1][y] = 3;
                    out[x+1][y] = counter;
                    point p(x+1,y);
                    Q.enqueue(p);
                }
                if (tab[x+1][y]==2) {
                    tab[x+1][y] = 3;
                    out[x+1][y] = counter;
                }
            }

             if(y-1>=0) {

                if (tab[x][y-1]==0) {
                    tab[x][y-1] = 3;
                    out[x][y-1] = counter;
                    point p(x,y-1);
                    Q.enqueue(p);
                }
                if (tab[x][y-1]==2) {
                    tab[x][y-1] = 3;
                    out[x][y-1] = counter;
                }
            }
              if(y+1<m
                 ) {

                if (tab[x][y+1]==0) {
                    tab[x][y+1] = 3;
                    out[x][y+1] = counter;
                    point p(x,y+1);
                    Q.enqueue(p);
                }
                if (tab[x][y+1]==2) {
                    tab[x][y+1] = 3;
                    out[x][y+1] = counter;
                }
            }
            }
        }

          for ( int j =0; j<n; j++) {
            for ( int l =0; l<m; l++)
            {
                cout << out[j][l]-1 << " ";
            }
            cout << endl;
        }

 }

 int main()
 {
     ios_base::sync_with_stdio(0);
    int z,n,m;
    cin >> z;
    string date;
    for ( int i =0; i<z; i++)
    {
        cin >> n >> m;
        for ( int j =0; j<n; j++) {

            cin >> date;
            for ( int l =0; l<m; l++)
            {
               if(date[l]=='0') tab[j][l]=0;
                if(date[l]=='1') tab[j][l]=1;
                if(date[l]=='2') tab[j][l]=2;

            }
        }
       Q.clear();
       bfs(n,m);
    }
 }
