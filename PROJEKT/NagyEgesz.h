#include <iostream>

using namespace std;

#define MAX 100

class NagyEgesz {
private:
    int elojel;
    int n;
    int *szamjegyek;
public:
    NagyEgesz();                   
    ~NagyEgesz();
    NagyEgesz(int,int,const int*);  
    NagyEgesz(const NagyEgesz&);    
    NagyEgesz(int);                  
    NagyEgesz(long);

    ostream& Kiir(ostream&) const; // nem lehet valtoztatni

    NagyEgesz operator=(const NagyEgesz&); //megvan

    NagyEgesz operator+(NagyEgesz);         //megvan
    NagyEgesz operator+=(NagyEgesz&);       //megvan

    NagyEgesz operator-(NagyEgesz);         //megvan
    NagyEgesz operator-=(NagyEgesz&);       //megvan

    NagyEgesz operator*(NagyEgesz);         //megvan
    NagyEgesz operator*=(NagyEgesz&);       //megvan

    NagyEgesz operator/(NagyEgesz);          //megvan
    NagyEgesz operator/=(NagyEgesz&);         //megvan

    NagyEgesz operator++();    //prefix ++i         //megvan
    NagyEgesz operator--();                         //megvan

    NagyEgesz operator++(int); // postfix i++       //megvan
    NagyEgesz operator--(int);                      //megvan

    //NagyEgesz operator<(NagyEgesz&);
    bool operator>(NagyEgesz&);                     //megvan
    bool eleje_nagyobb(NagyEgesz, NagyEgesz, int);
    NagyEgesz kivon_eleje(NagyEgesz, NagyEgesz, int);

    class NullavalValoOsztas {};      // automatikusan legeneral konstruktort stb.

};

ostream& operator<<(ostream& s, const NagyEgesz& b) {    
    return b.Kiir(s);
}

bool NagyEgesz::eleje_nagyobb(NagyEgesz a, NagyEgesz b, int k) {

    // a = 1 2 3 4 8
    // a = 0 0 0 4 8

    int i = MAX-a.n;
    if(k > b.n && a.szamjegyek[MAX-a.n] != 0)
        return true;
    else {
        if(k > b.n) {
            if(a.szamjegyek[i] == 0 && i < MAX - b.n) {
                i++;
            }
        }
    }
    // a = 0 0 1 9 0
    // b = 1 2 5 4

    for(int j = 0; j < k && j < b.n; j++) {
        if(a.szamjegyek[i+j] > b.szamjegyek[MAX - b.n + j]) {
            return true;
        }
        else 
            if(a.szamjegyek[i+j] < b.szamjegyek[MAX - b.n + j]) {
                //cout << a.szamjegyek[i+j] << " < " << b.szamjegyek[MAX - b.n + j] << endl;
                return false;
            }
    }
}

NagyEgesz NagyEgesz::kivon_eleje(NagyEgesz a, NagyEgesz b, int k ) {
    NagyEgesz eredmeny = a;

    int i = MAX-a.n;

    int db =0, sum=0;
    int j = i+k-1;
    int l = MAX-1;

    while(j >= i && l >= MAX-(b.n)) {
       
        if(a.szamjegyek[j] < b.szamjegyek[l]) {
            sum = (10+a.szamjegyek[j]) - b.szamjegyek[l];
            a.szamjegyek[j-1] -= 1;
        }
        else {
            sum = a.szamjegyek[j] - b.szamjegyek[l];
        }
        db++;
        //cout << a.szamjegyek[j] << " - " << b.szamjegyek[l] << " = " << sum << endl;
        eredmeny.szamjegyek[j] = sum;
        j--; l--;
    }
    while(j >= i) {
        eredmeny.szamjegyek[j] = a.szamjegyek[j];
        db++;
        j--;
        
    }
    while(l >= MAX-(b.n)) {
        eredmeny.szamjegyek[j] = b.szamjegyek[l];
        db++;
        l--;
    }

    return eredmeny;
}


NagyEgesz NagyEgesz::operator--() {
    int carry = 1;

    if(this->elojel == 0) {
        this->elojel = -1;
        szamjegyek[MAX-1] = carry;
    }

    int i;
    for(i = MAX-1; i >= MAX-n; i--) {
        if(this->szamjegyek[i] <= 0) {
            this->szamjegyek[i] = this->szamjegyek[i]+10 - carry;
            carry = 1;
        }
        else {
            this->szamjegyek[i] =this->szamjegyek[i]-carry;
            carry = 0;
        }
    }

    return *this;
}

