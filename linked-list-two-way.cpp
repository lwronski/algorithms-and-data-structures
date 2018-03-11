#include <iostream>
using namespace std;

class person
{
    public:
        long long int a;
        long long int b;
        person *next;
        person *previous;
        person(long long int a1, long long int b1) { a = a1; b = b1; next = NULL; previous = NULL;}

};

class doublelist
{
    public:

        person* head = new person(0,0);
        person* tail = new person(0,0);

        doublelist( ) { head->next = tail; tail->previous = head;}

        void PRINT_ASC ( ) {

            person* personlast = head->next;
            if(head->next == tail) cout << "EMPTY" << endl;
            else {

                if( personlast->a==0) {
                    cout << personlast->b;
                }
                if(personlast->a!=0) {
                        if(personlast->b==1){
                            cout << "x^" << personlast->a;
                        }
                        if(personlast->b==-1) {
                            cout << "-x^" <<personlast->a ;
                        }
                        if(personlast->b!=1 && personlast->b!=-1){
                            cout <<personlast->b << "x^" << personlast->a;
                        }
                }
                personlast = personlast->next;
                while(personlast->next) {

                        if(personlast->b==1) {
                            cout << "+x^" << personlast->a;
                        }
                        else {

                             if(personlast->b==-1) {
                                    cout << "-x^" << personlast->a;
                                }
                             else {
                                    if(personlast->b>0) cout << "+";
                                    cout << personlast->b << "x^" << personlast->a;
                             }

                        }
                        personlast = personlast->next;
                }
                cout << endl;
            }
        }

        void PRINT_DESC ( ) {

            person* personlast = tail->previous;
            if(tail->previous == head) cout << "EMPTY" << endl;
            else {

                if( personlast->a==0) {
                    cout << personlast->b;
                }
                if(personlast->a!=0) {
                        if(personlast->b==1){
                            cout << "x^" << personlast->a;
                        }
                        if(personlast->b==-1) {
                            cout << "-x^" <<personlast->a ;
                        }
                        if(personlast->b!=1 && personlast->b!=-1){
                            cout <<personlast->b << "x^" << personlast->a;
                        }
                }
                personlast = personlast->previous;
                while(personlast->previous) {

                        if(personlast->a!=0) {

                            if(personlast->b==1) {
                                cout << "+x^" << personlast->a;
                            }
                            else {

                                if(personlast->b==-1) {
                                        cout << "-x^" << personlast->a;
                                    }
                                else {
                                        if(personlast->b>0) cout << "+";
                                        cout << personlast->b << "x^" << personlast->a;
                                }

                            }
                        }
                        else {

                            if(personlast->b==1) {
                                cout << "+1";
                            }
                            else {

                                if(personlast->b==-1) {
                                        cout << "-1";
                                    }
                                else {
                                        if(personlast->b>0) cout << "+";
                                        cout << personlast->b;
                                }

                            }
                        }
                        personlast = personlast->previous;
                }
                cout << endl;
            }
        }

       person* ADD_MONO( long long int ina, long long int inb, person* p) {

            person* temp = new person(ina,inb);
            person* personlast = p->next;
            person* personlast1 = p->next;
            if(inb!=0) {
            if(p->next == tail) { // jeli lista jest pusta
                p->next = temp;
                temp->previous = p;
                temp->next = tail;
                tail->previous = temp;
                return temp->previous;
            }
            else {  // jeli znajdujš się elementy

                while( personlast->a < ina && personlast->next!=NULL) {
                        personlast = personlast->next;
                }
                if(personlast->a == ina && personlast->next!=NULL) { // jeli dany stopień istnieje już w licie

                    personlast->b = personlast->b + inb;
                    delete temp;
                    if( personlast->b ==0) {

                        personlast->next->previous = personlast->previous;
                        personlast->previous->next = personlast->next;
                        personlast1 = personlast->previous;
                        delete personlast;
                        return personlast1;
                    }
                    else return personlast->previous;
                }
                else {  // jeli nie to dodaje
                    personlast1 = personlast->previous;
                    temp->next = personlast;
                    temp->previous = personlast1;
                    personlast->previous = temp;
                    personlast1->next = temp;
                    return personlast->previous;
                }
            }
            }
        }

        void DERIVATIVE () {

            if(head->next !=tail) {
                long long int minusb;
                person* personlast = head->next;
                if(personlast->a==0) {
                    minusb = (personlast->b)*(-1);
                    ADD_MONO(0,minusb,head);
                    personlast = head->next;
                }

                while(personlast->next) {
                        personlast->b = personlast->b*(personlast->a);
                        personlast->a = personlast->a -1;
                        personlast = personlast->next;
                    }

            }
        }

