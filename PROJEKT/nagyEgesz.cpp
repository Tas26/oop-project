#include <iostream>
#include "NagyEgesz.h"

using namespace std;

int main() {

    int szamok[20] = {4, 2, 3, 5, 6, 1, 2, 6, 2, 5, 3, 1, 3 ,8 ,9 ,5, 7, 4, 5, 6};  
    int n = 20;

    NagyEgesz szam(1, n, szamok);

    int num = 1254;
    NagyEgesz szam2(num);

    NagyEgesz szam3(szam2);  

    cout << "Az eredeti szam: " << szam;
    cout << "prefix noveles: " << (++szam);
    cout << "postfix csokkentes: " << szam--;
    cout << "postfix noveles: " << szam++;
    cout << "prefix csokkentes: " << --szam;

    szam3 *= szam2;
    cout << "A szam3 *= szam2 eredmenye: " << szam3;

    szam2+=szam3;            
    cout << "A szam2 += szam3 eredmenye: " << szam2;

    szam-=szam2;           
    cout << "A szam -= szam2 eredmenye: " << szam;

    NagyEgesz eredmeny = szam * szam2;      
    cout << "szam * szam2 eredmenye: " << eredmeny;

    eredmeny = szam3 - szam2;
    cout << "A szam3 - szam2 eredmenye: " << eredmeny;

    eredmeny = szam + szam2;
    cout << "A szam + szam2 eredmenye: " << eredmeny;


    try {
        szam /= szam2;
        cout << "A szam /= szam2: ";
        cout << szam ;

        eredmeny = szam / szam2;
        cout << "A szam / szam2 eredmenye: " << eredmeny;

        eredmeny = szam / 0;
    }
    catch (NagyEgesz::NullavalValoOsztas){
        cout << "Nullaval nem lehet osztani.." << endl;
    }

    return 0;
}