NagyEgesz NagyEgesz::operator--(int b) {
    // eloszor teritem es utana modositom.
    int carry = 1;

    NagyEgesz masolat(*this);

        if(this->elojel == 0) {
        this->elojel = -1;
        szamjegyek[MAX-1] = carry;
    }

    int i;
    for(i = MAX-1; i >= MAX-n; i--) {
        if(this->szamjegyek[i] <= 0) {
            this->szamjegyek[i] = this->szamjegyek[i]+10 - carry;
            carry = 1;
        }
        else {
            this->szamjegyek[i] = this->szamjegyek[i]-carry;
            carry = 0;
        }
    }

    return masolat;
}

NagyEgesz NagyEgesz::operator++() {
    int carry = 1;

    int i;
    for(i = MAX-1; i >= MAX-n; i--) {
        int sum = this->szamjegyek[i] + carry;
        if(sum >= 10) {
            carry = 1;
            this->szamjegyek[i] = sum % 10;
        }
        else {
            carry = 0;
            this->szamjegyek[i] = sum;
        }
    }

    if(carry) {
        this->szamjegyek[i] = 1;
        this->n++;
    }

    return *this;
}

NagyEgesz NagyEgesz::operator++(int b) {
    // eloszor teritem es utana modositom.
    int carry = 1;

    NagyEgesz masolat(*this);

    int i;
    for(i = MAX-1; i >= MAX-n; i--) {
        int sum = this->szamjegyek[i] + carry;
        if(sum >= 10) {
            carry = 1;
            this->szamjegyek[i] = sum % 10;
        }
        else {
            carry = 0;
            this->szamjegyek[i] = sum;
        }
    }

    if(carry) {
        this->szamjegyek[i] = 1;
        this->n++;
    }

    return masolat;
}

// x = 5
// 3 + (++x)    = 9   x = 6
// 3 + (x++)    = 8   x = 6

ostream& NagyEgesz::Kiir(ostream& s) const{

    if(elojel < 0) {
        s << "-";    
    }
    else {
        s << "+";
    }
    for(int i = MAX-n; i < MAX; i++) {
        s << szamjegyek[i] << " ";
    }
    s << endl;

    return s;
}

NagyEgesz::NagyEgesz() {
    elojel = 0;
    n = 0;
    szamjegyek = new int[MAX] {0};
}

NagyEgesz::~NagyEgesz() {
    delete[] szamjegyek;
}

NagyEgesz::NagyEgesz(int prefix, int meret, const int* szamok) {
    elojel = prefix;
    n = meret;
    szamjegyek = new int[MAX] ;
    int j = 0;
    for(int i = MAX-n; i < MAX; i++) {
        
        szamjegyek[i] = szamok[j];
        j++;
    }
}

NagyEgesz::NagyEgesz(const NagyEgesz& b) {
    this->elojel = b.elojel;
    this->n = b.n;
    this->szamjegyek = new int[MAX] {0};

    for(int i = 0; i < MAX; i++) {
        this->szamjegyek[i] = b.szamjegyek[i];
    }
}

NagyEgesz::NagyEgesz(int szam) {
    if(szam < 0) {
        elojel = -1;
        szam *= (-1);
    }
    else {
        if(szam > 0) {
            elojel = 1;
        }
        else elojel = 0;
    }

    szamjegyek = new int[MAX] {0};

    int c, db = 0, i = MAX-1;
    while(szam) { 
        c = szam % 10;
        szam /= 10;
        szamjegyek[i] = c;
        i--;
        db++;
    }

    n = db;

}

NagyEgesz::NagyEgesz(long szam) {
    if(szam < 0) {
        elojel = -1;
        szam *= (-1);
    }
    else {
        if(szam > 0) {
            elojel = 1;
        }
        else elojel = 0;
    }

    szamjegyek = new int[MAX] {0};

    int c, db = 0, i = MAX-1;
    while(szam) {
        c = szam % 10;
        szam /= 10;
        szamjegyek[i] = c;
        i--;
        db++;
    }

    n = db;
}

NagyEgesz NagyEgesz::operator=(const NagyEgesz& b) {
    this->elojel = b.elojel;
    this->n = b.n;

    for(int i = 0; i < MAX; i++) {
        this->szamjegyek[i] = b.szamjegyek[i];
    }

    return *this;
}

bool NagyEgesz::operator>(NagyEgesz& b) {
    if(this->n > b.n)
        return true;
    else {
        if(this->n < b.n) {
            return false;
        }
        else {
            for(int i = MAX-n; i < MAX; i++) {
                if(this->szamjegyek[i] > b.szamjegyek[i]) {
                    return true;
                }
                else {
                    if(this->szamjegyek[i] < b.szamjegyek[i]) {
                        return false;
                    }
                }
            }
            return false;
        }
    }
}