        void MULTI_CONST(long long int ina) {

            person* personlast = head->next;

                if(ina != 0) {

                    while(personlast->next) {
                        personlast->b = personlast->b * ina;
                        personlast = personlast->next;
                    }
                }
                else CLEAN();

        }

        void MIN() {

                if(head->next==tail) cout << "ERROR" << endl;
                else {
                    cout << head->next->b << endl;
                }
        }

         void MAX() {

                if(head->next==tail) cout << "ERROR" << endl;
                else {
                    cout << tail->previous->b << endl;
                }
        }

        void CLEAN() {

            if(head->next == tail) {
            }
            else
            {
                person* personlast = head->next;
                person* personlast1 = head->next;

                while(personlast->next) {
                        personlast1 = personlast;
                        personlast = personlast->next;
                        delete personlast1;
                    }

                head->next = tail;
                tail->previous = head;
               // cout << "OK" << endl;
            }
        }

        ~doublelist() {
            delete head;
            delete tail;
        }
};

void ADD(doublelist& A, doublelist& B) {

        person* rate = A.head;
        person* rate1 = A.head;
        if( B.head->next != B.tail) {

            person* personlast = B.head->next;
            while(personlast->next) {
                rate = A.ADD_MONO(personlast->a, personlast->b,rate);
                personlast = personlast->next;
            }
        }
}

doublelist copytab;

void MULTI(doublelist& B, doublelist& A) {

        long long int a,b, licznik=0;
        copytab.CLEAN();
        person* rate = copytab.head;
        person* rate1 = copytab.head;
        person* personlast = A.head->next;
        person* personlast1 = B.head->next;

        while(personlast->next) {
            licznik=0;
            while(personlast1->next) {
                a = personlast->a + personlast1->a;
                b = (personlast->b)*(personlast1->b);
                if(licznik==0) {
                    rate = copytab.ADD_MONO(a,b,rate);
                    rate1 = rate;
                }
                else {
                    rate1 = copytab.ADD_MONO(a,b,rate1);
                }
                licznik++;
                personlast1 = personlast1->next;
            }
            personlast = personlast->next;
            personlast1 = B.head->next;
        }

        B.CLEAN();

        personlast = copytab.head->next;
        rate = B.head;
        while(personlast->next) {
               rate = B.ADD_MONO(personlast->a, personlast->b,rate);
               personlast = personlast->next;
        }
        copytab.CLEAN();
}

int main()
{
    ios_base::sync_with_stdio(0);
    doublelist tab[26];
    long long int z,n,a,b;
    cin >> z;
    string in,id,id2;
    for ( int i =0; i<z; i++) {

        cin >> n;
        for ( int j =0; j<n; j++) {
                cin >> in;
                if(in=="PRINT_ASC") {
                    cin >> id;
                    tab[id[0]-'A'].PRINT_ASC();
                }
                if(in=="PRINT_DESC") {
                    cin >> id;
                    tab[id[0]-'A'].PRINT_DESC();
                }
                 if(in=="DERIVATIVE") {
                    cin >> id;
                    tab[id[0]-'A'].DERIVATIVE();
                }
                if(in=="ADD_MONO") {
                    cin >> id >> a >> b;
                    tab[id[0]-'A'].ADD_MONO(a,b,tab[id[0]-'A'].head);
                    cout << "ADD OK" << endl;
                }
                if(in=="ADD") {
                    cin >> id >> id2;
                    ADD(tab[id[0]-'A'],tab[id2[0]-'A']);
                    cout << "ADD OK" << endl;
                }
                if(in=="MULTI_CONST") {
                    cin >> id >> a;
                    tab[id[0]-'A'].MULTI_CONST(a);
                    cout << "MULTI OK" << endl;
                }
                if(in=="MULTI") {
                    cin >> id >> id2;
                    MULTI(tab[id[0]-'A'],tab[id2[0]-'A']);
                    cout << "MULTI OK" << endl;
                }
                if(in=="MIN") {
                    cin >> id;
                    tab[id[0]-'A'].MIN();
                }
                 if(in=="MAX") {
                    cin >> id;
                    tab[id[0]-'A'].MAX();
                }
                 if(in=="CLEAN") {
                    cin >> id;
                     if(tab[id[0]-'A'].head->next == tab[id[0]-'A'].tail) cout << "EMPTY" << endl;
                    else {
                        cout << "CLEAN OK" << endl;
                    }
                    tab[id[0]-'A'].CLEAN();
                }
        }

        for ( int j =0; j<26; j++) {
            tab[j].CLEAN();
        }

    }

    return 0;
}
