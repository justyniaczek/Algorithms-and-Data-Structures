#include <iostream>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <stack>
#include <fstream>

using namespace std;
int start, stop;
int i, j,x ;
int pom;
void proste_wstawianie(int *tab, int ile)
{
     int pom, j;
     for(int i=1; i<ile; i++)
     {                           //wstawienie elementu w odpowiednie miejsce
        pom = tab[i];           //ten element bêdzie wstawiony w odpowiednie miejsce
        j = i-1;
                                          //przesuwanie elementów wiêkszych od pom
             while(j>=0 && tab[j]>pom)
             {  tab[j+1] = tab[j];          //przesuwanie elementów
                --j;
             }
             tab[j+1] = pom; //wstawienie pom w odpowiednie miejsce
     }
}




void QuickSort(int *tablica, int l,int p){
int lewy,prawy;

int m=10;// PEWNA STA£A OD KTÓREJ PODTABLICE NIE BEDA SORTOWANE
int x;
i=l; // LEWY INDEKS TABLICY
j=p; //PRAWY INDEKS TABLICY
x=tablica[(i+j)/2];
stack<pair<int,int> > stos; //INICJALIZACJA STOSU DLA DWÓCH LICZB
while(i>j){                //TRESC PROCEDURY PARTITION
    while(tablica[i]<x){
        i=i+1;
    }
    while(x<tablica[j]){
        j=j-1;
    }
    if(i<=j){
        tablica[i]=tablica[j];
        i=i+1;
        j=j-1;}
}                         //KONIEC PROCEDURY PARTITION

i=i+1;
stos.push({i,j});    // PARA INDEKSÓW Z PROCEDURY PARTITION NA STOS
j=prawy;             // PRAWY= OSTATNI ELEMENT TABLICY
i=lewy;             //LEWY = PIERWSZY ELEMENT TABLICY


while (lewy<prawy){    // PODZIA£ PODTABLICY

    if((j-lewy<m)&&(prawy-i<m)){    // JEŒLI OBIE PODTABLICE S¥ MA£E
       lewy = stos.top().first;    // odczyt liczby na szczyt stos jako first
        prawy = stos.top().second;    // odczyt liczby na szczyt stosu jako second
        stos.pop();
    }
    else if ((j-lewy<m)&&(prawy-i>=m)){// JESLI LEWA PODTABLICA JEST MALA , A PRAWA NIE
        lewy=i;                         // IGNOROWNIE LEWEJ PODTABLICY
    }
    else if((j-lewy >=m)&&(prawy-i>=m)){// JESLI PRAWA PODTABLICA JEST MA£A, A LEWA NIE
        prawy=j;                        //IGNOROWANIE PRAWEJ PODTABLICY
    }
    else if((j-lewy>=m)&&(prawy-i>=m)){ // JESLI OBIE PODTABLICE SA DUZE
        if(j-lewy> prawy-i){            // JESLLI LEWA JEST WIEKSZA
            stos.push({lewy,j});        //ODLOZ NA STOS PARE LICZB LEWY ORAZ J(KRANCE TABLICY)
            lewy=i;                     // USTALAM NOWY LEWY KRANIEC PRAWEJ PODTABLICY
        }
        else{                           // JESLI PRAWA PODTABLIC JEST WIEKSZA
            stos.push({i,prawy});       // ODK£ADAM NA STOS PARE LICZB LEWY I PRAWY
            prawy=j;                    // USTALAM NOWY KRANIEC LEWEJ PODTABLICY
        }
    }
}
}



void wypisz_losowanie( int *tab, int n){
    cout << "Wylosowane liczby to:\n"<<endl;
    for(int i=0; i<n; i++){
    cout << tab[i]<<" ";
    }
}
void wypisz_sortowanie( int *tab, int n){
    cout << "\nPodane liczby po sortowaniu:\n"<<endl;
    for(int i=0; i<n; i++){
    cout << tab[i]<<" ";
    }
}

int main()
{
    int ile;
    cout << "Generator liczb losowych , sortowanie" << endl;
    cout << "Ile liczb chcesz wylosowac?" << endl;
    cin>> ile;

    int i,czas;
    int *tablica;    //dynamiczna alokacja tablicy
    tablica=new int[ile];
    srand(time(NULL));
    for(i=0; i<ile; i++){
        tablica[i]= rand()% 10000+1;
    }
    wypisz_losowanie(tablica, ile);
    start= clock();
    QuickSort(tablica,0,ile-1);///WSTAWIC L I P KRANIEC TABLICY
    stop =clock();
    proste_wstawianie(tablica,ile);
    wypisz_sortowanie(tablica, ile);
    czas=(stop-start) / CLOCKS_PER_SEC;
    cout<< "\n Czas sortowania to:"<< czas<< "s"<<endl;
    fstream plik;
    plik.open("wyniki.txt", ios::out | ios::app);  // ZAPIS CZASU SORTOWANIA W PLIKU TEKSTOWYM
    plik<< czas<<"s   "<< ile<< endl;
    plik.close();
    delete []tablica;
    return 0;
}