NagyEgesz NagyEgesz::operator-(NagyEgesz b) {
    // (+3) - (-5) = 3 + 5 = +8 (osszeadas)
    // (+3) - (+5) = 3 - 5 = -2 (kivonas)
    NagyEgesz eredmeny;

    eredmeny.szamjegyek = new int[MAX];

    if(this->elojel == b.elojel) {
        // 8 - 5 = 3
        // 5 - 8 = -3
        // -(8 - 5) =  -3
        // (-5) - (-8) =  +3
        // +(-8 - -5)
        // +3

        //cout << "elojelek: " << this->elojel << " == " << b.elojel << endl;
        //  2345 - 12345 
        // 12345 - 2345
        if(!((*this) > b)) {
            eredmeny = b - (*this);
            eredmeny.elojel = this->elojel * (-1);
            return eredmeny;
        }

        //sima kivonas
        eredmeny.elojel = this->elojel;
        int db =0, sum=0;
        int i = MAX-1;

        while(i >= MAX-(this->n) && i >= MAX-(b.n)) {
            if(this->szamjegyek[i] < b.szamjegyek[i]) {
                sum = (10+this->szamjegyek[i]) - b.szamjegyek[i];
                this->szamjegyek[i-1] -= 1;
            }
            else {
                sum = this->szamjegyek[i] - b.szamjegyek[i];
            }
            db++;
            eredmeny.szamjegyek[i] = sum;
            i--;
        }
        while(i >= MAX-(this->n)) {
            eredmeny.szamjegyek[i] = this->szamjegyek[i];
            db++;
            i--;
        }
        while(i >= MAX-(b.n)) {
            eredmeny.szamjegyek[i] = b.szamjegyek[i];
            db++;
            i--;
        }
        eredmeny.n = db;

        return eredmeny;
    }
    else {
        if(this->elojel > 0 && b.elojel < 0) {
            // aktualis pozitiv parameterkent negativ && aktualis nagyobb mint a paramterben kapott   +-bol -   eredmeny +
            b.elojel = 1;
            return (*this)+b;
        }
        else {
            if(this->elojel < 0 && b.elojel > 0) {
                // aktualis negativ , parameter pozitiv && aktualis > mint a parameter         -bol +       eredmeny -
                b.elojel = -1;
                return (*this)+b;
            }
        }
    }
}

NagyEgesz NagyEgesz::operator-=(NagyEgesz& b) {             // atnezni
    return *this = *this - b;
}

NagyEgesz NagyEgesz::operator+(NagyEgesz b) {

    NagyEgesz eredmeny;

    eredmeny.szamjegyek = new int[MAX];

    if(this->elojel == b.elojel) {
        // siman osszeadni;
        eredmeny.elojel = this->elojel;
        int db=0, carry=0, sum=0;
        //   1 2 3 4 5 6 7
        //             8 9
        //   1 2 3 4 6 5 6
        int i = MAX-1;
        while(i >= MAX-(this->n) && i >= MAX-(b.n)) {  
            sum = this->szamjegyek[i] + b.szamjegyek[i] + carry;
            db++;
            if(sum >= 10) {
                carry=1;
                eredmeny.szamjegyek[i] = sum % 10;
            }
            else {
                carry = 0;
                eredmeny.szamjegyek[i] = sum;
            }
            i--;
        }
        while(i >= MAX-(this->n)) {
            sum = this->szamjegyek[i] + carry;
            if(sum >= 10) {
                carry=1;
                eredmeny.szamjegyek[i] = sum % 10;
            }
            else {
                carry = 0;
                eredmeny.szamjegyek[i] = sum;
            }
            db++;
            i--;
        } 
        while(i >= MAX-(b.n)) {
            sum = b.szamjegyek[i] + carry;
            if(sum >= 10) {
                carry=1;
                eredmeny.szamjegyek[i] = sum % 10;
            }
            else {
                carry = 0;
                eredmeny.szamjegyek[i] = sum;
            }
            db++;
            i--;
        } 
        if(carry) {
            db++;
            eredmeny.szamjegyek[i] = 1;
        }

        eredmeny.n = db;

        return eredmeny;
    }
    else {
        //-12345 + 2345
        // 2345 - 12345

        if(this->elojel > 0 && b.elojel < 0) {
            // aktualis pozitiv parameterkent negativ && aktualis nagyobb mint a paramterben kapott
            //8 + (-5) = 8 - 5 = 3
            b.elojel = +1;
            return (*this) - b;
        }
        else {
            
            if(this->elojel < 0 && b.elojel > 0) {
                // aktualis negativ , parameter pozitiv && aktualis < mint a parameter
                //(-5) + (+8) = 8 - 5 = 3
                // this->elojel = +1;
                NagyEgesz masolat = (*this);
                masolat.elojel = +1;
                return b - masolat;
            }  
        }
    }
}

NagyEgesz NagyEgesz::operator+=(NagyEgesz& b) {                     //atnezni 
    return *this = *this + b;
}

