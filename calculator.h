#include <iostream>
#include<string>
using namespace std;

class number {

    string tab;
    int capacity;
    int sign;

    public:
        number( string number="0") {

            if(number[0]=='-') sign =1;
            else sign =0;
            capacity = number.size();
            for ( int i =capacity-1; i>=0 +sign; i--) {
                tab += number[i];
            }
            capacity = number.size()-sign;
        }

        void add ( number&a );
        void subtract ( number&a );
        void multi ( number&a);

        int compare ( number&a) {

            if(capacity <a.capacity)
            {
               return -1;
            }
            else {

                if(capacity==a.capacity) {

                   for ( int i = a.capacity-1; i>=0; i--) {
                        if ( tab[i] > a.tab[i]) {
                                return 1;
                                break;
                        }

                        if ( tab[i] < a.tab[i]) {
                                return -1;
                                break;
                        }
                    }
                }
                else {
                    return 1;
                }
            }

        }

        void copya ( number&a) {

            int rest =0, rest1 =0, i=0, copycapacity, copysign;
            string numbercopy;

            numbercopy = tab;
            copycapacity = capacity;
            tab = a.tab;
            capacity = a.capacity;
            a.tab = numbercopy;
            a.capacity = copycapacity;
        }

        void change ( number&a) {

            if(capacity <a.capacity)
            {
               copya(a);
            }
            else {

                if(capacity==a.capacity) {

                   for ( int i = a.capacity-1; i>=0; i--) {
                        if ( tab[i] > a.tab[i]) {
                                break;
                        }

                        if ( tab[i] < a.tab[i]) {
                                copya(a);
                                break;
                        }
                    }
                }
            }
        }

        void operator += (number& a) {

            if(sign==0 && a.sign==0){
                change(a);
                add(a);
                return;
            }
            if(sign==1 && a.sign==1){
                change(a);
                add(a);
                sign = 1;
                return;
            }
            if(sign == 1 && a.sign ==0 && compare(a)==-1)
            {
                change(a);
                subtract(a);
                sign = 0;
                return;

            }
             if(sign == 1 && a.sign ==0 && compare(a)==1)
            {
                 change(a);
                subtract(a);
                sign = 1;
                return;
            }
             if(sign == 0 && a.sign ==1 && compare(a)==1)
            {
                change(a);
                subtract(a);
                sign = 0;
                return;
            }
             if(sign == 0 && a.sign ==1 && compare(a)==-1)
            {
                change(a);
                subtract(a);
                sign = 1;
                return;
            }
            change(a);
            subtract(a);
            sign =0;

        }

         void operator -= (number& a) {

             if(sign==0 && a.sign==0 && (compare(a)==1 || compare(a)==0) ){
                subtract(a);
                return;
            }
            if(sign==0 && a.sign==0 && compare(a)==-1){
                change(a);
                subtract(a);
                sign = 1;
                return;
            }
            if(sign==1 && a.sign==1 && (compare(a)==1 || compare(a)==0) ){
                change(a);
                subtract(a);
                sign = 1;
                return;
            }
            if(sign==1 && a.sign==1 && compare(a)==-1){
                change(a);
                subtract(a);
                sign = 0;
                return;
            }
            if(sign == 1 && a.sign ==0 )
            {
                change(a);
                add(a);
                sign = 1;
                return;

            }
             if(sign == 0 && a.sign ==1)
            {
                change(a);
                add(a);
                sign = 0;
                return;
            }

            change(a);
            subtract(a);
            sign =0;
        }

        void operator *= (number& a) {

            if( (sign==1 && a.sign == 1) || ( sign==0 && a.sign==0) ) sign = 0;
            else sign = 1;
            change(a);
            multi(a);
        }

        friend int operator < (number &a, number &b) {

            int outsign =1; // zmieniam znak jesli liczby sa ujemne
            if(a.sign==1 && b.sign ==0) return -1;
            if( a.sign == 0 && b.sign == 1) return 1;

            if(a.sign == 1 ) outsign = -1;

            if(a.capacity > b.capacity) return 1*outsign;
            if(a.capacity < b.capacity) return -1*outsign;

            for ( int i = a.capacity-1; i>=0; i--) {
                    if ( a.tab[i]> b.tab[i]) return 1*outsign;
                    if ( a.tab[i] < b.tab[i]) return -1*outsign;
                }
            return 0;
        }

        friend istream& operator >> (istream &s, number &a) {

                string number;
                s >> number;

                if(number[0]=='-') a.sign =1;
                else a.sign =0;
                a.capacity = number.size();

                a.tab.clear();
                for ( int i =a.capacity-1; i>=0 + a.sign; i--) {
                    a.tab += number[i];
                }

                a.capacity = number.size() - a.sign;
                return s;
        }

        friend ostream& operator << (ostream &s, number &a) {

                int i=0;
                string number;
                if(a.sign==1) number += '-';
                while(a.tab[a.capacity-1]=='0' && a.capacity>1) {
                    a.capacity--;
                }

                 for ( i +=a.capacity-1; i>=0; i--) {
                    number += a.tab[i];
                }
                s << number;
                return s;
        }
};

void number::add( number&a) {

    int rest =0, rest1 =0, i=0;

    for ( i =0; i< capacity; i++) {

                if ( i< a.capacity) {

                    if ( (tab[i] + a.tab[i] -96 + rest ) >9 ) rest = 1;
                    else rest =0;

                    tab[i] = (tab[i] + a.tab[i] - 96 + rest1)%10 + 48;
                }
                else {

                    if ( (tab[i] -48 + rest ) >9 ) rest = 1;
                    else rest =0;

                    tab[i] = (tab[i] - 48 + rest1)%10 + 48;

                }
                rest1 = rest;
            }
            if(rest==1) {
                tab[i] = rest+48;
                i++;
            }
            capacity = i;
}

void number::subtract( number&a) {

    int rest =0, rest1 =0, i=0;

    for ( i =0; i< capacity; i++) {


                if ( i< a.capacity) {

                    if ( (tab[i] - a.tab[i] - rest ) < 0  ) {
                            tab[i] = tab[i] + 10;
                            rest = 1;
                    }
                    else rest =0;

                    tab[i] = tab[i] - a.tab[i] - rest1 + 48;
                }
                else {

                    if ( (tab[i] -48 - rest ) < 0 ) {
                        tab[i] = tab[i] +10;
                        rest = 1;
                    }
                    else rest =0;

                    tab[i] = tab[i] - rest1;
                }
                rest1 = rest;
            }

            capacity = i;
}

void number::multi( number &a) {

    int count1[1056];
    for ( int i =0; i<1056; i++) {
        count1[i] =0;
    }

    int i =0, j=0, licznik =0, licznik1 =0, value;

    for ( i =0; i <a.capacity; i++) {

            for ( j =0; j<capacity; j++) {

                count1[j+i] += (a.tab[i]-48)*(tab[j]-48);

            }



        licznik1 =0;
        licznik =0;
        for ( j = 0; j<capacity+i+1; j++) {

            licznik1 = (count1[j]+licznik)/10;
            count1[j] = (count1[j]+licznik)%10;
            licznik = licznik1;

            }
        }

    tab.clear();

     for ( int j =0; j< a.capacity + capacity; j++) {

            tab  += count1[j]+48;
        }

    capacity = a.capacity + capacity;

}
