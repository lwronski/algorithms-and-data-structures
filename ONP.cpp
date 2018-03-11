#include <iostream>
using namespace std;
long long value[256];
long long counteronp =0;
class stack
{
    long long *tab = NULL;
    int counter,maxsize;

    public:
        stack() { tab = new long long[15]; counter =0; maxsize =15;}
        stack(int n) { tab = new long long[n]; counter =0; maxsize = n;}

        void push(long long &x) {

            if(counter<maxsize)
            {
                tab[counter] = x;
                counter++;
            }
        }

        long long pop() {

            if(counter!=0) {

                counter--;
                return tab[counter];
            }
            else return 0;
        }

        long long top() {

             if(counter!=0) {

                return tab[counter-1];
            }
            else  return 0;
        }

        bool empty() {

            return (counter==0);

        }

        bool full() {
            return (counter==maxsize);
        }

        void clear() {

            counter =0;
        }
        int size() {

            return counter;
        }
        void resize(int n) {

            if(n>maxsize) {
              long long * tabcopy = new long long[n];

                for( int i =0; i<maxsize; i++) {

                    tabcopy[i] = tab[i];
                }
                maxsize = n;
                delete[] tab;
                tab = tabcopy;
            }
        }
        ~stack() {

           delete[] tab;
        }
};

stack S(200001);

string onpstack(string expression) {

    string onp = "";
    long long length = expression.size();
    long long counter =0, top,pop;
    long long x = '(';
    S.push(x);
    expression[length] = ')'; counteronp =0;
    while(counter<=length) {

        if(expression[counter]>='a' && expression[counter]<='z') {
                onp += expression[counter];
                counteronp++;
            }
        else {

            if( expression[counter] == '(') {
                x = '('; S.push(x);
            }
            else {

                 if( expression[counter] == ')'){
                        top = S.top();
                        while(top!='(') {
                            pop = S.pop();
                            onp  += pop;
                            top = S.top();
                            counteronp++;
                        }
                        pop = S.pop();
                    }
                    else {

                        top = S.top();
                        while(value[top]>=value[expression[counter]]) { // dopóki aktualny znak ma mniejsza lub wiekszy
                            pop = S.pop();
                            onp += pop;
                            top = S.top();
                            counteronp++;
                        }
                       x = expression[counter]; S.push(x);
                    }
            }
        }
        counter++;
    }

   cout << onp << endl;
    return onp;
}

int output(string onp) {

    long long v1,v2, result;
    long long counter =0;
    while(counter<counteronp) {

        if(onp[counter]>='a' && onp[counter]<='z') {
                result = value[onp[counter]];
            }
        else {
        v1 = S.pop();
        v2 = S.pop();

        if(onp[counter]=='^') {

            if(v1>=0) {
                    result = 1;
                    for (int i = 0; i<v1; i++) {
                           result*=v2;
                    }
                }
            else result = 1;
        }
        if(onp[counter]=='/') {
                if(v1!=0) result = v2/v1;
                else result =0;
        }
        if(onp[counter]=='*') {
               result = v1*v2;
        }
         if(onp[counter]=='+') {
               result = v1+v2;
        }
        if(onp[counter]=='-') {
               result = v2-v1;
        }
        if(onp[counter]>='a' && onp[counter]<='z') {
                result = value[onp[counter]];
            }
        }
        S.push(result);
        counter++;
    }
    cout << S.pop() << endl;
}

int main()
{
    long long z,counter,w;
    cin >> z;
    string expression,onp;
    value['('] =0; value[')'] =0; value['+'] =1; value['-'] =1; value['/'] =2; value['*'] =2; value['^'] =3;
    for ( int i =0; i<z; i++) {
        counter =97;

            while(counter<97+26) {
                    cin >> value[counter];
                    counter++;
            }
            cin >> w;
            while(w>0) {
                cin >> expression;
                S.clear();
                onp = onpstack(expression);
                S.clear();
                output(onp);
                onp.clear();
                w--;
            }
    }
    return 0;
}
