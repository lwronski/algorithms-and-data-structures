#include <iostream>
using namespace std;

class person
{
    string name;
    int age;
    person *next;
    person(string a, int b) { name = a; age = b; next = NULL;}

    public:
        friend class list;
};

class list
{
    person* head = new person("head",0);

    public:
        list() {}

        void NEW( string n, int age) {

            person* temp = new person(n,age);
            person* personlast = head;

            while(personlast->next) {
                    personlast = personlast->next;
                }

            personlast->next = temp;
            temp->next = NULL;
        }

        void VIP( string n, int age) {

                person* temp = new person(n,age);
                temp->next = head->next;
                head->next = temp;
        }

        int INSERT( string n, int age, int number) {

                person* temp = new person(n,age);
                person* personlast = head;
                number--;
                while(personlast->next && number>0) {
                    personlast = personlast->next;
                    number--;
                }

                if(number==0) {

                    temp->next = personlast->next;
                    personlast->next = temp;
                }
                else cout << "ERROR" << endl;

        }

        void BUYING() {

            if( head->next == NULL ) {
                    cout << "ERROR" << endl;
            }
            else {
               person* persondelete = head->next;
               head->next = persondelete->next;
               delete persondelete;
            }

        }

        void  RESIGNATION() {

            if( head->next == NULL ) {
                    cout << "ERROR" << endl;
            }
            else {

               person* personlast = head;
               person* personlast1 = head;
                while(personlast->next) {
                    personlast1 = personlast;
                    personlast = personlast->next;
                }
                personlast1->next = NULL;
                delete personlast;
            }
        }

        void DELETE( string n1, int age1) {

            if( head->next == NULL ) {
                    cout << "ERROR" << endl;
            }
            else {

                person* personlast = head->next;
                person* personlast1 = head;
                while( (personlast->name!=n1 || personlast->age!=age1) && personlast->next!=NULL) {
                        personlast1 = personlast;
                        personlast = personlast->next;
                }
                if(personlast->next==0 && personlast->name==n1 && personlast->age==age1 ) {
                    personlast1->next = NULL;
                }
                else {

                    if( personlast->name==n1 && personlast->age==age1 ) {
                        personlast1->next = personlast->next;
                        delete personlast;
                    }
                    else {
                        cout << "ERROR" << endl;
                    }
                }
            }
        }

        void PRINT() {

            if( head->next == NULL ) {
                cout << "EMPTY" << endl;
            }
            else {
                person* personlast = head->next;
                while(personlast->next) {
                    cout << personlast->name << " " << personlast->age << endl;
                    personlast = personlast->next;
                }
                cout << personlast->name << " " << personlast->age << endl;
            }
        }

        void REVERSE() {

            if( head->next == NULL ) {
                cout << "EMPTY" << endl;
            }
            else {

                person* headnew = new person("head", 0);
                person* temp = head;
                person* personlast = head->next;

                while(personlast->next) {
                    temp = personlast;
                    personlast = personlast->next;

                    temp->next = headnew->next;
                    headnew->next = temp;
                }

                temp = personlast;

                temp->next = headnew->next;
                headnew->next = temp;

                head = headnew;
            }
        }

        void CLEAN()
        {
            if( head->next != NULL ) {
               person* personlast = head->next;
               person* personlast1 = head;
                while(personlast->next) {
                    personlast1 = personlast;
                    personlast = personlast->next;
                    delete personlast1;
                }
                head->next = NULL;
                delete personlast;
            }
        }
        ~list() {
            delete head;
        }
};

int main()
{
    ios_base::sync_with_stdio(0);
    int z,n,age,number;
    cin >> z;
    string in,name;
    list S;
    for ( int i =0; i<z; i++) {
        cin >> n;
            for ( int j =0; j<n; j++) {
                cin >> in;

                    if(in=="NEW") {
                        cin >> name >> age;
                        S.NEW(name,age);
                    }
                    if(in=="VIP") {
                        cin >> name >> age;
                        S.VIP(name,age);
                    }
                    if(in=="INSERT") {
                        cin >> name >> age >> number;
                        S.INSERT(name,age,number);
                    }
                    if(in=="BUYING") {
                        S.BUYING();
                    }
                    if(in=="RESIGNATION") {
                        S.RESIGNATION();
                    }
                     if(in=="DELETE") {
                        cin >> name >> age;
                        S.DELETE(name,age);
                    }
                    if(in=="PRINT") {
                        S.PRINT();
                    }
                     if(in=="REVERSE") {

                        S.REVERSE();
                    }
                    if(in=="CLEAN") {
                        S.CLEAN();
                    }
            }
            S.CLEAN();
    }
    return 0;
}
