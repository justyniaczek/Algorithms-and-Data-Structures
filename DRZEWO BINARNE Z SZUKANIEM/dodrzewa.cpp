#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <fstream>

using namespace std;
int ile;
double czas;
clock_t start, stop;

struct WezelDrzewaBin{
    int data;
    WezelDrzewaBin* lewy;
    WezelDrzewaBin* prawy;
};

///FUNKCJA TWORZ¥CA NOWY WEZEL
WezelDrzewaBin* StworzNowyWezel(int data) {
	WezelDrzewaBin* nowyWezel = new WezelDrzewaBin();
	nowyWezel->data = data;
	nowyWezel->lewy = nowyWezel->prawy = NULL;
	return nowyWezel;
}
WezelDrzewaBin* GenerujDDZ(WezelDrzewaBin* root,int data){ ///GENEROWANIE DRZEWA BINARNEGO  , wskaznik i liczba ktora dodajemy do drzewa
    if(root==0){                                          /// jesli poddrzewo jest puste
        root = StworzNowyWezel(data);  ///konczy dzilanie
    }
    else {
        root->lewy = GenerujDDZ(root->lewy,(data/2));
		root->prawy = GenerujDDZ(root->prawy,data-(data/2));
	}
	return root;
}
bool SzukajN(WezelDrzewaBin* root,int data) {
	if(root == NULL) {
		return false;
	}
	else if(root->data == data) {
		return true;
	}
	else if(data <= root->data) {
		return SzukajN(root->lewy,data);
	}
	else {
		return SzukajN(root->prawy,data);
	}
}
void DrukujDrzewoBin_util(WezelDrzewaBin *root, int h)
{
    int COUNT=1;
    if (root == NULL)
        return;
    h += COUNT;

    DrukujDrzewoBin_util(root->prawy, h+1);
    cout<<"\n";
    for (int i = COUNT; i < h; i++)
        cout<<("..");
    cout<<("\n", root->data);
    DrukujDrzewoBin_util(root->lewy, h+1);
}
void DrukujDrzewoBin(WezelDrzewaBin *root)
{
   DrukujDrzewoBin_util(root, 0);
}
int main()

{ int liczba;
    WezelDrzewaBin* root=NULL; /// Tworze nowe drzewo
    root = GenerujDDZ(root,5);
	root = GenerujDDZ(root,4);
	root = GenerujDDZ(root,0);
	root = GenerujDDZ(root,2);

    cout<<"\n";
    cout<<"DRUKOWANIE DRZEWA BINARNEGO\n";
    DrukujDrzewoBin(root);
    cout<< "\nWpisz liczbe ktora chcesz znalezc."<<endl;
    cin>> liczba;
    start= clock();
    if(SzukajN(root,liczba) == true){
        cout<<"Liczba " << liczba<< " jest w drzewie binarnym\n";}
	else {
            cout<<"NIE MA TAKIEJ LICZBY\n";}
    stop =clock();
    czas=(stop-start)/(double)CLOCKS_PER_SEC;
    cout<< "\n Czas wyszukiwania to:"<< czas<< "s"<<endl;
    fstream plik;
    plik.open("wyniki.txt", ios::out | ios::app);  // ZAPIS CZASU SORTOWANIA W PLIKU TEKSTOWYM
    plik<< czas<<"s   "<< ile<< endl;
    plik.close();
    return 0;
}
