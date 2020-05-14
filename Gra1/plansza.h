#ifndef PLANSZA_HH
#define PLANSZA_HH

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <windows.h>

#define strzalka_w_lewo 0x25
#define strzalka_w_prawo 0x27
#define strzalka_w_dol 0x28
#define strzalka_w_gore 0x26
#define enter 0x0D
#define ROZMIAR 15

using namespace std;

int wiersz = 0, kolumna = 0, obecny_wiersz = 1, obecna_kolumna = 1;
int ilosc_bomb;
int wygrana = 0;

struct pole {
	int wartosc;
	bool czy_odkryte;
};

pole plansza[ROZMIAR][ROZMIAR];

bool genruj_plansze();
bool generuj_bombe(int wiersz, int kolumna);
void losuj_bomby(int ilosc_bomb);
void odkryj_pole(int x, int y);
void wyswietl_plansze();
void poruszanie();
bool czy_wygrana();


bool genruj_plansze()
{
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			plansza[i][j].wartosc = 0;
			plansza[i][j].czy_odkryte = false;
		}
	}
		return true;
}

bool generuj_bombe(int wiersz, int kolumna)
{
	if (plansza[wiersz][kolumna].wartosc != 9) {
		plansza[wiersz][kolumna].wartosc = 9;

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if ((wiersz + j) < 0 || (kolumna + i) < 0) {
					continue; //koniec planszy
				}
				if ((wiersz + j) > ROZMIAR - 1 || (kolumna + i) > ROZMIAR - 1) {
					continue; //koniec planszy
				}
				if (plansza[wiersz + j][kolumna + i].wartosc == 9) {
					continue;
				}
					plansza[wiersz + j][kolumna + i].wartosc += 1; //zwieksz o 1 wokó³ bomby
				
			}
		}
	}

	return true;
}

void losuj_bomby(int ilosc_bomb)
{
	unsigned int pom;//zmienna pomocnicza do losowania liczb
	int pozycja_bomby_wiersz, pozycja_bomby_kolumna;
	int ilosc = ilosc_bomb;

	srand(unsigned int (&pom));
	while (ilosc > 0)
	{
		pozycja_bomby_wiersz = rand() % ROZMIAR;
		pozycja_bomby_kolumna = rand() % ROZMIAR;

		if (plansza[pozycja_bomby_wiersz][pozycja_bomby_kolumna].wartosc != 9){
			generuj_bombe(pozycja_bomby_wiersz, pozycja_bomby_kolumna);
			ilosc--;
		}
	}
}

void odkryj_pole(int wiersz, int kolumna)
{
	if (wiersz < 0 || wiersz > ROZMIAR - 1) {
		return; // czy nie wychodzi poza plansze
	}
	
	if (kolumna < 0 || kolumna > ROZMIAR - 1) {
		return;
	}
	
	if (plansza[wiersz][kolumna].czy_odkryte == true) {
		return;
	}

	if (plansza[wiersz][kolumna].wartosc != 9 && plansza[wiersz][kolumna].czy_odkryte == false) {
		plansza[wiersz][kolumna].czy_odkryte = true;   
	}
	if (plansza[wiersz][kolumna].wartosc != 0) {
		return;
	}

	//wywo³anie dla wszystkich pól obok 
	odkryj_pole(wiersz - 1, kolumna - 1);
	odkryj_pole(wiersz - 1, kolumna);
	odkryj_pole(wiersz - 1, kolumna + 1);
	odkryj_pole(wiersz + 1, kolumna - 1);
	odkryj_pole(wiersz + 1, kolumna);
	odkryj_pole(wiersz + 1, kolumna + 1);
	odkryj_pole(wiersz, kolumna - 1);
	odkryj_pole(wiersz, kolumna);
	odkryj_pole(wiersz, kolumna + 1);
}

void wyswietl_plansze()
{
	system("cls"); 

	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			if (j == wiersz && i == kolumna){ //nasza pozycja
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
				cout << "$";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				if (plansza[j][i].czy_odkryte == true) {
					if (plansza[j][i].wartosc == 0) {
						cout << " ";
					}
					else {
						cout << plansza[j][i].wartosc;
					}
				}
				if (plansza[j][i].czy_odkryte == false) { //pole nie odkryte
					cout << "%";
				}
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
		cout << endl;
	}

	cout << "\nTwoja pozycja:\n"; 
	cout << "X: " << wiersz << endl;
	cout << "Y: " << kolumna << endl;
}

void poruszanie()
{
	if ((GetKeyState(enter) & 0x80)) {
		if (plansza[wiersz][kolumna].wartosc == 9) {
			wygrana = 2;
		}

		odkryj_pole(wiersz, kolumna);
		wyswietl_plansze();
	}

	if ((GetKeyState(strzalka_w_prawo) & 0x80) && wiersz < ROZMIAR - 1) {
		wiersz++;// sprawdzanie czy klawisz wciœniêty i czy trzymany
	}

	if ((GetKeyState(strzalka_w_lewo) & 0x80) && wiersz > 0){ 
		wiersz--;
	}

	if ((GetKeyState(strzalka_w_dol) & 0x80) && kolumna < ROZMIAR - 1){
		kolumna++;
	}

	if ((GetKeyState(strzalka_w_gore) & 0x80) && kolumna > 0) {
		kolumna--;
	}

	if (obecna_kolumna == kolumna && obecny_wiersz == wiersz) {
		return; //brak ruchu
	}

	obecna_kolumna = kolumna; 
	obecny_wiersz = wiersz;

	wyswietl_plansze(); 
}

bool czy_wygrana()
{
	int bomby = 0;
	for (int i = 0; i < ROZMIAR; i++)
	{
		for (int j = 0; j < ROZMIAR; j++)
		{
			if (plansza[i][j].czy_odkryte == false) {
				bomby++;
			}
		}
	}
	if (bomby == ilosc_bomb) {
		return true;
	}

	else{
		return false;
	}
}

#endif 