NagyEgesz NagyEgesz::operator*(NagyEgesz b) {
    NagyEgesz eredmeny;
    NagyEgesz masolat;

    masolat.szamjegyek = new int[MAX] {0};
    
    if(this->elojel == 0 || b.elojel == 0) {
        eredmeny.elojel = 0;
        eredmeny.szamjegyek = new int[MAX] {0};
        return eredmeny;
    }

    eredmeny.szamjegyek = new int[MAX] {0};
    int carry = 0, db = 0, sum = 0, kivono = 1, szamolo = 0;

    if(this->elojel != b.elojel) 
        // ha az elojelek megegyezoek akkor pozitiv szam lesz az eredmeny
        //eredmeny.elojel = -1;
        masolat.elojel = -1;
    else {
        //eredmeny.elojel = 1;
        masolat.elojel = 1;
    }
        
    for(int i = MAX-1; i >= MAX - b.n; i--) { 
        int szorzo = b.szamjegyek[i];
        int k = MAX-1-szamolo;
        int k2 = MAX-1;

        int szamolo_masolat = szamolo;
        int index = 1;

        for(int j = 0 ; j < MAX; j++) {
            eredmeny.szamjegyek[j] = 0;
        }
        db = 0;

        while(szamolo) {
            eredmeny.szamjegyek[k2] = 0;
            szamolo--;
            k2--;
            db++;
        }

        szamolo = szamolo_masolat;
        carry = 0;

        for(int j = MAX-1; j >= MAX - this->n; j--) {
            
            sum = this->szamjegyek[j] * szorzo + carry;
            //cout << "carry = " << carry << endl;
            //cout << this->szamjegyek[j] << " * " << szorzo << " + " << carry << endl;
            //cout << sum << endl;
            
            db++;
            if(sum >= 10) {
                carry = sum / 10;
                eredmeny.szamjegyek[k] = sum % 10;
                //cout << eredmeny.szamjegyek[k] << endl;
                k--;
            }
            else {
                carry = 0;
                eredmeny.szamjegyek[k] = sum;
                //cout << eredmeny.szamjegyek[k] << endl;
                k--;
            }
            if(j == MAX-n && carry) {
                eredmeny.szamjegyek[k] = carry;
                k--;
                db++;
            }
        }

        szamolo++;
        eredmeny.n = db;        
        masolat.n = db;
       
        int j;
        for(j = MAX-1; j >= MAX- masolat.n; j--) {
            masolat.szamjegyek[j] += eredmeny.szamjegyek[j];
            if(masolat.szamjegyek[j] >= 10) {
                masolat.szamjegyek[j-1]++;
                masolat.szamjegyek[j] %= 10;
                if(j == MAX-masolat.n) {
                    masolat.n++;
                    eredmeny.n++;
                }
            }
        }
        if(carry) {
            masolat.szamjegyek[j] += eredmeny.szamjegyek[j];
            
            if(masolat.szamjegyek[j] >= 10) {
                masolat.szamjegyek[j-1]++;
                masolat.szamjegyek[j] %= 10;
                
            }
            
        }
    }

    eredmeny = masolat;

    delete[] masolat.szamjegyek;
    return eredmeny;
}

NagyEgesz NagyEgesz::operator*=(NagyEgesz& b) {
    return *this = *this * b;
}

NagyEgesz NagyEgesz::operator/(NagyEgesz b) {
    try {
        if(b.n == 0)
            throw "Can't devide by 0..";

        NagyEgesz masolat;
        masolat.szamjegyek = new int[MAX];

        if(this->elojel != b.elojel) 
            masolat.elojel = -1;
        else
            masolat.elojel = 1;

        NagyEgesz osztando = *this;

        int tomb[MAX];
        int v = 0;
        int k = b.n;
        while(osztando > b) {
            int hanyszor = 0;
            if(eleje_nagyobb(osztando,  b, k)) {
                while(eleje_nagyobb(osztando,  b, k)) {
                    osztando = kivon_eleje(osztando, b, k);
                    
                    hanyszor++;

                }
            } else {
                k = b.n + 1;
                while(eleje_nagyobb(osztando,  b, k)) {
                    osztando = kivon_eleje(osztando, b, k);
                    hanyszor++;
                }
            }
            
            if(osztando.szamjegyek[MAX-osztando.n] == 0) {
                osztando.n--;
            }
        
            tomb[v] = hanyszor;
            v++;
        }
        
        return NagyEgesz(masolat.elojel, v, tomb);
    }
    catch (const char *s) {
        throw NullavalValoOsztas();
    }
}

NagyEgesz NagyEgesz::operator/=(NagyEgesz& b) {
    try {
        return *this = *this / b;
    }
    catch (const char *s) {
        throw NullavalValoOsztas();
    }
}
